// Copyright (C) 2017 Fassio Blatter
// GNU Lesser General Public License, version 2.1

#include "stdafx.h"

#include <experimental/algorithm>
#include <experimental/impl/algorithm_impl.h>

#include "algo.h"

//double define
#include <experimental/execution_policy>
#include <vector>

// Taken from msvc symbol error
using fvect = std::_Vector_iterator<std::_Vector_val<std::_Simple_types<float>>>;
//using fexec = std::experimental::parallel::parallel_vector_execution_policy;
#include "dummy.h"
using fexec = dummy;

grapher::samples_To_VG::samples_To_VG(int samplesPerPixel) : _samplesPerPixel(samplesPerPixel) {
}

grapher::samples_To_VG::~samples_To_VG() {
}

template <class ExecutionPolicy, class Iterator, class OutputIterator> void grapher::samples_To_VG::operator()(ExecutionPolicy& task1, Iterator begin, Iterator end, OutputIterator begin2)
{
	//par
	//sycl::impl::transform(task1_sub1, begin, end,begin2, [](float f) {return 3.3f; });//its doing queue stuff internally -> not sycl inside sycl
	//std::experimental::parallel::transform(task1, begin, end, begin, [](float f) {return 3.3f; });
	std::transform(begin, end, begin, [](float f) {return 3.3f; });
}
template void grapher::samples_To_VG::operator()(fexec& task1, fvect begin, fvect end, fvect begin2);
//template void grapher::samples_To_VG(dvect begin, dvect end, dvect begin2);