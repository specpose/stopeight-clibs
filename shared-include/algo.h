// Copyright (C) 2017 Fassio Blatter
// GNU Lesser General Public License, version 2.1

#ifndef ALGO_H
#define ALGO_H

namespace grapher {
	class __calculate_rotations {
	public:
		template <class ExecutionPolicy, class Iterator, class OutputIterator>void operator()(ExecutionPolicy&, Iterator begin, Iterator end, OutputIterator begin2,std::random_access_iterator_tag);
	};

	class __apply_rotation_matrix {
	public:
		template <class ExecutionPolicy, class Iterator, class OutputIterator>void operator()(ExecutionPolicy&, Iterator begin, Iterator end, OutputIterator begin2, std::forward_iterator_tag);
	};

	class _sum_blocks {
	public:
		template <class ExecutionPolicy, class Iterator, class OutputIterator>void operator()(ExecutionPolicy&, Iterator begin, Iterator end, OutputIterator begin2, std::random_access_iterator_tag);
	};

	int samples_To_VG_final_size(int inputSize, int samplesPerPixel);

	/*template<class Iterator> class blocks {
	public:
		blocks<Iterator>(int seg_size=1);
		~blocks<Iterator>();

		//is a forward iterator
		Iterator operator()(Iterator it);

	private:
		int _seg_size;
		int _counter = 0;
		Iterator _first;
	};*/

	class samples_To_VG {
	public:
		samples_To_VG(int samplesPerPixel);
		~samples_To_VG();

		template <class ExecutionPolicy, class Iterator, class OutputIterator>void operator()(ExecutionPolicy&, Iterator begin, Iterator end, OutputIterator begin2);

	private:
		int _samplesPerPixel;
	};
}
#endif