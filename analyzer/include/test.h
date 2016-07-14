// Copyright (C) 2009-2016 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#ifndef TEST_H
#define TEST_H

#include "analyzer_global.h"

class Test
{
public:
    Test();
    ~Test();

    // method for access from python
    static void hello(const char* fileName);

};

#endif // TEST_H
