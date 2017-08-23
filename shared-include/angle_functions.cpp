// Copyright (C) 2017 Fassio Blatter
// GNU Lesser General Public License, version 2.1

#include "angle_functions.h"
#include <numeric>
#include <math.h>
#include <vector>

namespace angle {

	template<typename T> using vector_T = typename std::vector<T>::iterator;

    //specialization: 1 iterator_category, 2 value_types
    
    template <class Iterator>double __average::operator()(Iterator begin, Iterator end){
        auto sum = std::accumulate(begin, end, 0.0f, [](double first, double second) {
            return first += fabs(second);
            
        });
        return sum / std::distance(begin, end);
        }

    template double __average::operator()(vector_T<double> begin, vector_T<double> end);
	template double __average::operator()(vector_T<float> begin, vector_T<float> end);

	angle::~angle() {};
	
	template<typename Iterator>averageScaled::averageScaled(Iterator begin, Iterator end, double average, double angleScale) 
        : av((average==0.0f)?__average()(begin, end):average)
			, _angleScale((angleScale==0.0f)?std::numeric_limits<double>::min():angleScale) {
			//if (_contextAverage == 0.0f)
			//	_contextAverage == std::numeric_limits<double>::min();
	}
	template averageScaled::averageScaled(vector_T<double> begin, vector_T<double> end, double average, double angleScale);


	template<typename Iterator>relative2::relative2(Iterator begin, Iterator end, double average, double angleScale, double initialAngle) : averageScaled(begin, end, average, angleScale), _previous(initialAngle) {};
	template relative2::relative2(vector_T<double> begin, vector_T<double> end, double average, double angleScale, double initialAngle);
	template relative2::relative2(vector_T<float> begin, vector_T<float> end, double average, double angleScale, double initialAngle);

	double relative2::operator()(double d) {
			if (d == 0.0f || av == 0.0f)
				return double(0.0f);
			auto absdiff = 0;
			_previous += atan((d/av)*_angleScale/ av);
			return (_previous);
	};


	template<typename Iterator>independent2::independent2(Iterator begin, Iterator end, double average, double angleScale) : averageScaled(begin, end, average, angleScale) {};
	template independent2::independent2(vector_T<double> begin, vector_T<double> end, double average, double angleScale);
	template independent2::independent2(vector_T<float> begin, vector_T<float> end, double average, double angleScale);

	double independent2::operator()(double d) {
			if (d == 0.0f || av == 0.0f)
				return double(0.0f);
			return atan((d/av)*_angleScale/ av);
	};
	
	template<typename Iterator>relative::relative(Iterator begin, Iterator end, double average, double angleScale, double initialAngle) : averageScaled(begin, end, average, angleScale), _previous(initialAngle) {};
	template relative::relative(vector_T<double> begin, vector_T<double> end, double average, double angleScale, double initialAngle);
	template relative::relative(vector_T<float> begin, vector_T<float> end, double average, double angleScale, double initialAngle);

	double relative::operator()(double d) {
			if (d == 0.0f || av == 0.0f)
				return double(0.0f);
			_previous += atan(d*_angleScale / av);
			return (_previous);
	};

	template<typename Iterator>independent::independent(Iterator begin, Iterator end, double average, double angleScale) : averageScaled(begin, end, average, angleScale) {};
	template independent::independent(vector_T<double> begin, vector_T<double> end, double average, double angleScale);
	template independent::independent(vector_T<float> begin, vector_T<float> end, double average, double angleScale);

	double independent::operator()(double d) {
			if (d == 0.0f || av == 0.0f)
				return double(0.0f);
			return atan(d*_angleScale / av);
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
