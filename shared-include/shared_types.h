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
		
	};
	template<typename T> using element_ = timecode<T>;
    template<typename T> using element = element_<T>;//element_*;
	template<typename T> using result = std::vector<element<T>>;

	/*template<class What> bool is(element* t) {
		element* u = t;//dynamic_cast<sp::element*>(&t);
		What* v = nullptr;
		v = dynamic_cast<What*>(u);
		if (v)
			return true;
		else
			return false;
	}*/
	/*element construct_element(double a, double b) {
		element r = new element_{ a,b };
		return r;
	}*/
	template<typename T> element<T> construct_element_(T a, T b) {
        element<T> e = element<T>();
        e.first = a;
        e.second = b;
		return e;
	}
}
//sp::timecode<double> static operator+=(sp::timecode<double>& a, const sp::timecode<double>& b) { a.first = a.first + b.first; a.second = a.second + b.second; return a; };
template<typename T> sp::timecode<T> static operator+=(sp::timecode<T>& a, const sp::timecode<T>& b) {
    T af,as;
    af = a.first;
    as = a.second;
    af += b.first;
    as += b.second;
    a.first = af;
    a.second = as;
    return a; };//function template
//sp::element static operator+(const sp::element& a, const sp::element& b) { return sp::element{ a.first + b.first, a.second + b.second }; };
//sp::element static operator-(const sp::element& a, const sp::element& b) { return sp::element{ a.first - b.first, a.second - b.second }; };

template<typename T> using it_element = std::pair< typename std::vector<sp::element<T>>::iterator, typename std::vector<sp::element<T>>::iterator >;
/*template<typename T> class it_element : public std::pair<typename std::vector<sp::element<T>>::iterator, typename std::vector<sp::element<T>>::iterator >{
public:
    using std::pair< typename std::vector<sp::element<T>>::iterator, typename std::vector<sp::element<T>>::iterator >::pair;
};*/


//Windows using vector_single = std::_Vector_iterator<std::_Vector_val<std::_Simple_types<double>>>;
template<typename T> using vector_single = typename std::vector<T>::iterator;
//Windows using vector_singlef = std::_Vector_iterator<std::_Vector_val<std::_Simple_types<float>>>;

//Windowsusing vector_pair = std::_Vector_iterator<std::_Vector_val<std::_Simple_types<sp::element>>>;
template<typename T> using vector_pair = typename std::vector<sp::element<T>>::iterator;
//Windows using vector_vectors = std::_Vector_iterator<std::_Vector_val<std::_Simple_types<it_element>>>;
template<typename T> using vector_vectors = typename std::vector<it_element<T>>::iterator;

//using fexec = std::experimental::parallel::parallel_vector_execution_policy;
#include "dummy.h"
using fexec = const dummy;


#endif
