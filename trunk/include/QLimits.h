
//
// C++ Interface: QLimits
//
// Description: 
//
//
// Author: John M. Drescher <drescherjm@gmail.com>, (C) 2009
//
// Copyright: See COPYING file that comes with this distribution
//
//

#ifndef __QLIMITS_H__
#define __QLIMITS_H__

/* Minimum of signed integral types.  */
# define INT8_MIN		(-128)
# define INT16_MIN		(-32767-1)
# define INT32_MIN		(-2147483647-1)
# define INT64_MIN		(-__INT64_C(9223372036854775807)-1)
/* Maximum of signed integral types.  */
# define INT8_MAX		(127)
# define INT16_MAX		(32767)
# define INT32_MAX		(2147483647)
# define INT64_MAX		(__INT64_C(9223372036854775807))

/* Maximum of unsigned integral types.  */
# define UINT8_MAX		(255)
# define UINT16_MAX		(65535)
# define UINT32_MAX		(4294967295U)
# define UINT64_MAX		(__UINT64_C(18446744073709551615))

#ifndef INT_MAX
#define INT_MAX INT32_MAX
#define INT_MIN INT32_MIN
#define UCHAR_MAX UINT8_MAX
#define USHRT_MAX UINT16_MAX
#define SHRT_MIN INT16_MIN
#define SHRT_MAX INT16_MAX

#define SCHAR_MIN INT16_MIN
#define SCHAR_MAX INT16_MAX
#endif //ndef INT_MAX

namespace QTUTILS {

const quint32 quint32_MAX = -1;
const quint32 quint32_MIN = 0;

}; // namespace QTUTILS
#endif //__QLIMITS_H__
