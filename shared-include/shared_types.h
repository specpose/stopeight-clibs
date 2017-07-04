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
		typedef first_type value_type;
		using timecode_types = typename tctype;
		timecode_types category{tctype::EMPTY};

		virtual ~timecode() {};
	};
	template<typename T> class empty : public timecode<T> {
	public:
		using timecode_types = typename timecode::timecode_types;
		empty<T>(timecode<T>&& other) : timecode<T>{ other } {
			category = tctype::EMPTY;
		};
	};
	template<typename T> class fixpoint : public timecode<T> {
	public:
		using timecode_types = typename timecode::timecode_types;
		fixpoint<T>(timecode<T>&& other) : timecode<T>{ other } {
			category = tctype::FIXPOINT;
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

#endif