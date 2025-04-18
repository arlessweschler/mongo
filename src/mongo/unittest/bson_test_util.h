/**
 *    Copyright (C) 2018-present MongoDB, Inc.
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

#pragma once

// IWYU pragma: private, include "mongo/unittest/unittest.h"
// IWYU pragma: friend "mongo/unittest/.*"

#include <string>

#include "mongo/base/string_data.h"
#include "mongo/bson/bsonelement.h"
#include "mongo/bson/bsonobj.h"
#include "mongo/bson/simple_bsonelement_comparator.h"
#include "mongo/bson/simple_bsonobj_comparator.h"
#include "mongo/unittest/assert.h"
#include "mongo/unittest/inline_auto_update.h"

/**
 * BSON comparison utility macro. Do not use directly.
 */
#define ASSERT_BSON_COMPARISON(NAME, a, b, astr, bstr) \
    ::mongo::unittest::assertComparison_##NAME(__FILE__, __LINE__, astr, bstr, a, b)

/**
 * Use to compare two instances of type BSONObj under the default comparator in unit tests.
 */
#define ASSERT_BSONOBJ_EQ(a, b) ASSERT_BSON_COMPARISON(BSONObjEQ, a, b, #a, #b)
#define ASSERT_BSONOBJ_LT(a, b) ASSERT_BSON_COMPARISON(BSONObjLT, a, b, #a, #b)
#define ASSERT_BSONOBJ_LTE(a, b) ASSERT_BSON_COMPARISON(BSONObjLTE, a, b, #a, #b)
#define ASSERT_BSONOBJ_GT(a, b) ASSERT_BSON_COMPARISON(BSONObjGT, a, b, #a, #b)
#define ASSERT_BSONOBJ_GTE(a, b) ASSERT_BSON_COMPARISON(BSONObjGTE, a, b, #a, #b)
#define ASSERT_BSONOBJ_NE(a, b) ASSERT_BSON_COMPARISON(BSONObjNE, a, b, #a, #b)

/**
 * Use to compare two instances of type BSONObj with unordered fields in unit tests.
 */
#define ASSERT_BSONOBJ_EQ_UNORDERED(a, b) ASSERT_BSON_COMPARISON(BSONObjEQ_UNORDERED, a, b, #a, #b)
#define ASSERT_BSONOBJ_LT_UNORDERED(a, b) ASSERT_BSON_COMPARISON(BSONObjLT_UNORDERED, a, b, #a, #b)
#define ASSERT_BSONOBJ_LTE_UNORDERED(a, b) \
    ASSERT_BSON_COMPARISON(BSONObjLTE_UNORDERED, a, b, #a, #b)
#define ASSERT_BSONOBJ_GT_UNORDERED(a, b) ASSERT_BSON_COMPARISON(BSONObjGT_UNORDERED, a, b, #a, #b)
#define ASSERT_BSONOBJ_GTE_UNORDERED(a, b) \
    ASSERT_BSON_COMPARISON(BSONObjGTE_UNORDERED, a, b, #a, #b)
#define ASSERT_BSONOBJ_NE_UNORDERED(a, b) ASSERT_BSON_COMPARISON(BSONObjNE_UNORDERED, a, b, #a, #b)

/**
 * Use to compare two instances of type BSONElement under the default comparator in unit tests.
 */
#define ASSERT_BSONELT_EQ(a, b) ASSERT_BSON_COMPARISON(BSONElementEQ, a, b, #a, #b)
#define ASSERT_BSONELT_LT(a, b) ASSERT_BSON_COMPARISON(BSONElementLT, a, b, #a, #b)
#define ASSERT_BSONELT_LTE(a, b) ASSERT_BSON_COMPARISON(BSONElementLTE, a, b, #a, #b)
#define ASSERT_BSONELT_GT(a, b) ASSERT_BSON_COMPARISON(BSONElementGT, a, b, #a, #b)
#define ASSERT_BSONELT_GTE(a, b) ASSERT_BSON_COMPARISON(BSONElementGTE, a, b, #a, #b)
#define ASSERT_BSONELT_NE(a, b) ASSERT_BSON_COMPARISON(BSONElementNE, a, b, #a, #b)

#define ASSERT_BSONOBJ_BINARY_EQ(a, b) \
    ::mongo::unittest::assertComparison_BSONObjBINARY_EQ(__FILE__, __LINE__, #a, #b, a, b)

namespace mongo {
namespace unittest {

#define DECLARE_BSON_CMP_FUNC(BSONTYPE, NAME)                          \
    void assertComparison_##BSONTYPE##NAME(const std::string& theFile, \
                                           unsigned theLine,           \
                                           StringData aExpression,     \
                                           StringData bExpression,     \
                                           const BSONTYPE& aValue,     \
                                           const BSONTYPE& bValue);

DECLARE_BSON_CMP_FUNC(BSONObj, EQ);
DECLARE_BSON_CMP_FUNC(BSONObj, LT);
DECLARE_BSON_CMP_FUNC(BSONObj, LTE);
DECLARE_BSON_CMP_FUNC(BSONObj, GT);
DECLARE_BSON_CMP_FUNC(BSONObj, GTE);
DECLARE_BSON_CMP_FUNC(BSONObj, NE);

DECLARE_BSON_CMP_FUNC(BSONObj, EQ_UNORDERED);
DECLARE_BSON_CMP_FUNC(BSONObj, LT_UNORDERED);
DECLARE_BSON_CMP_FUNC(BSONObj, LTE_UNORDERED);
DECLARE_BSON_CMP_FUNC(BSONObj, GT_UNORDERED);
DECLARE_BSON_CMP_FUNC(BSONObj, GTE_UNORDERED);
DECLARE_BSON_CMP_FUNC(BSONObj, NE_UNORDERED);

DECLARE_BSON_CMP_FUNC(BSONObj, BINARY_EQ);

DECLARE_BSON_CMP_FUNC(BSONElement, EQ);
DECLARE_BSON_CMP_FUNC(BSONElement, LT);
DECLARE_BSON_CMP_FUNC(BSONElement, LTE);
DECLARE_BSON_CMP_FUNC(BSONElement, GT);
DECLARE_BSON_CMP_FUNC(BSONElement, GTE);
DECLARE_BSON_CMP_FUNC(BSONElement, NE);
#undef DECLARE_BSON_CMP_FUNC

/**
 * Given a BSONObj, return a string that wraps the json form of the BSONObj with
 * `fromjson(R"(<>)")`.
 */
std::string formatJsonStr(const std::string& obj);

#define ASSERT_BSONOBJ_EQ_AUTO(expected, actual)                                     \
    ASSERT(AUTO_UPDATE_HELPER(::mongo::unittest::formatJsonStr(expected),            \
                              ::mongo::unittest::formatJsonStr(actual.jsonString()), \
                              false))
}  // namespace unittest
}  // namespace mongo
