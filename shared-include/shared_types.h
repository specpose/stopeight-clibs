// Copyright (C) 2017 Fassio Blatter
// GNU Lesser General Public License, version 2.1

//#pragma once
#ifndef SHARED_TYPES_H
#define SHARED_TYPES_H
namespace sp {

	enum class tctype
	{
		EMPTY,
		TURN,
		CORNER
	};
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
		using timecode_types = typename tctype;
		timecode_types category{sp::tctype::EMPTY};

		//virtual ~timecode() = 0;
	};
	/*template<typename T> class empty : public timecode<T> {
	public:
		using timecode_types = typename timecode::timecode_types;
		empty<T>(timecode<T>&& other) : timecode<T>{ other } {
			category = sp::tctype::EMPTY;
		};
	};*/
	template<typename T> class turn : public timecode<T> {
	public:
		using timecode_types = typename timecode::timecode_types;
		turn<T>(timecode<T>&& other) : timecode<T>{ other }{
			category = sp::tctype::TURN;
		};
		
		//fixpoint() {};
		//fixpoint(timecode&& point) :*this{point}
		//~fixpoint() override {
		//	throw std::exception("fixpoints refer to timecode data and can not be deleted.");
		//};
	};
	using element = timecode<double>;
	//using element = std::pair<double, double>;
	//using result = std::pair<std::vector<element>, std::vector<element>>;
	using result = std::vector<element>;
}
sp::element static operator+=(sp::element& a, const sp::element& b) { a.first = a.first + b.first; a.second = a.second + b.second; return a; };
//sp::element static operator+(const sp::element& a, const sp::element& b) { return sp::element{ a.first + b.first, a.second + b.second }; };
//sp::element static operator-(const sp::element& a, const sp::element& b) { return sp::element{ a.first - b.first, a.second - b.second }; };

#endif