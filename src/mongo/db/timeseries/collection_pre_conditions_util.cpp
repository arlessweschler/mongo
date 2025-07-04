/**
 *    Copyright (C) 2025-present MongoDB, Inc.
 *
 *    This program is free software: you can redistribute it and/or modify
 *    it under the terms of the Server Side Public License, version 1,
 *    as published by MongoDB, Inc.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    Server Side Public License for more details.
 *
 *    You should have received a copy of the Server Side Public License
 *    along with this program. If not, see
 *    <http://www.mongodb.com/licensing/server-side-public-license>.
 *
 *    As a special exception, the copyright holders give permission to link the
 *    code of portions of this program with the OpenSSL library under certain
 *    conditions as described in each individual source file and distribute
 *    linked combinations including the program with the OpenSSL library. You
 *    must comply with the Server Side Public License in all respects for
 *    all of the code used other than as permitted herein. If you modify file(s)
 *    with this exception, you may extend this exception to your version of the
 *    file(s), but you are not obligated to do so. If you do not wish to do so,
 *    delete this exception statement from your version. If you delete this
 *    exception statement from all source files in the program, then also delete
 *    it in the license file.
 */

#include "mongo/db/timeseries/collection_pre_conditions_util.h"


namespace mongo::timeseries {

CollectionPreConditions getCollectionPreConditions(OperationContext* opCtx,
                                                   const NamespaceString& nss,
                                                   boost::optional<UUID> expectedUUID) {

    auto acquisitionRequest = CollectionAcquisitionRequest::fromOpCtx(
        opCtx, nss, AcquisitionPrerequisites::OperationType::kRead, expectedUUID);

    auto [acquisition, wasNssTranslatedToBuckets] =
        acquireCollectionWithBucketsLookup(opCtx, acquisitionRequest, LockMode::MODE_IS);

    if (!acquisition.exists()) {
        return NonExistentCollectionPreConditions{};
    }
    return ExistingCollectionPreConditions{
        acquisition.getCollectionPtr()->uuid(),
        acquisition.getCollectionPtr()->isTimeseriesCollection(),
        acquisition.getCollectionPtr()->isNewTimeseriesWithoutView(),
        wasNssTranslatedToBuckets};
}

void checkAcquisitionAgainstPreConditions(const CollectionPreConditions& preConditions,
                                          const CollectionAcquisition& acquisition) {
    std::visit(
        OverloadedVisitor{
            [&](const NonExistentCollectionPreConditions&) {
                uassert(10685100,
                        "Collection did not exist at the beginning of operation but has "
                        "subsequently been created as a time-series collection",
                        !acquisition.exists() ||
                            !acquisition.getCollectionPtr()->isTimeseriesCollection());
            },
            [&](const ExistingCollectionPreConditions& preConditions) {
                uassert(
                    10685101,
                    fmt::format("Collection with ns {} has been dropped and recreated since the "
                                "beginning of the operation",
                                acquisition.nss().toStringForErrorMsg()),
                    preConditions.collectionUUID == acquisition.uuid() ||
                        (preConditions.isTimeseriesCollection ==
                             acquisition.getCollectionPtr()->isTimeseriesCollection() &&
                         preConditions.isViewlessTimeseriesCollection ==
                             acquisition.getCollectionPtr()->isNewTimeseriesWithoutView()));
            }},
        preConditions);
}
}  // namespace mongo::timeseries
