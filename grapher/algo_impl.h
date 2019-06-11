// Copyright (C) 2017 Fassio Blatter
// GNU Lesser General Public License, version 2.1

#ifndef ALGO_H
#define ALGO_H

#include <stopeight-clibs/angle_functions.h>

namespace grapher {

	template<class InputIterator, class OutputIterator> void __differences(InputIterator begin, InputIterator end, OutputIterator begin2);

	template<class InputIterator, class OutputIterator> void __calculate_rotations(InputIterator begin, InputIterator end, OutputIterator begin2,angle::angle& angleFunction);

	template<class InputIterator, class OutputIterator> void __apply_rotation_matrix(InputIterator begin, InputIterator end, OutputIterator begin2);

	class _fixpoints {
	public:
		_fixpoints(std::vector<size_t>& points);
		~_fixpoints();
		template <class InputIterator, class OutputIterator>void operator()(InputIterator begin, InputIterator end, OutputIterator begin2);
	private:
		std::vector<size_t>& _fixPoint_indices;
	};

	class _blocks {
	public:
		_blocks(size_t samplesPerVector);
		~_blocks();
		template <class InputIterator, class OutputIterator>void operator()(InputIterator begin, InputIterator end, OutputIterator begin2);
	private:
		size_t _samplesPerVector;
	};

	template <class InputIterator, class OutputIterator>void _sum_blocks(InputIterator begin, InputIterator end, OutputIterator begin2);//freedom vector or deque//type in or out?

	//specialization: 1 iterator_category, 2 value_types
	class _append {
	public:
		template <class ExecutionPolicy, class InputIterator, class OutputIterator>void operator()(ExecutionPolicy&, InputIterator begin, InputIterator end, OutputIterator begin2, std::forward_iterator_tag);
	};

	//speed test formally std::vector<timecode> is generic, sp::result<type> is specialized
	class __differences_To_VG {
	public:
		__differences_To_VG(int samplesPerVector, double vectorLength, std::vector<size_t> fixPoints_indices = std::vector<size_t>(1, 0));
		~__differences_To_VG();

		//specialization: 1 iterator_category, 2 value_types
        template <class ExecutionPolicy, class InputIterator, class OutputIterator, class UnaryFunction>void operator()(ExecutionPolicy&, InputIterator begin, InputIterator end, OutputIterator begin2, UnaryFunction& angleFunction);

	private:
		int _samplesPerVector;
		double _vectorLength;
		std::vector<size_t> _fixPoint_indices;
	};

	int samples_To_VG_vectorSize(int inputSize, int samplesPerVector=1);
	double samples_To_VG_vectorLength(int showSamples, double unitaryLength = 1);

	class samples_To_VG {
	public:
		//experimental value from notation2.wav => sin(1.0f/300.0f)
		samples_To_VG(int samplesPerVector, double vectorLength, std::vector<size_t> fixPoints_indices = std::vector<size_t>(1, 0));
		~samples_To_VG();

		//specialization: 1 iterator_category, 2 value_types
        template <class ExecutionPolicy, class InputIterator, class OutputIterator, class UnaryFunction>void operator()(ExecutionPolicy&, InputIterator begin, InputIterator end, OutputIterator begin2, UnaryFunction& angleFunction);

	private:
		int _samplesPerVector;
		double _vectorLength;
		std::vector<size_t> _fixPoint_indices;
	};
}
#endif
