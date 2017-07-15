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

	template<typename T> class timecode : public std::pair<T, T> {
	public:
		using std::pair<T, T>::pair;
		typedef typename std::pair<T, T>::first_type value_type;
		using timecode_types = typename sp::tctype;

		timecode_types category{ tctype::EMPTY };
		virtual ~timecode();

		//sp::timecode<T> static operator+=(sp::timecode<T>& a, const sp::timecode<T>& b);//function template
	};
	template<typename T> class empty : public sp::timecode<T> {
	public:
		using timecode_types = typename sp::timecode<T>::timecode_types;
		empty<T>(timecode<T>&& other);
	};
	template<typename T> class fixpoint : public sp::timecode<T> {
	public:
		using timecode_types = typename sp::timecode<T>::timecode_types;
		fixpoint<T>(timecode<T>&& other);
	};
	template<typename T> using element_ = timecode<T>;
	template<typename T> using element = element_<T>;//element_*;
	template<typename T> using result = std::vector<element<T>>;
	template<typename T> element<T> static construct_element_(T a, T b) {
		element<T> e = element<T>();
		e.first = a;
		e.second = b;
		return e;
	};
	//template<typename T> element<T> static construct_element_(T a, T b);
	/*template<class What> bool is(element* t) {
		element* u = t;//dynamic_cast<sp::element*>(&t);
		What* v = nullptr;
		v = dynamic_cast<What*>(u);
		if (v)
			return true;
		else
			return false;
	}*/

	template<typename T> sp::timecode<T> static operator+=(sp::timecode<T>& a, const sp::timecode<T>& b) {
		T af, as;
		af = a.first;
		as = a.second;
		af += b.first;
		as += b.second;
		a.first = af;
		a.second = as;
		return a;
	};//function template
	//template<typename T> sp::timecode<T> static operator+=(sp::timecode<T>& a, const sp::timecode<T>& b);//function template

	//sp::element static operator+(const sp::element& a, const sp::element& b) { return sp::element{ a.first + b.first, a.second + b.second }; };
	//sp::element static operator-(const sp::element& a, const sp::element& b) { return sp::element{ a.first - b.first, a.second - b.second }; };
}



template<typename T> using it_element = std::pair< typename std::vector<sp::element<T>>::iterator, typename std::vector<sp::element<T>>::iterator >;

template<typename T> using vector_single = typename std::vector<T>::iterator;
template<typename T> using vector_single_T = typename std::iterator_traits<T>::value_type;

template<typename T> using vector_pair = typename std::vector<sp::element<T>>::iterator;
template<typename T> using vector_pair_T = typename std::iterator_traits<T>::value_type::value_type;

template<typename T> using vector_vectors = typename std::vector<it_element<T>>::iterator;
template<typename T> using vector_vectors_T = typename std::iterator_traits<typename std::iterator_traits<T>::value_type::first_type>::value_type::value_type;

//using fexec = std::experimental::parallel::parallel_vector_execution_policy;
#include "dummy.h"
using fexec = const dummy;

#endif
