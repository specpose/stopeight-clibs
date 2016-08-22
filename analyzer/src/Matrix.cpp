// Copyright (C) 2009-2016 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#include "include/Matrix.h"
#include <iostream>
#include <functional>

template<typename datatype> Matrix<datatype>::Matrix(int dim) : elems(CL_DBL_MIN,dim*dim) {
	std::cout << "dimensions is " << dimensions() << "\n";
	
}

template<typename datatype> Matrix<datatype>::Matrix(std::initializer_list<datatype> list) {
	elems = std::valarray<datatype>{ list };
	//const size_t indexes[]{ 2,5,8 };
	size_t indexes[dimensions()];
	//for (int i; i < list.size(); ++i) {
	//	indexes << std::modulus<int>((i+1) / dimensions());

	//	if ((i+1)%dimensions() == 0) {
	//		indexes[i] = i;
	//	}
	//}
	//std::valarray<datatype> elems2 = elems[std::valarray<size_t>(indexes, dimensions())];
	for (auto i : indexes) std::cout << i<< ", ";
	std::cout << "\n";
}

template<typename datatype> Matrix<datatype>::~Matrix() { elems.~valarray(); }