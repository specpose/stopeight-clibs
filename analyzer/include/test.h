// Copyright (C) 2009-2016 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#ifndef TEST_H
#define TEST_H

#include "analyzer_global.h"
#include "single_task.h"

class Test
{
public:
	__declspec(dllexport) Test();
	__declspec(dllexport) ~Test();

    // method for access from python
	__declspec(dllexport) static void hello(const char* fileName);

};

//class ANALYZERSHARED_EXPORT Test;

#endif // TEST_H
