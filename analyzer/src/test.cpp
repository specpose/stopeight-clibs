// Copyright (C) 2009-2016 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#include "include/test.h"
#include <iostream>

//using namespace analyzer;

Test::Test()
{
}

Test::~Test(){}

void Test::hello(const char *fileName){
	std::cout << "Hello " << fileName << "Number from SYCL single_task "<<number()<<"\n";
	Matrix<> test = Matrix<>(3);
}
