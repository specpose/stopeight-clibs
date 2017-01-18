#pragma once

namespace grapher {
	class __calculate_rotations {
	public:
		__calculate_rotations();
		~__calculate_rotations();

		template <class ExecutionPolicy, class Iterator, class OutputIterator>void operator()(ExecutionPolicy&, Iterator begin, Iterator end, OutputIterator begin2);
	};

	class samples_To_VG {
	public:
		samples_To_VG(int samplesPerPixel);
		~samples_To_VG();

		template <class ExecutionPolicy, class Iterator, class OutputIterator>void operator()(ExecutionPolicy&, Iterator begin, Iterator end, OutputIterator begin2);

	private:
		int _samplesPerPixel;
	};
}