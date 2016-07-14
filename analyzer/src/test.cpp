// Copyright (C) 2009-2016 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#include "include/test.h"

//using namespace analyzer;

Test::Test()
{
}

Test::~Test(){}

void Test::hello(const char *fileName){
    //printf("Hello %s",fileName);
}

//manual template instantiation needed for wrapper!
//void Test::hello(const char *fileName);
