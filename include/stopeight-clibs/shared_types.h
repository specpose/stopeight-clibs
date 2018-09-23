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

	template<typename T> class timecode;

	template<std::size_t I, typename T> typename std::tuple_element<I,std::tuple<std::array<T, 2>,sp::FixpointType>>::type&& get(timecode<T>&& v) {
		return std::get<I>(static_cast<std::tuple<std::array<T, 2>,sp::FixpointType>&&>(v));
	}
	template<std::size_t I, typename T> typename std::tuple_element<I,std::tuple<std::array<T, 2>,sp::FixpointType>>::type& get(timecode<T>& v) {
		return std::get<I>(static_cast<std::tuple<std::array<T, 2>, sp::FixpointType>&>(v));
	}
	template<std::size_t I, typename T> typename std::tuple_element<I,std::tuple<std::array<T, 2>,sp::FixpointType>>::type const& get(const timecode<T>& v) {
		return std::get<I>(static_cast<std::tuple<std::array<T, 2>, sp::FixpointType> const&>(v));
	}
	template<typename T> class timecode : public std::tuple<std::array<T, 2>,sp::FixpointType> {
	public:
		//using std::array<T, 2>::array;
		timecode() : std::tuple<std::array<T, 2>,sp::FixpointType>() {
			sp::get<1, T>(*this) = sp::FixpointType::EMPTY;
		}
		timecode(T x, T y) : std::tuple<std::array<T, 2>, sp::FixpointType>(){
			sp::get<0, T>(*this) = { { x, y } };
			sp::get<1, T>(*this) = sp::FixpointType::EMPTY;
		}
		typedef typename std::array<T, 2>::value_type value_type;
		typedef typename std::array<T, 2>::reference reference;
		sp::FixpointType category() {
			return sp::get<1,T>(*this);
		}
		void set_category(sp::FixpointType type) {
			sp::get<1,T>(*this) = type;
		}
		virtual ~timecode() {};

		value_type get_x() { return (sp::get<0,T>(*this))[0]; };
		value_type get_y() { return (sp::get<0,T>(*this))[1]; };
		void set_x(const reference other) { (sp::get<0,T>(*this))[0] = other; };
		void set_y(const reference other) { (sp::get<0,T>(*this))[1] = other; };
		typename std::array<T, 2>::pointer data() { return (sp::get<0,T>(*this)).data();}

		//template<typename U>
		timecode& operator=(sp::timecode<T> other) {
			T one = other.get_x();
			this->set_x(one);
			T two = other.get_y();
			this->set_y(two);
			sp::get<1, T>(*this) = other.category();
			return *this;
		}
		//template<typename U>
		timecode& operator+=(const sp::timecode<T>& b) {
			const T one1 = this->get_x();
			const T one2{ (sp::get<0,T>(b))[0] };
			T one3{ one1 + one2 };
			this->set_x(one3);
			const T two1 = this->get_y();
			const T two2{ (sp::get<0,T>(b))[1] };
			T two3 = two1 + two2;
			this->set_y(two3);
			return *this;
			
		};//function template
	};
	template<typename T> class empty : public sp::timecode<T> {
	public:
		using sp::timecode<T>::timecode;
		empty<T>(timecode<T>&& other) {
			sp::get<1, T>(*this) = sp::FixpointType::EMPTY;
		};
	};
	template<typename T> class fixpoint : public sp::timecode<T> {
	public:
		using sp::timecode<T>::timecode;
		fixpoint<T>(timecode<T>&& other) {
			sp::get<1, T>(*this) = sp::FixpointType::FIXPOINT;
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
