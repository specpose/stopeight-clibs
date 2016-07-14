// Copyright (C) 2009-2016 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#ifndef ANALYZER_GLOBAL_H
#define ANALYZER_GLOBAL_H

#if defined(ANALYZER_LIBRARY)
#  define ANALYZERSHARED_EXPORT Q_DECL_EXPORT
#else
#  define ANALYZERSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // ANALYZER_GLOBAL_H
