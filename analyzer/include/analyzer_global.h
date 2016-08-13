// Copyright (C) 2009-2016 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#ifndef ANALYZER_GLOBAL_H
#define ANALYZER_GLOBAL_H

#if _MSC_VER && !__INTEL_COMPILER // COMPILER
//  Microsoft
#define ANALYZERSHARED_EXPORT __declspec(dllexport)
#else // COMPILER
//  do nothing and hope for the best?
#define ANALYZERSHARED_EXPORT
#pragma WARNING: Unknown dynamic link import/export semantics.
#endif // COMPILER

#endif // ANALYZER_GLOBAL_H
