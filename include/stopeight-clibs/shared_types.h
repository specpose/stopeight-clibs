// Copyright (C) 2017 Fassio Blatter
// GNU Lesser General Public License, version 2.1

#ifndef SHARED_TYPES_H
#define SHARED_TYPES_H

#include <vector>
#include <array>
#include <tuple>

namespace sp {

	enum class FixpointType {
		EMPTY,
		FIXPOINT
	};

	enum class tctype
	{
		STRAIT,
		SWING,
		CLIFF,
		CREST,
		SPIRAL,
		SPIKE
	};

	const sp::tctype turns[3] = { tctype::SWING,tctype::CREST,tctype::SPIRAL };
	const sp::tctype corners[3] = { tctype::STRAIT, tctype::CLIFF, tctype::SPIKE };
	const sp::tctype symetric[3] = { tctype::CLIFF, tctype::SWING, tctype::STRAIT };
	const sp::tctype notsymetric[3] = { tctype::CREST, tctype::SPIRAL, tctype::SPIKE };

	template<typename T> class timecode {
	public:
		//using std::array<T, 2>::array;
		timecode() {
			type = sp::FixpointType::EMPTY;
		}
		timecode(T x, T y){
			coords = { { x, y } };
			type = sp::FixpointType::EMPTY;
		}
		typedef typename std::array<T, 2>::value_type value_type;
		typedef typename std::array<T, 2>::reference reference;
		sp::FixpointType category() {
			return type;
		}
		void set_category(sp::FixpointType type) {
			this->type = type;
		}
		//virtual ~timecode() {};

		value_type get_x() { return coords[0]; };
		value_type get_y() { return coords[1]; };
		void set_x(const reference other) { coords[0] = other; };
		void set_y(const reference other) { coords[1] = other; };

		//template<typename U>
		/*timecode& operator=(sp::timecode<T> other) {
			T one = other.get_x();
			this->set_x(one);
			T two = other.get_y();
			this->set_y(two);
			this->type = other.category();
			return *this;
		}
		//template<typename U>
		timecode& operator+=(const sp::timecode<T>& b) {
			const T one1 = this->get_x();
			const T one2{ coords[0] };
			T one3{ one1 + one2 };
			this->set_x(one3);
			const T two1 = this->get_y();
			const T two2{ coords[1] };
			T two3 = two1 + two2;
			this->set_y(two3);
			return *this;
			
		};//function template*/

		std::array<T, 2> coords;
		sp::FixpointType type;
	};
	template<typename T> sp::timecode<T> operator+=(sp::timecode<T>& a, const sp::timecode<T>& b) {
		a.coords[0] = a.coords[0]+b.coords[0];
		a.coords[1] = a.coords[1]+b.coords[1];
		return a;
	};//function template
	template<typename T> bool operator==(const sp::timecode<T>& a, const sp::timecode<T>& b){
		if (a.coords==b.coords){
			return true;
		} else {
			return false;
		}	
	};
	template<typename T> class empty : public sp::timecode<T> {
	public:
		using sp::timecode<T>::timecode;
		empty<T>(timecode<T>&& other) {
			this->type = sp::FixpointType::EMPTY;
		};
	};
	template<typename T> class fixpoint : public sp::timecode<T> {
	public:
		using sp::timecode<T>::timecode;
		fixpoint<T>(timecode<T>&& other) {
			this->type = sp::FixpointType::FIXPOINT;
		};
	};
	template<typename T> using result = std::vector<timecode<T>>;
	
	//sp::element static operator+(const sp::element& a, const sp::element& b) { return sp::element{ a.first + b.first, a.second + b.second }; };
	//sp::element static operator-(const sp::element& a, const sp::element& b) { return sp::element{ a.first - b.first, a.second - b.second }; };
}



template<typename T> using it_element = std::pair< typename std::vector<sp::timecode<T>>::iterator, typename std::vector<sp::timecode<T>>::iterator >;

template<typename T> using vector_single = typename std::vector<T>::iterator;
template<typename T> using vector_single_T = typename std::iterator_traits<T>::value_type;

template<typename T> using vector_pair = typename std::vector<sp::timecode<T>>::iterator;
template<typename T> using vector_pair_T = typename std::iterator_traits<T>::value_type::value_type;

template<typename T> using vector_vectors = typename std::vector<it_element<T>>::iterator;
template<typename T> using vector_vectors_T = typename std::iterator_traits<typename std::iterator_traits<T>::value_type::first_type>::value_type::value_type;

#endif
