// Copyright (C) 2009-2016 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#include "include/Matrix.h"
#include <iostream>

template<typename datatype> Matrix<datatype>::Matrix(int dimensions) : elem(new datatype[dimensions]), dimensions(dimensions){
	std::cout << "const dimensions is " << this->dimensions << "\n";
}

template<typename datatype> Matrix<datatype>::~Matrix() { delete[] elem; }