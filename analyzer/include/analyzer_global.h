// Copyright (C) 2009-2016 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#ifndef ANALYZER_GLOBAL_H
#define ANALYZER_GLOBAL_H


#if defined(_WIN32) || defined(_WIN64) || defined(WIN32) || defined(WIN64)
//  Microsoft
#if defined(ANALYZER_LIBRARY)
#define ANALYZERSHARED_EXPORT __declspec(dllexport)
#else
#define ANALYZERSHARED_EXPORT __declspec(dllimport)
#endif
#elif defined(__linux__) || defined(UNIX) || defined(__unix__) || defined(LINUX)
//  GCC
#if defined(ANALYZER_LIBRARY)
#  define ANALYZERSHARED_EXPORT
//#  define ANALYZERSHARED_EXPORT Q_DECL_EXPORT
#else
#  define ANALYZERSHARED_EXPORT
//#  define ANALYZERSHARED_EXPORT Q_DECL_IMPORT
#endif
#else
//  do nothing and hope for the best?
#define ANALYZERSHARED_EXPORT
#pragma WARNING: Unknown dynamic link import/export semantics.
#endif

#endif // ANALYZER_GLOBAL_H
