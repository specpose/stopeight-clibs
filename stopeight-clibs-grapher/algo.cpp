// Copyright (C) 2017 Fassio Blatter
// GNU Lesser General Public License, version 2.1

#include "stdafx.h"

#include <experimental/algorithm>//CYCLIC DEPENDENCY
#include "shared_types.h"//CYCLIC DEPENDENCY
#include <experimental/impl/algorithm_impl.h>

#include "algo.h"
#include "containers.h"
//#include "iterators.h"

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

template <class ExecutionPolicy, class Iterator, class OutputIterator> void grapher::__differences::operator()(ExecutionPolicy& task1, Iterator begin, Iterator end, OutputIterator begin2)
{
	std::adjacent_difference(begin, end, begin2);
	//*std::begin(differences) = 0.0f;
}
template void grapher::__differences::operator()(fexec& task1, vector_single begin, vector_single end, vector_single begin2);

template <class Iterator> double grapher::__average::operator()(Iterator begin, Iterator end)
{
	auto sum = std::accumulate(begin, end, 0.0f, [](double first, double second) {
		return first += abs(second);

	});
	return sum / std::distance(begin, end);
}
template double grapher::__average::operator()(vector_single begin, vector_single end);

template <class ExecutionPolicy, class Iterator, class OutputIterator> void grapher::__calculate_rotations::operator()(ExecutionPolicy& task1, Iterator begin, Iterator end, OutputIterator begin2, grapher::angle& angleFunction, std::forward_iterator_tag itag)
{
	std::transform(begin, end, begin2, [&angleFunction](double diff) {
		return angleFunction(diff);
	});
}
template void grapher::__calculate_rotations::operator()(fexec& task1, vector_single begin, vector_single end, vector_single begin2, grapher::angle& angleFunction, std::forward_iterator_tag itag);

/*template <class ExecutionPolicy, class Iterator, class OutputIterator> void grapher::__calculate_rotations::operator()(ExecutionPolicy& task1, Iterator begin, Iterator end, OutputIterator begin2, grapher::averageScaled& angleFunction, std::forward_iterator_tag itag)
{
	std::transform(begin, end, begin2, [&angleFunction](double diff) {
		return angleFunction(diff);
	});
}
template void grapher::__calculate_rotations::operator()(fexec& task1, vector_single begin, vector_single end, vector_single begin2, grapher::averageScaled& angleFunction, std::forward_iterator_tag itag);*/

template <class ExecutionPolicy, class Iterator, class OutputIterator> void grapher::__apply_rotation_matrix::operator()(ExecutionPolicy& task1, Iterator begin, Iterator end, OutputIterator begin2)
{
	OutputIterator begin2_c = begin2;
	//std::for_each(begin, end,[&begin2](double rot, sp::element vec) {
	//binary,not unary
	std::transform(begin, end, begin2, begin2, [](double rot, sp::element vec) {
		double x = (cos(rot)*vec.first - sin(rot)*vec.second);
		double y = (sin(rot)*vec.first + cos(rot)*vec.second);
		//double x = (cos(rot)*begin2->first - sin(rot)*begin2->second);
		//double y = (sin(rot)*begin2->first + cos(rot)*begin2->second);
		sp::element p{ x , y };
		return p;
		//*begin2++ = p;
	});
}
template void grapher::__apply_rotation_matrix::operator()(fexec& task1, vector_single begin, vector_single end, vector_pair begin2);

