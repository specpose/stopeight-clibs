// Copyright (C) 2017 Fassio Blatter
// GNU Lesser General Public License, version 2.1

#include "stdafx.h"

#include <experimental/algorithm>
#include <experimental/impl/algorithm_impl.h>

#include "algo.h"
#include "iterators.h"

//double define
#include <experimental/execution_policy>

#include <vector>

// Taken from msvc symbol error
using vector_double = std::_Vector_iterator<std::_Vector_val<std::_Simple_types<double>>>;
using vector_pair = std::_Vector_iterator<std::_Vector_val<std::_Simple_types<std::pair<double,double>>>>;
//using fexec = std::experimental::parallel::parallel_vector_execution_policy;
#include "dummy.h"
using fexec = dummy;

//specialization
template <class ExecutionPolicy, class Iterator, class OutputIterator> void grapher::__calculate_rotations::operator()(ExecutionPolicy& task1, Iterator begin, Iterator end, OutputIterator begin2,std::random_access_iterator_tag)
{
	//binary,not unary
	std::transform(begin, end-1, begin+1, ++begin2, [](double a, double b) {
		return asin(b - a);
	});
}
template void grapher::__calculate_rotations::operator()(fexec& task1, vector_double begin, vector_double end, vector_double begin2,std::random_access_iterator_tag);

//specialization
template <class ExecutionPolicy, class Iterator, class OutputIterator> void grapher::__apply_rotation_matrix::operator()(ExecutionPolicy& task1, Iterator begin, Iterator end, OutputIterator begin2, std::forward_iterator_tag)
{
	//binary,not unary
	std::transform(begin, end, begin2,begin2, [](double rot, std::pair<double, double> vec) {
		double x = (cos(rot)*vec.first - sin(rot)*vec.second);
		double y = (sin(rot)*vec.first + cos(rot)*vec.second);
		std::pair<double, double> p{ x , y };
		return p;
	});
}
template void grapher::__apply_rotation_matrix::operator()(fexec& task1, vector_double begin, vector_double end, vector_pair begin2, std::forward_iterator_tag);

grapher::__add_vectors::__add_vectors(int samplesPerPixel) : _samplesPerPixel(samplesPerPixel) {
}
grapher::__add_vectors::~__add_vectors() {
}
//specialization
template <class ExecutionPolicy, class Iterator, class OutputIterator> void grapher::__add_vectors::operator()(ExecutionPolicy& task1, Iterator begin, Iterator end, OutputIterator begin2, std::random_access_iterator_tag)
{
	//make my own iterator, advancing samplesPerPixel
	stopeight::block_iterator<Iterator> block(begin,end,_samplesPerPixel);
	stopeight::block_iterator<Iterator> block_end(begin, begin, 1);
	//transform calculating some of each element+samplesPerPixel; requires randomaccess
	std::transform(block, block_end, begin2, [](std::pair<Iterator, Iterator> current_block) {
		std::pair<double, double> block_sum = std::accumulate(current_block.first, current_block.second, std::pair<double, double>{ 0.0f,0.0f }, [](std::pair<double, double> v1, std::pair<double, double> v2) {
			return std::pair<double, double>{v1.first+v2.first,v1.second+v2.second};
		});
		return block_sum;
	});


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
	//__calculate_rotations()(task1, begin, end, std::begin(rotations), typename std::iterator_traits<Iterator>::iterator_category{});
	__calculate_rotations()(task1, begin, end, std::begin(rotations), Iterator::iterator_category{});
	//buffer double pair; length of vector in x-direction depends on sampleRate and window-pixels; will be rotated below
	std::vector<std::pair<double, double>> vectors = std::vector<std::pair<double, double>>(size, std::pair<double,double>{1.0f / _samplesPerPixel, 0.0f} );
	//__apply_rotation_matrix
	__apply_rotation_matrix()(task1, std::begin(rotations), std::end(rotations), std::begin(vectors), Iterator::iterator_category{});
	//buffer double pair (shorter!)
	//__add_vectors(samplesPerPixel)
	std::vector<std::pair<double, double>> out_vectors = std::vector<std::pair<double, double>>(int((vectors.size() / _samplesPerPixel)+1), { double(0.0f), double(0.0f) });
	__add_vectors(_samplesPerPixel)(task1, std::begin(vectors), std::end(vectors), std::begin(out_vectors), Iterator::iterator_category{});
	//result_vector.shrink_to_fit
	//move output data to outputiterator
	std::copy<decltype(std::begin(vectors)),OutputIterator>(std::begin(out_vectors), std::end(out_vectors), begin2);
}
template void grapher::samples_To_VG::operator()(fexec& task1, vector_double begin, vector_double end, vector_pair begin2);
//template void grapher::samples_To_VG(dvect begin, dvect end, dvect begin2);