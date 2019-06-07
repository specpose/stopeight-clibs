// Copyright (C) 2017 Fassio Blatter
// GNU Lesser General Public License, version 2.1

#ifndef ALGO_H
#define ALGO_H

#include <stopeight-clibs/angle_functions.h>

namespace grapher {

	template<class InputIterator, class OutputIterator> void __differences(InputIterator begin, InputIterator end, OutputIterator begin2);

	template<class InputIterator, class OutputIterator> void __calculate_rotations(InputIterator begin, InputIterator end, OutputIterator begin2,angle::angle& angleFunction);

	template<class InputIterator, class OutputIterator> void __apply_rotation_matrix(InputIterator begin, InputIterator end, OutputIterator begin2);

	//specialization: 1 iterator_category, 2 value_types
	template<typename T> class _fixpoints {
	public:
		_fixpoints(std::vector<int>& points);
		~_fixpoints();
		template <class ExecutionPolicy, class InputIterator, class OutputIterator>void operator()(ExecutionPolicy&, InputIterator begin, InputIterator end, OutputIterator begin2, std::random_access_iterator_tag);
	private:
		std::vector<int>& _fixPoint_indices;
	};

	//specialization: 1 iterator_category, 2 value_types
	class _blocks {
	public:
		_blocks(int samplesPerVector);
		~_blocks();
		template <class ExecutionPolicy, class InputIterator, class OutputIterator>void operator()(ExecutionPolicy&, InputIterator begin, InputIterator end, OutputIterator begin2, std::random_access_iterator_tag);
	private:
		int _samplesPerVector;
	};

	//specialization: 1 iterator_category, 2 value_types
	class _sum_blocks {
	public:
		template <class ExecutionPolicy, class InputIterator, class OutputIterator>void operator()(ExecutionPolicy&, InputIterator begin, InputIterator end, OutputIterator begin2, std::random_access_iterator_tag);//freedom vector or deque//type in or out?
	};

	//specialization: 1 iterator_category, 2 value_types
	class _append {
	public:
		template <class ExecutionPolicy, class InputIterator, class OutputIterator>void operator()(ExecutionPolicy&, InputIterator begin, InputIterator end, OutputIterator begin2, std::forward_iterator_tag);
	};

	class __differences_To_VG {
	public:
		__differences_To_VG(int samplesPerVector, double vectorLength, std::vector<int> fixPoints_indices = std::vector<int>(1, 0));
		~__differences_To_VG();

		//specialization: 1 iterator_category, 2 value_types
        template <class ExecutionPolicy, class InputIterator, class OutputIterator, class UnaryFunction>void operator()(ExecutionPolicy&, InputIterator begin, InputIterator end, OutputIterator begin2, UnaryFunction& angleFunction);

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
        template <class ExecutionPolicy, class InputIterator, class OutputIterator, class UnaryFunction>void operator()(ExecutionPolicy&, InputIterator begin, InputIterator end, OutputIterator begin2, UnaryFunction& angleFunction);

	private:
		int _samplesPerVector;
		double _vectorLength;
		std::vector<int> _fixPoint_indices;
	};
}
#endif
