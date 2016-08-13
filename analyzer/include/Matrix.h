// Copyright (C) 2009-2016 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#include "analyzer_global.h"
#include "cl_platform.h"
#include <valarray>

template<typename datatype=cl_double> class Matrix {
public:
	Matrix(int dimensions);
	~Matrix();
private:
	std::valarray<datatype> elems;
	const int dimensions;
};

template class ANALYZERSHARED_EXPORT Matrix<cl_double>;