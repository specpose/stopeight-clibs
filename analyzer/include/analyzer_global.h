// Copyright (C) 2009-2016 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#ifndef ANALYZER_GLOBAL_H
#define ANALYZER_GLOBAL_H

#ifdef _WIN32 || _WIN64
#if defined(ANALYZER_LIBRARY)
#  define ANALYZERSHARED_EXPORT __declspec(dllexport)
#else
#  define ANALYZERSHARED_EXPORT __declspec(dllimport)
#endif
#else
#if defined(ANALYZER_LIBRARY)
#  define ANALYZERSHARED_EXPORT
#else
#  define ANALYZERSHARED_EXPORT
#endif
#endif

#endif // ANALYZER_GLOBAL_H
