// Copyright (C) 2017 Fassio Blatter
// GNU Lesser General Public License, version 2.1

#ifndef ALGO_H
#define ALGO_H

namespace grapher {

	class angle : public std::unary_function<double,double> {
	public:
		virtual ~angle() {};
		virtual result_type operator()(argument_type d) = 0;
	};

	class plainAngle : public angle {
	public:
		//virtual result_type operator()(argument_type d) = 0;
	};

	class averageScaled : public angle {
	public:
		template<typename Iterator>averageScaled(Iterator begin, Iterator end) : av(__average()(begin, end, Iterator::iterator_category{})) {
			//if (_contextAverage == 0.0f)
			//	_contextAverage == std::numeric_limits<double>::min();
		}
		virtual void setAverate(argument_type average) final { av = average; };
		virtual const argument_type getAverage() final { return av; };
		//virtual result_type operator()(argument_type d) = 0;
	protected:
		argument_type av;
	};

	class relative : public averageScaled {
	public:
		template<typename Iterator>relative(Iterator begin, Iterator end, double initialAngle = 0.0f) : averageScaled(begin,end),_previous(initialAngle) {};
		double operator()(double d) {
			if (d == 0.0f || av == 0.0f)
				return double(0.0f);
			_previous += atan((d / av) / 1);
			return (_previous);
		};
	private:
		double _previous;
	};
	
	class independent : public averageScaled {
	public:
		template<typename Iterator>independent(Iterator begin, Iterator end) : averageScaled(begin, end) {};
		double operator()(double d) {
			if (d == 0.0f || av == 0.0f)
				return double(0.0f);
			return atan((d / av) / 1);
		};
	};

	class test : public averageScaled {
	public:
		template<typename Iterator>test(Iterator begin, Iterator end) : averageScaled(begin, end) {};
		double operator()(double d) {
			if (d == 0.0f || av == 0.0f)
				return double(0.0f);
			return 300*asin(d);
		};
	};

	class test2 : public averageScaled {
	public:
		template<typename Iterator>test2(Iterator begin, Iterator end, double initialAngle = 0.0f) : averageScaled(begin, end),_previous(initialAngle) {};
		double operator()(double d) {
			if (d == 0.0f || av == 0.0f)
				return double(0.0f);
			double inc = d - av;
			if (inc <= 0)
				inc = 0;
			_previous += atan((inc)/ av);
			return (_previous);
		};
	private:
		double _previous;
	};

	class test3 : public plainAngle {
	public:
		test3(double dummer) {};
		double operator()(double d) {
			return atan(d);
		};
	private:
	};

	//specialization: 1 iterator_category, 2 value_types
	class __differences {
	public:
		template <class ExecutionPolicy, class Iterator, class OutputIterator>void operator()(ExecutionPolicy&, Iterator begin, Iterator end, OutputIterator begin2);
	};

	//specialization: 1 iterator_category, 2 value_types
	class __average {
	public:
		template <class Iterator>double operator()(Iterator begin, Iterator end, std::forward_iterator_tag);
	};

	//specialization: 1 iterator_category, 2 value_types
	class __calculate_rotations {
	public:
		template <class ExecutionPolicy, class Iterator, class OutputIterator> void operator()(ExecutionPolicy&, Iterator begin, Iterator end, OutputIterator begin2,angle& angleFunction, std::forward_iterator_tag itag);
		template <class ExecutionPolicy, class Iterator, class OutputIterator> void operator()(ExecutionPolicy&, Iterator begin, Iterator end, OutputIterator begin2, averageScaled& angleFunction, std::forward_iterator_tag itag);

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