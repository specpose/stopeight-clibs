// Copyright (C) 2017 Fassio Blatter
// GNU Lesser General Public License, version 2.1

#include "stdafx.h"

#include <experimental/algorithm>//CYCLIC DEPENDENCY
#include "shared_types.h"//CYCLIC DEPENDENCY
#include <experimental/impl/algorithm_impl.h>

#include "algo.h"
#include "containers.h"

//double define
#include <experimental/execution_policy>

#include <vector>

using it_element = std::pair<typename std::vector<sp::element>::iterator, typename std::vector<sp::element>::iterator>;

using vector_single = std::_Vector_iterator<std::_Vector_val<std::_Simple_types<double>>>;
using vector_pair = std::_Vector_iterator<std::_Vector_val<std::_Simple_types<sp::element>>>;

using vector_vectors = std::_Vector_iterator<std::_Vector_val<std::_Simple_types<it_element>>>;
//using fexec = std::experimental::parallel::parallel_vector_execution_policy;
#include "dummy.h"
using fexec = dummy;

template <class ExecutionPolicy, class Iterator> double grapher::__average::operator()(ExecutionPolicy& task1, Iterator begin, Iterator end, std::forward_iterator_tag)
{
	return std::accumulate(begin, end, 0.0f)/std::distance(begin,end);
}
template double grapher::__average::operator()(fexec& task1, vector_single begin, vector_single end, std::forward_iterator_tag);


grapher::__calculate_rotations::__calculate_rotations(double average_df) : average_df(average_df) {

}
grapher::__calculate_rotations::~__calculate_rotations() {

}
template <class ExecutionPolicy, class Iterator, class OutputIterator> void grapher::__calculate_rotations::operator()(ExecutionPolicy& task1, Iterator begin, Iterator end, OutputIterator begin2, std::random_access_iterator_tag)
{
	//binary,not unary
	auto av = this->average_df;
	std::transform(begin, end-1, ++begin2, [av](double diff) {
		//rotations are absolute:
		return 300*asin(diff);

		//rotations are relative:
		//return atan(diff/av);
	});
}
template void grapher::__calculate_rotations::operator()(fexec& task1, vector_single begin, vector_single end, vector_single begin2, std::random_access_iterator_tag);

template <class ExecutionPolicy, class Iterator, class OutputIterator> void grapher::__apply_rotation_matrix::operator()(ExecutionPolicy& task1, Iterator begin, Iterator end, OutputIterator begin2, std::forward_iterator_tag)
{
	//rotations are absolute, not relative to previous vector(prerotate to previous, THEN apply rotation)?!
	//binary,not unary
	std::transform(begin, end, begin2, begin2, [](double rot, sp::element vec) {
		double x = (cos(rot)*vec.first - sin(rot)*vec.second);
		double y = (sin(rot)*vec.first + cos(rot)*vec.second);
		sp::element p{ x , y };
		return p;
	});
}
template void grapher::__apply_rotation_matrix::operator()(fexec& task1, vector_single begin, vector_single end, vector_pair begin2, std::forward_iterator_tag);

template <class ExecutionPolicy, class Iterator, class OutputIterator> void grapher::_sum_blocks::operator()(ExecutionPolicy& task1, Iterator begin, Iterator end, OutputIterator begin2, std::random_access_iterator_tag)
{

	std::transform(begin, end, begin2, [](it_element block) {
		//both can be nonempty; preserve type of last
		if (block.first != block.second) {
			return std::accumulate(block.first, block.second, sp::element{ 0.0f,0.0f }, [](sp::element v1, sp::element v2) {
				v2 += v1;
				return v2;
			});
		}
		else {
			return *block.first;//second could be last+1
		}
	});
}
template void grapher::_sum_blocks::operator()(fexec& task1, vector_vectors begin, vector_vectors end, vector_pair begin2, std::random_access_iterator_tag);

template <class ExecutionPolicy, class Iterator, class OutputIterator> void grapher::_append::operator()(ExecutionPolicy& task1, Iterator begin, Iterator end, OutputIterator begin2, std::forward_iterator_tag)
{
	class my_add {
	public:
		my_add() : cache(sp::element{0.0f,0.0f}) {};
		sp::element operator()(sp::element e) {
			auto newvalue = e;//type preserved
			newvalue += cache;//type preserved
			cache += e;//type mutating
			return newvalue;
		};
	private:
		sp::element cache;
	};
	std::transform(begin, end, begin2, my_add());
}
template void grapher::_append::operator()(fexec& task1, vector_pair begin, vector_pair end, vector_pair begin2, std::forward_iterator_tag);

