// Copyright (C) 2017 Fassio Blatter
// GNU Lesser General Public License, version 2.1

#include "shared_types.h"
#include <vector>

namespace sp {

	const sp::tctype turns[3] = { tctype::SWING,tctype::CREST,tctype::SPIRAL };
	const sp::tctype corners[3] = { tctype::STRAIT, tctype::CLIFF, tctype::SPIKE };
	const sp::tctype symetric[3] = { tctype::CLIFF, tctype::SWING, tctype::STRAIT };
	const sp::tctype notsymetric[3] = { tctype::CREST, tctype::SPIRAL, tctype::SPIKE };

	template<typename T> timecode<T>::~timecode() {};
	template timecode<double>::~timecode();
	template timecode<float>::~timecode();

	template<typename T> empty<T>::empty(timecode<T>&& other) : timecode<T>{ other } {
		sp::timecode<T>::category = sp::tctype::EMPTY;
	};
	template empty<double>::empty(timecode<double>&& other);
	template empty<float>::empty(timecode<float>&& other);

	template<typename T> fixpoint<T>::fixpoint(timecode<T>&& other) : timecode<T>{ other } {
		sp::timecode<T>::category = sp::tctype::FIXPOINT;
	};
	template fixpoint<double>::fixpoint(timecode<double>&& other);
	template fixpoint<float>::fixpoint(timecode<float>&& other);

	template<typename T> using element_ = timecode<T>;
	template<typename T> using element = element_<T>;//element_*;
	template<typename T> using result = std::vector<element<T>>;
	template<typename T> element<T> construct_element(T a, T b) {
		element<T> e = element<T>();
		e.first = a;
		e.second = b;
		return e;
	};
	template element<double> construct_element(double a, double b);
	template element<float> construct_element(float a, float b);

	template<typename T> sp::timecode<T> operator+=(sp::timecode<T>& a, const sp::timecode<T>& b) {
		T af, as;
		af = a.first;
		as = a.second;
		af += b.first;
		as += b.second;
		a.first = af;
		a.second = as;
		return a;
	};//function template
	template sp::timecode<double> operator+=(sp::timecode<double>& a, const sp::timecode<double>& b);
	template sp::timecode<float> operator+=(sp::timecode<float>& a, const sp::timecode<float>& b);

}