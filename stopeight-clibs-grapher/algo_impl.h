// Copyright (C) 2017 Fassio Blatter
// GNU Lesser General Public License, version 2.1

#ifndef ALGO_H
#define ALGO_H

#include "angle_functions.h"
using it_element = std::pair<typename std::vector<sp::element>::iterator, typename std::vector<sp::element>::iterator>;

using vector_singled = std::_Vector_iterator<std::_Vector_val<std::_Simple_types<double>>>;
using vector_singlef = std::_Vector_iterator<std::_Vector_val<std::_Simple_types<float>>>;
using vector_pair = std::_Vector_iterator<std::_Vector_val<std::_Simple_types<sp::element>>>;

using vector_vectors = std::_Vector_iterator<std::_Vector_val<std::_Simple_types<it_element>>>;
//using fexec = std::experimental::parallel::parallel_vector_execution_policy;
#include "dummy.h"
using fexec = dummy;
namespace grapher {

	//specialization: 1 iterator_category, 2 value_types
	class __differences {
	public:
		template <class ExecutionPolicy, class Iterator, class OutputIterator>void operator()(ExecutionPolicy&, Iterator begin, Iterator end, OutputIterator begin2);
	};
	template void __differences::operator() < fexec&, vector_singled, vector_singled > (fexec& task1, vector_singled begin, vector_singled end, vector_singled begin2);
	template void __differences::operator() < fexec&, vector_singlef, vector_singlef > (fexec& task1, vector_singlef begin, vector_singlef end, vector_singlef begin2);

	//specialization: 1 iterator_category, 2 value_types
	class __average {
	public:
		template <class Iterator>double operator()(Iterator begin, Iterator end);
	};

	//specialization: 1 iterator_category, 2 value_types
	class __calculate_rotations {
	public:
		template <class ExecutionPolicy, class Iterator, class OutputIterator> void operator()(ExecutionPolicy&, Iterator begin, Iterator end, OutputIterator begin2,angle& angleFunction, std::forward_iterator_tag itag);
		//for different implementation: overload, not specialisation
	};

	//specialization: 1 iterator_category, 2 value_types
	class __apply_rotation_matrix {
	public:
		template <class ExecutionPolicy, class Iterator, class OutputIterator>void operator()(ExecutionPolicy&, Iterator begin, Iterator end, OutputIterator begin2);
	};

	//specialization: 1 iterator_category, 2 value_types
	class _fixpoints {
	public:
		_fixpoints(std::vector<int>& points);
		~_fixpoints();
		template <class ExecutionPolicy, class Iterator, class OutputIterator>void operator()(ExecutionPolicy&, Iterator begin, Iterator end, OutputIterator begin2, std::random_access_iterator_tag);
	private:
		std::vector<int>& _fixPoint_indices;
	};

	//specialization: 1 iterator_category, 2 value_types
	class _blocks {
	public:
		_blocks(int samplesPerVector);
		~_blocks();
		template <class ExecutionPolicy, class Iterator, class OutputIterator>void operator()(ExecutionPolicy&, Iterator begin, Iterator end, OutputIterator begin2, std::random_access_iterator_tag);
	private:
		int _samplesPerVector;
	};

	//specialization: 1 iterator_category, 2 value_types
	class _sum_blocks {
	public:
		template <class ExecutionPolicy, class Iterator, class OutputIterator>void operator()(ExecutionPolicy&, Iterator begin, Iterator end, OutputIterator begin2, std::random_access_iterator_tag);
	};

	//specialization: 1 iterator_category, 2 value_types
	class _append {
	public:
		template <class ExecutionPolicy, class Iterator, class OutputIterator>void operator()(ExecutionPolicy&, Iterator begin, Iterator end, OutputIterator begin2, std::forward_iterator_tag);
	};

	class __differences_To_VG {
	public:
		__differences_To_VG(int samplesPerVector, double vectorLength, std::vector<int> fixPoints_indices = std::vector<int>(1, 0));
		~__differences_To_VG();

		//specialization: 1 iterator_category, 2 value_types
		template <class ExecutionPolicy, class Iterator, class OutputIterator, class UnaryFunction>void operator()(ExecutionPolicy&, Iterator begin, Iterator end, OutputIterator begin2, UnaryFunction& angleFunction = test2(0.0f));

	private:
		int _samplesPerVector;
		double _vectorLength;
		std::vector<int> _fixPoint_indices;
	};

	int samples_To_VG_vectorSize(int inputSize, int samplesPerVector=1);
	double samples_To_VG_vectorLength(int showSamples, double unitaryLength = 1);

	class samples_To_VG {
	public:
		//experimental value from notation2.wav => sin(1.0f/300.0f)
		samples_To_VG(int samplesPerVector, double vectorLength, std::vector<int> fixPoints_indices = std::vector<int>(1, 0));
		~samples_To_VG();

		//specialization: 1 iterator_category, 2 value_types
		template <class ExecutionPolicy, class Iterator, class OutputIterator, class UnaryFunction>void operator()(ExecutionPolicy&, Iterator begin, Iterator end, OutputIterator begin2, UnaryFunction& angleFunction=test2(0.0f));

	private:
		int _samplesPerVector;
		double _vectorLength;
		std::vector<int> _fixPoint_indices;
	};
}
#endif