#pragma once

#if QT_VERSION >= QT_VERSION_CHECK(5, 14, 0)
#define qt_endl Qt::endl
#else
#define qt_endl endl
#endif