grapher::_fixpoints::_fixpoints(std::vector<int>& points) : _fixPoint_indices(points) {

}
grapher::_fixpoints::~_fixpoints() {

}
template <class ExecutionPolicy, class Iterator, class OutputIterator> void grapher::_fixpoints::operator()(ExecutionPolicy& task1, Iterator begin, Iterator end, OutputIterator begin2, std::random_access_iterator_tag)
{
	//remove all illegal fixpoint_indices
	//Note: last can not be fixPoint
	const auto vectors_size = std::distance(begin, end);
	std::remove_if(std::begin(_fixPoint_indices), std::end(_fixPoint_indices), [vectors_size](int index) {
		if ((index >= (vectors_size - 1)) || (index == 0))
			return true;
		return false;
	});
	//make it a fixPoint
	for (auto index : _fixPoint_indices) {
		*(begin + index) = sp::turn<double>(std::move(*(begin + index)));
	}
	std::vector<std::pair<int, int>> slices = std::vector<std::pair<int, int>>{};
	class prev {
	public:
		prev() : _prev(0) {};
		std::pair<int, int> operator()(int curr) {
			auto result = std::pair<int, int>{ _prev,curr };
			_prev = curr + 1;
			return result;
		};
	private:
		int _prev;
	};
	auto it = std::back_inserter(slices);
	std::for_each(std::begin(_fixPoint_indices), std::end(_fixPoint_indices), [&it](auto index) {
		*it++ = (prev()(index));//was index
		*it++ = (std::pair<int, int>{index, index + 1});//was index+1
	});
	//tail end
	std::pair<int, int> last = std::pair<int, int>{ 0,vectors_size };
	if (vectors_size > 0) {
		last = std::pair<int, int>{ _fixPoint_indices.back() + 1, vectors_size };// was _fixPoint_indices.back() + 1
	}
	*it++ = (last);
	std::transform(std::begin(slices), std::end(slices), begin2, [begin](std::pair<int, int> p) {
		it_element e = it_element{ (begin + p.first),(begin + p.second) };
		return e;
	});
}
template void grapher::_fixpoints::operator()(fexec& task1, vector_pair begin, vector_pair end, vector_vectors begin2, std::random_access_iterator_tag);

grapher::_blocks::_blocks(int samplesPerVector) : _samplesPerVector(samplesPerVector) {

}
grapher::_blocks::~_blocks() {

}
template <class ExecutionPolicy, class Iterator, class OutputIterator> void grapher::_blocks::operator()(ExecutionPolicy& task1, Iterator begin, Iterator end, OutputIterator begin2, std::random_access_iterator_tag)
{
	auto spV = _samplesPerVector;
	std::for_each(begin, end, [&begin2, spV](it_element slice) {
		auto size = std::distance(slice.first, slice.second);
		if (size > 0) {
			auto sectionend = (spV > size) ? size : spV;
			for (int i = 0; i < (size / sectionend); i++) {
				*begin2++ = (it_element{ (slice.first + (i*sectionend)),(slice.first + (i*sectionend) + sectionend) });
			}
			auto remainder = size%sectionend;
			if (remainder != 0)
				*begin2++ = (it_element{ (slice.second - remainder),slice.second });
		}
		else {
			*begin2++ = (it_element{ slice.first, slice.first });
		}
	});
}
template void grapher::_blocks::operator()(fexec& task1, vector_vectors begin, vector_vectors end, vector_vectors begin2, std::random_access_iterator_tag);


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
		my_add() : cache(sp::element{ 0.0f,0.0f }) {};
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

