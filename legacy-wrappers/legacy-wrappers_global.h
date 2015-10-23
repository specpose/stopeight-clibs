#ifndef LEGACYWRAPPERS_GLOBAL_H
#define LEGACYWRAPPERS_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(LEGACYWRAPPERS_LIBRARY)
#  define LEGACYWRAPPERSSHARED_EXPORT Q_DECL_EXPORT
#else
#  define LEGACYWRAPPERSSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // LEGACYWRAPPERS_GLOBAL_H
