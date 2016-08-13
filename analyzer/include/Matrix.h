// Copyright (C) 2009-2016 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#include "analyzer_global.h"
//#include "cl_platform.h"

template<typename datatype=double> class Matrix {
public:
	Matrix(int dimensions);
	~Matrix();
private:
	datatype* elem;
	const int dimensions;
};

template class ANALYZERSHARED_EXPORT Matrix<double>;