grapher::__differences_To_VG::__differences_To_VG(int samplesPerVector, double vectorLength, std::vector<int> fixPoints_indices)
	: _samplesPerVector(samplesPerVector)
	, _vectorLength(vectorLength)
	, _fixPoint_indices(fixPoints_indices)
{
}
grapher::__differences_To_VG::~__differences_To_VG() {
}
//partial specialization
template <class ExecutionPolicy, class Iterator, class OutputIterator, class UnaryFunction> void grapher::__differences_To_VG::operator()(ExecutionPolicy& task1, Iterator begin, Iterator end, OutputIterator begin2, UnaryFunction& angleFunction)
{
	//par
	//std::experimental::parallel::transform(task1, begin, end, begin, [](float f) {return 3.3f; });

	std::vector<double> rotations;
	//first one is invalid
	__calculate_rotations()(task1, begin, end, std::back_inserter(rotations), angleFunction, Iterator::iterator_category{});

	std::vector<sp::element> vectors;
	std::fill_n(std::back_inserter(vectors), std::distance(std::begin(rotations), std::end(rotations)), sp::element{ _vectorLength, 0.0f });
	__apply_rotation_matrix()(task1, std::begin(rotations), std::end(rotations), std::begin(vectors));

	std::vector<it_element> vectors_sliced;
	_fixpoints(_fixPoint_indices)(task1, std::begin(vectors), std::end(vectors), std::back_inserter(vectors_sliced), Iterator::iterator_category{});

	std::vector<sp::element> out_vectors;
	
	/*
	//HERESTART
	std::vector<it_element> blocks;
	_blocks(_samplesPerVector)(task1, std::begin(vectors_sliced), std::end(vectors_sliced), std::back_inserter(blocks), Iterator::iterator_category{});

	std::vector<sp::element> sums;
	_sum_blocks()(task1, std::begin(blocks), std::end(blocks), std::back_inserter(sums), Iterator::iterator_category{});

	std::move(std::begin(sums), std::end(sums), std::back_inserter(out_vectors));
	//HEREEND
	*/

	//hierarchy all to 1
	//std::transform(std::begin(vectors_sliced), std::end(vectors_sliced), std::back_inserter(out_vectors), [_samplesPerVector](decltype(vectors_sliced) v) {
	for (auto v : vectors_sliced) {
		stopeight::blocks<sp::element> blocks_vector = stopeight::blocks<sp::element>(v, _samplesPerVector);
		//std::move(slice), _samplesPerVector);

		std::vector<sp::element> ov = std::vector<sp::element>{};//(blocks_vector.size(), { double(0.0f), double(0.0f) });
																 //std::fill<typename std::vector<sp::element>::iterator>(std::begin(ov), std::end(ov), sp::element{ 1.0f, 1.0f });

		_sum_blocks()(task1, std::begin(blocks_vector), std::end(blocks_vector), std::back_inserter(ov), Iterator::iterator_category{});
		std::move(std::begin(ov), std::end(ov), std::back_inserter(out_vectors));
	}
	//});

	_append()(task1, std::begin(out_vectors), std::end(out_vectors), std::begin(out_vectors), Iterator::iterator_category{});

	std::copy<typename std::vector<sp::element>::iterator, OutputIterator>(std::begin(out_vectors), std::end(out_vectors), begin2);
}
//template void grapher::__differences_To_VG::operator()(fexec& task1, vector_single begin, vector_single end, vector_pair begin2, plainAngle& angleFunction);
//template void grapher::__differences_To_VG::operator()(fexec& task1, vector_single begin, vector_single end, vector_pair begin2, test2& angleFunction);


int grapher::samples_To_VG_vectorSize(int inputSize, int samplesPerVector) {
	auto size = inputSize / samplesPerVector;
	if (inputSize%samplesPerVector > 0)
		size++;
	return size;
	//return stopeight::blocks<sp::element>::calculateSize(inputSize, samplesPerVector);
}

double grapher::samples_To_VG_vectorLength(int showSamples, double unitaryLength) {
	return unitaryLength / showSamples;
}

grapher::samples_To_VG::samples_To_VG(int samplesPerVector, double vectorLength, std::vector<int> fixPoints_indices)
	: _samplesPerVector(samplesPerVector)
	, _vectorLength(vectorLength)
	, _fixPoint_indices(fixPoints_indices)
{
}
grapher::samples_To_VG::~samples_To_VG() {
}
//partial specialization
template <class ExecutionPolicy, class Iterator, class OutputIterator, class UnaryFunction> void grapher::samples_To_VG::operator()(ExecutionPolicy& task1, Iterator begin, Iterator end, OutputIterator begin2, UnaryFunction& angleFunction)
{
	//par
	//std::experimental::parallel::transform(task1, begin, end, begin, [](float f) {return 3.3f; });
	size_t size = std::distance(begin, end);
	if (size > 0) {
		std::vector<double> differences = std::vector<double>(size, 0.0f);
		__differences()(task1, begin, end, std::begin(differences));

		__differences_To_VG(_samplesPerVector, _vectorLength, _fixPoint_indices)(task1, std::begin(differences) + 1, std::end(differences), begin2, angleFunction);
	}
}
//template void grapher::samples_To_VG::operator()(fexec& task1, vector_single begin, vector_single end, vector_pair begin2, plainAngle& angleFunction);
//template void grapher::samples_To_VG::operator()(fexec& task1, vector_single begin, vector_single end, vector_pair begin2, test2& angleFunction);