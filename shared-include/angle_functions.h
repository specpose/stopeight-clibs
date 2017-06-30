// Copyright (C) 2017 Fassio Blatter
// GNU Lesser General Public License, version 2.1

#ifndef ANGLE_FUNCTIONS
#define ANGLE_FUNCTIONS

#include <numeric>

namespace grapher {

	class angle : public std::unary_function<double, double> {
	public:
		virtual ~angle() {};
		virtual result_type operator()(argument_type d) = 0;
	};

	class plainAngle : public angle {
	public:
	};

	class averageScaled : public angle {
	public:
		template<typename Iterator>averageScaled(Iterator begin, Iterator end, double average, double angleScale) 
			: av((average==0.0f)?__average()(begin, end):average)
			, _angleScale((angleScale==0.0f)?std::numeric_limits<double>::min():angleScale) {
			//if (_contextAverage == 0.0f)
			//	_contextAverage == std::numeric_limits<double>::min();
		}
		//virtual void setAverate(argument_type average) final { av = average; };
		//virtual const argument_type getAverage() final { return av; };
	protected:
		argument_type av;
		double _angleScale;
	};

	class relative2 : public averageScaled {
	public:
		template<typename Iterator>relative2(Iterator begin, Iterator end, double average=0.0f, double angleScale=1.0f,double initialAngle = 0.0f) : averageScaled(begin, end, average, angleScale), _previous(initialAngle) {};
		double operator()(double d) {
			if (d == 0.0f || av == 0.0f)
				return double(0.0f);
			auto absdiff = 0;
			_previous += atan(((d/av)/ av)*_angleScale);
			return (_previous);
		};
	private:
		double _previous;
	};

	class independent2 : public averageScaled {
	public:
		template<typename Iterator>independent2(Iterator begin, Iterator end, double average=0.0f, double angleScale=1.0f) : averageScaled(begin, end, average, angleScale) {};
		double operator()(double d) {
			if (d == 0.0f || av == 0.0f)
				return double(0.0f);
			return atan(((d/av)/ av)*_angleScale);
		};
	};

	class relative : public averageScaled {
	public:
		template<typename Iterator>relative(Iterator begin, Iterator end, double average = 0.0f, double angleScale = 1.0f, double initialAngle = 0.0f) : averageScaled(begin, end, average, angleScale), _previous(initialAngle) {};
		double operator()(double d) {
			if (d == 0.0f || av == 0.0f)
				return double(0.0f);
			_previous += atan((d / av)*_angleScale);
			return (_previous);
		};
	private:
		double _previous;
	};

	class independent : public averageScaled {
	public:
		template<typename Iterator>independent(Iterator begin, Iterator end, double average = 0.0f, double angleScale = 1.0f) : averageScaled(begin, end, average, angleScale) {};
		double operator()(double d) {
			if (d == 0.0f || av == 0.0f)
				return double(0.0f);
			return atan((d / av)*_angleScale);
		};
	};

	/*class test : public averageScaled {
	public:
		template<typename Iterator>test(Iterator begin, Iterator end) : averageScaled(begin, end) {};
		double operator()(double d) {
			if (d == 0.0f || av == 0.0f)
				return double(0.0f);
			return 300 * asin(d);
		};
	};

	class test2 : public averageScaled {
	public:
		template<typename Iterator>test2(Iterator begin, Iterator end, double initialAngle = 0.0f) : averageScaled(begin, end), _previous(initialAngle) {};
		double operator()(double d) {
			if (d == 0.0f || av == 0.0f)
				return double(0.0f);
			double inc = d - av;
			if (inc <= 0)
				inc = 0;
			_previous += atan((inc) / av);
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
	};*/
}
#endif