// Copyright (C) 2017 Fassio Blatter
// GNU Lesser General Public License, version 2.1

#ifndef ALGO_H
#define ALGO_H

namespace grapher {
	double static _angle(double ratio) { return atan(ratio); };

	//specialization: 1 iterator_category, 2 value_types
	class __average {
	public:
		template <class ExecutionPolicy, class Iterator>double operator()(ExecutionPolicy&, Iterator begin, Iterator end, std::forward_iterator_tag);
	};

	//specialization: 1 iterator_category, 2 value_types
	class __calculate_rotations {
	public:
		__calculate_rotations(double average_df);
		~__calculate_rotations();
		template <class ExecutionPolicy, class Iterator, class OutputIterator>void operator()(ExecutionPolicy&, Iterator begin, Iterator end, OutputIterator begin2,std::random_access_iterator_tag);
	private:
		double average_df;
	};

	//specialization: 1 iterator_category, 2 value_types
	class __apply_rotation_matrix {
	public:
		template <class ExecutionPolicy, class Iterator, class OutputIterator>void operator()(ExecutionPolicy&, Iterator begin, Iterator end, OutputIterator begin2, std::forward_iterator_tag);
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
	class _sum_blocks {
	public:
		template <class ExecutionPolicy, class Iterator, class OutputIterator>void operator()(ExecutionPolicy&, Iterator begin, Iterator end, OutputIterator begin2, std::random_access_iterator_tag);
	};

	//specialization: 1 iterator_category, 2 value_types
	class _append {
	public:
		template <class ExecutionPolicy, class Iterator, class OutputIterator>void operator()(ExecutionPolicy&, Iterator begin, Iterator end, OutputIterator begin2, std::forward_iterator_tag);
	};

	int samples_To_VG_vectorSize(int inputSize, int samplesPerVector=1);
	double samples_To_VG_vectorLength(int showSamples, double unitaryLength = 1);

	class samples_To_VG {
	public:
		//experimental value from notation2.wav => sin(1.0f/300.0f)
		samples_To_VG(int samplesPerVector,double vectorLength,std::vector<int> fixPoints_indices=std::vector<int>(1,0), double contextAverage=0.0f);
		~samples_To_VG();

		//specialization: 1 iterator_category, 2 value_types
		template <class ExecutionPolicy, class Iterator, class OutputIterator>void operator()(ExecutionPolicy&, Iterator begin, Iterator end, OutputIterator begin2);

	private:
		int _samplesPerVector;
		double _vectorLength;
		double _contextAverage;
		std::vector<int> _fixPoint_indices;
	};
}
#endif