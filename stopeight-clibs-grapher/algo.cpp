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

grapher::__calculate_rotations::__calculate_rotations() {
}
grapher::__calculate_rotations::~__calculate_rotations() {
}
template <class ExecutionPolicy, class Iterator, class OutputIterator> void grapher::__calculate_rotations::operator()(ExecutionPolicy& task1, Iterator begin, Iterator end, OutputIterator begin2)
{
	//binary,not unary
	Iterator lookahead = begin;
	std::transform(begin, end-1, ++lookahead, ++begin2, [](float a, float b) {
		return asin(b - a);
		//		return 3.3f; 
	});
}
template void grapher::__calculate_rotations::operator()(fexec& task1, fvect begin, fvect end, fvect begin2);


grapher::samples_To_VG::samples_To_VG(int samplesPerPixel) : _samplesPerPixel(samplesPerPixel) {
}
grapher::samples_To_VG::~samples_To_VG() {
}
template <class ExecutionPolicy, class Iterator, class OutputIterator> void grapher::samples_To_VG::operator()(ExecutionPolicy& task1, Iterator begin, Iterator end, OutputIterator begin2)
{
	//par
	//std::experimental::parallel::transform(task1, begin, end, begin, [](float f) {return 3.3f; });
	//std::transform(begin, end, begin2, [](float f) {return f*3.3f; });
	//buffer double single
	size_t size = std::distance(begin, end);
	std::vector<Iterator::value_type> b1 = std::vector<Iterator::value_type>(size);
	//__calculate_rotations
	std::fill(std::begin(b1), std::end(b1), 7.0f);
	__calculate_rotations()(task1, begin, end, std::begin(b1));
	//buffer double pair
	//__apply_rotation_matrix
	//buffer double pair (shorter!)
	//__add_scalars(samplesPerPixel)
	//move output data to outputiterator
	std::copy<Iterator,OutputIterator>(std::begin(b1), std::end(b1), begin2);
}
template void grapher::samples_To_VG::operator()(fexec& task1, fvect begin, fvect end, fvect begin2);
//template void grapher::samples_To_VG(dvect begin, dvect end, dvect begin2);