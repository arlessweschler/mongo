/* Provide a real file - not a symlink - as it would cause multiarch conflicts
   when multiple different arch releases are installed simultaneously.  */

#ifndef UNW_REMOTE_ONLY

#if defined __aarch64__
# include "tdep-aarch64/libunwind_i.h"
#elif defined __arm__
# include "tdep-arm/libunwind_i.h"
#elif defined __hppa__
# include "tdep-hppa/libunwind_i.h"
#elif defined __ia64__
# include "tdep-ia64/libunwind_i.h"
#elif defined __mips__
# include "tdep-mips/libunwind_i.h"
#elif defined __powerpc__ && !defined __powerpc64__
# include "tdep-ppc32/libunwind_i.h"
#elif defined __powerpc64__
# include "tdep-ppc64/libunwind_i.h"
#elif defined __sh__
# include "tdep-sh/libunwind_i.h"
#elif defined __i386__
# include "tdep-x86/libunwind_i.h"
#elif defined __x86_64__
# include "tdep-x86_64/libunwind_i.h"
#elif defined __s390x__
# include "tdep-s390x/libunwind_i.h"
#elif defined __riscv || defined __riscv__
# include "tdep-riscv/libunwind_i.h"
#elif defined __loongarch64
# include "tdep-loongarch64/libunwind_i.h"
#else
# error "Unsupported arch"
#endif


#else /* UNW_REMOTE_ONLY */

# include "tdep-aarch64/libunwind_i.h"

#endif /* UNW_REMOTE_ONLY */
