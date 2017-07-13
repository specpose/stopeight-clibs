// Copyright (C) 2017 Fassio Blatter
// GNU Lesser General Public License, version 2.1

#ifndef SHARED_TYPES_H
#define SHARED_TYPES_H

#include <vector>

namespace sp {

	enum class tctype
	{
		EMPTY,
		FIXPOINT,
		STRAIT,
		SWING,
		CLIFF,
		CREST,
		SPIRAL,
		SPIKE
	};
	const sp::tctype turns[3] = { tctype::SWING,tctype::CREST,tctype::SPIRAL };
	const sp::tctype corners[3] = {tctype::STRAIT, tctype::CLIFF, tctype::SPIKE};
	const sp::tctype symetric[3] = {tctype::CLIFF, tctype::SWING, tctype::STRAIT};
	const sp::tctype notsymetric[3] = {tctype::CREST, tctype::SPIRAL, tctype::SPIKE};


	/*template<typename T> class pair : private std::pair<T, T> {//private std::vector<T> {
	public:
		typedef first_type value_type;
		using timecode_types = typename tctype;
		timecode_types category{ sp::tctype::EMPTY };

		pair() : std::pair<T, T>{}, first(first), second(second) {}//std::vector<T>(2),first(&this[0]),second(&this[1]){}
		using std::pair<T, T>::pair{};

		T& first, second;

	};
	template<typename T> class timecode : public sp::pair<T> {
	public:*/
	template<typename T> class timecode : public std::pair<T,T> {
	public:
		using std::pair<T, T>::pair;
        //Windows: typedef std::pair<T,T>::first_type value_type;
        typedef typename std::pair<T,T>::first_type value_type;
        using timecode_types = typename sp::tctype;
        
        timecode_types category{tctype::EMPTY};
		virtual ~timecode() {};
	};
    template<typename T> class empty : public sp::timecode<T> {
	public:
        using timecode_types = typename sp::timecode<T>::timecode_types;
		empty<T>(timecode<T>&& other) : timecode<T>{ other } {
            sp::timecode<T>::category = sp::tctype::EMPTY;
		};
	};
    template<typename T> class fixpoint : public sp::timecode<T> {
	public:
        using timecode_types = typename sp::timecode<T>::timecode_types;
		fixpoint<T>(timecode<T>&& other) : timecode<T>{ other } {
            sp::timecode<T>::category = sp::tctype::FIXPOINT;
		};
		
		//fixpoint() {};
		//fixpoint(timecode&& point) :*this{point}
		//~fixpoint() override {
		//	throw std::exception("fixpoints refer to timecode data and can not be deleted.");
		//};
	};
	using element_ = timecode<double>;
	using element = element_;//element_*;
	using result = std::vector<element>;

	template<class What> bool is(element* t) {
		element* u = t;//dynamic_cast<sp::element*>(&t);
		What* v = nullptr;
		v = dynamic_cast<What*>(u);
		if (v)
			return true;
		else
			return false;
	}
	/*element construct_element(double a, double b) {
		element r = new element_{ a,b };
		return r;
	}*/
	/*element construct_element(element::value_type a, element::value_type b) {
		return element{ a,b };
	}*/
}
sp::timecode<double> static operator+=(sp::timecode<double>& a, const sp::timecode<double>& b) { a.first = a.first + b.first; a.second = a.second + b.second; return a; };
//sp::element static operator+(const sp::element& a, const sp::element& b) { return sp::element{ a.first + b.first, a.second + b.second }; };
//sp::element static operator-(const sp::element& a, const sp::element& b) { return sp::element{ a.first - b.first, a.second - b.second }; };

using it_element = std::pair<typename std::vector<sp::element>::iterator, typename std::vector<sp::element>::iterator>;

//Windows using vector_single = std::_Vector_iterator<std::_Vector_val<std::_Simple_types<double>>>;
using vector_single = std::vector<double>::iterator;
//Windows using vector_singlef = std::_Vector_iterator<std::_Vector_val<std::_Simple_types<float>>>;
using vector_singlef = std::vector<float>::iterator;

//Windowsusing vector_pair = std::_Vector_iterator<std::_Vector_val<std::_Simple_types<sp::element>>>;
using vector_pair = std::vector<sp::element>::iterator;
//Windows using vector_vectors = std::_Vector_iterator<std::_Vector_val<std::_Simple_types<it_element>>>;
using vector_vectors = std::vector<it_element>::iterator;

//using fexec = std::experimental::parallel::parallel_vector_execution_policy;
#include "dummy.h"
using fexec = dummy;


#endif
