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
		EMPTY,
		SWING,
		CREST,
		DUNE,
		EDGE,
		LEGALSEGMENT,
		CLIFF,
		SPIRAL,
		//Corner??
		STRAIGHT
	};

	enum class covertype {
		EMPTY,
		SWELL,
		SPIRAL,
		ZIGZAG
	};

	//const sp::tctype turns[3] = { tctype::SWING,tctype::CREST,tctype::SPIRAL };
	//pybind POD clash with is_array, alignment?
	//todo
	//make tuple
	//virtual constructor
	//ENABLE_IF does work for classes (not in MSVC doc)
	template<class T,
		typename = typename std::enable_if_t<std::is_arithmetic<T>::value>
	> class timecode {
	public:
		//using std::array<T, 2>::array;
		timecode() {
			clear_types();
		}
		timecode(T x, T y){
			coords = { { x, y } };
			clear_types();
		}
		typedef typename std::array<T, 2>::value_type value_type;
		typedef typename std::array<T, 2>::reference reference;
		sp::FixpointType category() {
			return type;
		}
		void set_category(sp::FixpointType type) {
			this->type = type;
		}
		void clear_types() {
			type = sp::FixpointType::EMPTY;
			tct_type = sp::tctype::EMPTY;
			cov_type = sp::covertype::EMPTY;
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
			
		};*/

		std::array<T, 2> coords;
		sp::FixpointType type;
		sp::tctype tct_type;
		sp::covertype cov_type;
	};
	template<typename T> sp::timecode<T> operator+=(sp::timecode<T>& a, const sp::timecode<T>& b) {
		a.coords[0] = a.coords[0]+b.coords[0];
		a.coords[1] = a.coords[1]+b.coords[1];
		return a;
	};
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
	template<typename T> class result : public std::vector<timecode<T>> {
		using std::vector<timecode<T>>::vector;

		bool invalid = false;
		int cycle_count = 0;
		//next*
	};
	//sp::element static operator+(const sp::element& a, const sp::element& b) { return sp::element{ a.first + b.first, a.second + b.second }; };
	//sp::element static operator-(const sp::element& a, const sp::element& b) { return sp::element{ a.first - b.first, a.second - b.second }; };
	template<typename T> using input_iterator = typename std::enable_if_t < std::is_base_of<std::input_iterator_tag, typename std::iterator_traits<T>::iterator_category>::value>; //&& std::is_arithmetic<typename std::iterator_traits<T>::value_type::value_type>::value>;
		template<typename T> using random_access = typename std::enable_if_t<std::is_base_of<std::random_access_iterator_tag, typename std::iterator_traits<T>::iterator_category>::value>; //&& std::is_arithmetic<typename std::iterator_traits<T>::value_type::value_type>::value>;

	template<typename T> using it_pair = std::pair< typename sp::result<T>::iterator, typename sp::result<T>::iterator >;

	struct sharing_functor_tag {};
	struct propagating_functor_tag : sharing_functor_tag {};
	struct readonly_functor_tag : propagating_functor_tag {};
	template<class R,class... Args> class functor {//: public std::function<R,Args...> {
	public:
		virtual ~functor() {};
		virtual R operator()(Args... arguments) = 0;
	};
	//member variables can be assigned from within operator(), strictly sequential
	template<class R, class... Args> class sharing_functor : public functor<R, Args...> {
	public:
		using functor_category = typename sharing_functor_tag;
	};
	//member variables can be assigned from within operator(), but this is non-blocking
	//is it still sequential when out of order threads terminate earlier?
	template<class R, class... Args> class propagating_functor : public sharing_functor<R, Args...> {
	public:
		using functor_category = typename propagating_functor_tag;
	};
	//member variables (should) not be assigned from within operator()
	template<class R, class... Args> class readonly_functor : public propagating_functor<R, Args...> {
	public:
		using functor_category = typename readonly_functor_tag;
	};
	template<class Ftor> struct functor_traits{
		using functor_category = typename Ftor::functor_category;
	};

}

#endif
