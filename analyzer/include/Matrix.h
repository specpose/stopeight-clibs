// Copyright (C) 2009-2016 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#include "analyzer_global.h"
#include "cl_platform.h"
#include <valarray>

/*
	A square, row-major, dense matrix
*/

template<typename datatype=cl_double> class Matrix {
public:
	Matrix(int dimensions);
	Matrix(std::initializer_list<datatype> list);
	~Matrix();
	int dimensions() { return sqrt(elems.size()); };
private:
	std::valarray<datatype> elems;
};

template class ANALYZERSHARED_EXPORT Matrix<cl_double>;