int grapher::samples_To_VG_vectorSize(int inputSize, int samplesPerVector) {
	return stopeight::blocks<sp::element>::calculateSize(inputSize,samplesPerVector);
}

double grapher::samples_To_VG_vectorLength(int showSamples, double unitaryLength) {
	return unitaryLength / showSamples;
}

grapher::samples_To_VG::samples_To_VG(int samplesPerVector,double vectorLength, std::vector<int> fixPoints_indices, double contextAverage)
	: _samplesPerVector(samplesPerVector)
	, _vectorLength(vectorLength)
	, _fixPoint_indices(fixPoints_indices)
	, _contextAverage(contextAverage) {
}
grapher::samples_To_VG::~samples_To_VG() {
}
template <class ExecutionPolicy, class Iterator, class OutputIterator> void grapher::samples_To_VG::operator()(ExecutionPolicy& task1, Iterator begin, Iterator end, OutputIterator begin2)
{
	//par
	//std::experimental::parallel::transform(task1, begin, end, begin, [](float f) {return 3.3f; });

	size_t size = std::distance(begin, end);
	std::vector<double> differences = std::vector<double>(size, 0.0f);
	std::adjacent_difference(begin, end, std::begin(differences));
	*std::begin(differences) = 0.0f;

	if (_contextAverage==0.0f)//HACK for avoiding duplicate function call in init
		_contextAverage = __average()(task1, ++std::begin(differences), std::end(differences), Iterator::iterator_category{});

	std::vector<double> rotations = std::vector<double>(size, 0.0f);
	__calculate_rotations(_contextAverage)(task1, std::begin(differences), std::end(differences), std::begin(rotations), Iterator::iterator_category{});

	std::vector<sp::element> vectors = std::vector<sp::element>(size, sp::element{ _vectorLength, 0.0f});
	__apply_rotation_matrix()(task1, std::begin(rotations), std::end(rotations), std::begin(vectors), Iterator::iterator_category{});

	std::vector<std::vector<sp::element>> vectors_sliced = std::vector<std::vector<sp::element>>{};
	//after append, but before blocks
	//fixpoints; needs container access
	int i = 0;
	for (auto index : _fixPoint_indices) {

		//pre-fixpoint
		if (index > 0) {
			std::vector<sp::element> v = std::vector<sp::element>(index - i);
			std::move(std::begin(vectors)+i, std::begin(vectors)+index, std::begin(v));
			vectors_sliced.push_back(v);
		}

		//make it a fixPoint
		vectors.at(index) = sp::turn<double>(std::move(vectors.at(index)));

		//Note: last can not be fixPoint
		if (index < std::distance(std::begin(vectors), std::end(vectors))) {
			//append point following to mini segment
			int pointFollowingFixpoint = index +1;
			std::vector<sp::element> v = std::vector<sp::element>((pointFollowingFixpoint)-index);
			std::move(std::begin(vectors) + index, std::begin(vectors) + (pointFollowingFixpoint), std::begin(v));
			vectors_sliced.push_back(v);
			i = pointFollowingFixpoint;//point following fixpoint is needed for rotation
		}
		else {
			i = index;
		}
	}
	if (i < (vectors.size())) {
		std::vector<sp::element> v = std::vector<sp::element>(vectors.size() - i);
		std::move(std::begin(vectors) + i, std::end(vectors), std::begin(v));
		vectors_sliced.push_back(v);
	}

	std::vector<sp::element> out_vectors = std::vector<sp::element>{};
	for (auto v : vectors_sliced) {
		stopeight::blocks<sp::element> blocks_vector = stopeight::blocks<sp::element>(std::move(v), _samplesPerVector);

		std::vector<sp::element> ov = std::vector<sp::element>(blocks_vector.size(), { double(0.0f), double(0.0f) });
		std::fill<typename std::vector<sp::element>::iterator>(std::begin(ov), std::end(ov), sp::element{ 1.0f, 1.0f });

		_sum_blocks()(task1, std::begin(blocks_vector), std::end(blocks_vector), std::begin(ov), Iterator::iterator_category{});
		std::move(std::begin(ov), std::end(ov), std::back_inserter(out_vectors));
	}

	_append()(task1, std::begin(out_vectors), std::end(out_vectors), std::begin(out_vectors), Iterator::iterator_category{});

	std::copy<typename std::vector<sp::element>::iterator, OutputIterator>(std::begin(out_vectors), std::end(out_vectors), begin2);
}
template void grapher::samples_To_VG::operator()(fexec& task1, vector_single begin, vector_single end, vector_pair begin2);