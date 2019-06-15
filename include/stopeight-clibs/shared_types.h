// Copyright (C) 2017 Fassio Blatter
// GNU Lesser General Public License, version 2.1

#ifndef SHARED_TYPES_H
#define SHARED_TYPES_H

#include <vector>
#include <array>
#include <tuple>
#include <cassert>

#include"Matrix.h"

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
	class moogli {
	public:
		decltype(auto) data() { return &(this->myd); };

		double myd[3];
	};
	//const sp::tctype turns[3] = { tctype::SWING,tctype::CREST,tctype::SPIRAL };
	//ENABLE_IF does work for classes (not in MSVC doc)
	template<class T, size_t Size = 2,
		typename = typename std::enable_if_t<std::is_arithmetic<T>::value
		>
	> struct timecode {//inheritance AND data members present, or tuple: not pod
		template<typename T> using element = typename std::array<T, Size>;
		//timecode(std::initializer_list<T>) = delete;
		timecode<T,Size>& operator=(std::initializer_list<T>& other) {
			static_assert(other.size() == std::tuple_size<element<T>>::value);
			auto e = element<T>{other};
			this->coords = e;
			this->clear_types();
			return *this;
		}
		timecode<T,Size>& operator+=(const timecode<T,Size>& other) {
			//assert(this->type==FixpointType::EMPTY && other.type==FixpointType::EMPTY);
			std::transform(std::begin(this->coords), std::end(this->coords), std::begin(other.coords), std::begin(this->coords), std::plus<T>{});
			return *this;
		}
		bool operator==(const timecode<T,Size>& other) {
			return std::equal(std::begin(this->coords), std::end(this->coords),std::begin(other.coords)) ;
		}

		typedef typename element<T>::value_type value_type;
		typedef typename element<T>::reference reference;
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

		value_type get_x() { return coords[0]; };
		value_type get_y() { return coords[1]; };
		void set_x(const reference other) { coords[0] = other; };
		void set_y(const reference other) { coords[1] = other; };

	//public: //assignment operator does not work when private members present and no CLASS constructor
	//construction by order of appearance!
		element<T> coords;//1
		sp::FixpointType type;//1
		sp::tctype tct_type;//3
		sp::covertype cov_type;//4
	};
	/*template<typename T> timecode<T> make_timecode(T x,T y,FixpointType type= FixpointType::EMPTY) {
		timecode<T> tc;
		tc.set_x(x);
		tc.set_y(y);
		tc.set_category(type);
		return tc;
	};*/
	class Test0 : public std::array<double, 3> {
	public:
		//Test() = delete;//not a pod
		//using std::array<double, 3>::array;
	};
	class Test1 : public Test0 {

	};
	class Test2 {
	public:
		//Test2() = delete;//not a pod
		double x, y, z;
	};
	template<typename T, size_t Size = 2,
			typename = typename std::enable_if_t<std::is_pod<timecode<T,Size>>::value>
	> class result : public std::vector<timecode<T,Size>> {
	public:
		result() : std::vector<timecode<T,Size>>() {
			timecode<T,Size> tc = { 0,0 };
			tc.tct_type = tctype::EMPTY;
		};
		result(size_t n) : std::vector<timecode<T,Size>>(n) {
			timecode<T,Size> tc = { 0,0 };
			tc.clear_types();
			std::fill(std::begin(this), std::end(this), tc);
		};
		result(std::initializer_list<T>) = delete;

		bool invalid = false;
		int cycle_count = 0;
		//next*
	};

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
