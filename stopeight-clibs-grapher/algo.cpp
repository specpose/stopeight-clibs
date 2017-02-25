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
using vector_float = std::_Vector_iterator<std::_Vector_val<std::_Simple_types<float>>>;
using vector_pair = std::_Vector_iterator<std::_Vector_val<std::_Simple_types<std::pair<float,float>>>>;
//using fexec = std::experimental::parallel::parallel_vector_execution_policy;
#include "dummy.h"
using fexec = dummy;

//specialization
template <class ExecutionPolicy, class Iterator, class OutputIterator> void grapher::__calculate_rotations::operator()(ExecutionPolicy& task1, Iterator begin, Iterator end, OutputIterator begin2,std::random_access_iterator_tag)
{
	//binary,not unary
	std::transform(begin, end-1, begin+1, ++begin2, [](float a, float b) {
		return asin(b - a);
	});
}
template void grapher::__calculate_rotations::operator()(fexec& task1, vector_float begin, vector_float end, vector_float begin2,std::random_access_iterator_tag);

//specialization
template <class ExecutionPolicy, class Iterator, class OutputIterator> void grapher::__apply_rotation_matrix::operator()(ExecutionPolicy& task1, Iterator begin, Iterator end, OutputIterator begin2, std::forward_iterator_tag)
{
	//binary,not unary
	std::transform(begin, end, begin2,begin2, [](double rot, std::pair<double, double> vec) {
		double x = (cos(rot)*vec.first - sin(rot)*vec.first);
		double y = (sin(rot)*vec.second + cos(rot)*vec.second);
		std::pair<double, double> p{ x , y };
		return p;
	});
}
template void grapher::__apply_rotation_matrix::operator()(fexec& task1, vector_float begin, vector_float end, vector_pair begin2, std::forward_iterator_tag);

grapher::__add_vectors::__add_vectors(int samplesPerPixel) : _samplesPerPixel(samplesPerPixel) {
}
grapher::__add_vectors::~__add_vectors() {
}
//specialization
template <class ExecutionPolicy, class Iterator, class OutputIterator> void grapher::__add_vectors::operator()(ExecutionPolicy& task1, Iterator begin, Iterator end, OutputIterator begin2, std::random_access_iterator_tag)
{
	//make my own iterator, advancing samplesPerPixel

	//transform calculating some of each element+samplesPerPixel; requires randomaccess


	//replace every vector with sum of precedings up to limit
	//std::transform(begin, end, begin2, __length_sum(_samplesPerPixel));
	//remove every vector below limit
}
template void grapher::__add_vectors::operator()(fexec& task1, vector_pair begin, vector_pair end, vector_pair begin2, std::random_access_iterator_tag);

grapher::samples_To_VG::samples_To_VG(int samplesPerPixel) : _samplesPerPixel(samplesPerPixel) {
}
grapher::samples_To_VG::~samples_To_VG() {
}
template <class ExecutionPolicy, class Iterator, class OutputIterator> void grapher::samples_To_VG::operator()(ExecutionPolicy& task1, Iterator begin, Iterator end, OutputIterator begin2)
{
	//par
	//std::experimental::parallel::transform(task1, begin, end, begin, [](float f) {return 3.3f; });
	//buffer double single
	size_t size = std::distance(begin, end);
	std::vector<double> rotations = std::vector<double>(size,0.0f);
	//__calculate_rotations
	//__calculate_rotations()(task1, begin, end, std::begin(b1), typename std::iterator_traits<decltype(begin)>::iterator_category{});
	__calculate_rotations()(task1, begin, end, std::begin(rotations), Iterator::iterator_category{});
	//buffer double pair; length of vector in x-direction depends on sampleRate and window-pixels; will be rotated below
	std::vector<std::pair<double, double>> vectors = std::vector<std::pair<double, double>>(size, {1 / _samplesPerPixel, 0.0f} );
	//__apply_rotation_matrix
	__apply_rotation_matrix()(task1, std::begin(rotations), std::end(rotations), std::begin(vectors), Iterator::iterator_category{});
	//buffer double pair (shorter!)
	//__add_scalars(samplesPerPixel)
	//move output data to outputiterator
	std::copy<decltype(std::begin(vectors)),OutputIterator>(std::begin(vectors), std::end(vectors), begin2);
}
template void grapher::samples_To_VG::operator()(fexec& task1, vector_float begin, vector_float end, vector_pair begin2);
//template void grapher::samples_To_VG(dvect begin, dvect end, dvect begin2);