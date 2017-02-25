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

	class __length_sum {
		__length_sum(int limit) : _limit(limit) {};
		~__length_sum() {};
		std::pair<double, double> operator()(std::pair<double,double> current) {
			if (_count <= _limit) {
				_accumulate = _add(_accumulate, current);
				_count++;
			}
			else {
				_accumulate = current;
				_count = 0;
			}
			return _accumulate;
		}
	private:
		static std::pair<double, double> _add(std::pair<double, double> a, std::pair<double, double> b) { return std::pair<double, double>{ a.first+b.first,a.second+b.second}; };
		std::pair<double, double> _accumulate{ 0.0f,0.0f };
		int _limit;
		int _count = 0;
	};

	class __add_vectors {
	public:
		__add_vectors(int samplesPerPixel);
		~__add_vectors();

		template <class ExecutionPolicy, class Iterator, class OutputIterator>void operator()(ExecutionPolicy&, Iterator begin, Iterator end, OutputIterator begin2, std::random_access_iterator_tag);

	private:
		int _samplesPerPixel;
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
#endif