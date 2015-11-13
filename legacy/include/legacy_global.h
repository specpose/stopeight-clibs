// Copyright (C) 2009-2015 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#ifndef LEGACY_GLOBAL_H
#define LEGACY_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(LEGACY_LIBRARY)
#  define LEGACYSHARED_EXPORT Q_DECL_EXPORT
#else
#  define LEGACYSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // LEGACY_GLOBAL_H
