// Copyright (C) 2009-2016 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#include "test.h"
#include "single_task.h"
#include "Matrix.h"
#include <iostream>

//using namespace analyzer;

Test::Test()
{
}

Test::~Test(){}

void Test::hello(const char *fileName){
	std::cout << "Hello " << fileName << ": My Number from SYCL single_task "<<number()<<"\n";
	Matrix<> test{1,2,3,4,5,6,7,8,9};
}
