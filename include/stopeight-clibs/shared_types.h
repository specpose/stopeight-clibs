// Copyright (C) 2017 Fassio Blatter
// GNU Lesser General Public License, version 2.1

#ifndef SHARED_TYPES_H
#define SHARED_TYPES_H

#include <vector>
#include <array>

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
	const sp::tctype corners[3] = { tctype::STRAIT, tctype::CLIFF, tctype::SPIKE };
	const sp::tctype symetric[3] = { tctype::CLIFF, tctype::SWING, tctype::STRAIT };
	const sp::tctype notsymetric[3] = { tctype::CREST, tctype::SPIRAL, tctype::SPIKE };

	template<typename T> class timecode : public std::array<T, 2> {
	public:
		//using std::array<T, 2>::array;
		timecode() : std::array<T, 2>() {
		}
		timecode(const timecode<T>& other) : std::array<T, 2>(other) {
			this->category = other.category;
		}
		timecode(timecode<T>&& other) : std::array<T, 2>(other) {
			this->category = other.category;
		}
		timecode(T x, T y) : std::array<T, 2>{ {x, y}} {
		}
		typedef typename std::array<T, 2>::value_type value_type;
		typedef typename value_type& reference;
		using timecode_types = typename sp::tctype;

		timecode_types category{ tctype::EMPTY };
		virtual ~timecode() {};

		value_type get_x() { return (*this)[0]; };
		value_type get_y() { return (*this)[1]; };
		void set_x(value_type other) { (*this)[0] = other; };
		void set_y(value_type other) { (*this)[1] = other; };

		//template<typename U>
		timecode& operator=(sp::timecode<T> other) {
			this->set_x(other.get_x());
			this->set_y(other.get_y());
			this->category = other.category;
			return *this;
		}
		//template<typename U>
		timecode& operator+=(sp::timecode<T> b) {
			this->set_x(this->get_x()+b.get_x());
			this->set_y(this->get_y()+b.get_y());
			return *this;
			
		};//function template
	};
	template<typename T> class empty : public sp::timecode<T> {
	public:
		using sp::timecode<T>::timecode;
		using timecode_types = typename sp::timecode<T>::timecode_types;
		empty<T>(timecode<T>&& other) {
			sp::timecode<T>::category = sp::tctype::EMPTY;
		};
	};
	template<typename T> class fixpoint : public sp::timecode<T> {
	public:
		using sp::timecode<T>::timecode;
		using timecode_types = typename sp::timecode<T>::timecode_types;
		fixpoint<T>(timecode<T>&& other) {
			sp::timecode<T>::category = sp::tctype::FIXPOINT;
		};
	};
	//template<typename T> using element_ = timecode<T>;
	//template<typename T> using element = element_<T>;//element_*;
	template<typename T> using result = std::vector<timecode<T>>;
	/*template<typename T> element<T> construct_element(T a, T b) {
		element<T> e = element<T>();
		e.set_x(a);
		e.set_y(b);
		return e;
	};*/

	//template<typename T> element<T> construct_element(T a, T b);
	/*template<class What> bool is(element* t) {
		element* u = t;//dynamic_cast<sp::element*>(&t);
		What* v = nullptr;
		v = dynamic_cast<What*>(u);
		if (v)
			return true;
		else
			return false;
	}*/

	/*template<typename T> sp::timecode<T> operator+=(sp::timecode<T>& a, const sp::timecode<T>& b) {
		T af, as;
		af = a.get_x();
		as = a.get_y();
		af += b.get_x();
		as += b.get_y();
		a.set_x(af);
		a.set_y(as);
		return a;
	};*/
	//function template
	//template<typename T> sp::timecode<T> operator+=(sp::timecode<T>& a, const sp::timecode<T>& b);//function template

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
