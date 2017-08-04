// Copyright (C) 2017 Fassio Blatter
// GNU Lesser General Public License, version 2.1

#pragma once
#include <array>
#include <vector>

// not available on windows:
#ifndef M_PIl
#define M_PIl		3.1415926535897932384626433832795029L  /* pi */
#endif //M_PIl

template<typename T> class Vector {
public:
	using value_type = T;

	template<typename U> explicit Vector(U x,U y, U z=1) {
		elems[0] = x;
		elems[1] = y;
		elems[2] = z;
	}

	T x() { return elems[0]; };
	T y() { return elems[1]; };
	T z() { return elems[2]; };
private:
	std::array<T,3> elems;
};

template<typename T> class Vectors : public std::vector<Vector<T>> {
public:
	using value_type = T;
	Vectors() : std::vector<Vector<T>>() {};

	void apply(Stack<T>& stack) {
		auto& me = *this;
		/*Matrix<T> all = *std::rbegin(stack);
		std::for_each(++std::rbegin(stack), std::rend(stack), [&all](Matrix<T> m) {
			all = Matrix<T>::mul(all,m);
		});
		all.apply(me);*/
		std::for_each(std::rbegin(stack), std::rend(stack), [&me](Matrix<T> m) {
			m.apply(me);
		});
	}
};

/* Row Major 2D*/
template<typename T> class Matrix {
public:
	friend class Matrix;
	friend class Vectors<T>;
	using value_type = T;
	
	template<typename U> explicit Matrix(U x1, U x2, U x3, U y1, U y2, U y3, U z1, U z2, U z3) {
		elems[0] = x1;
		elems[1] = x2;
		elems[2] = x3;
		elems[3] = y1;
		elems[4] = y2;
		elems[5] = y3;
		elems[6] = z1;
		elems[7] = z2;
		elems[8] = z3;
	}

	static Matrix identity() {
		auto m = Matrix{	T(1),T(0),T(0),
							T(0),T(1),T(0),
							T(0),T(0),T(1)
		};
		return m;
	}

	template<typename U> static Matrix scale(U x, U y) {
		auto m = Matrix{	T(x),T(0),T(0),
							T(0),T(y),T(0),
							T(0),T(0),T(1)
		};
		return m;
	}

	template<typename U> static Matrix rotate(U deg) {
		U rad = _degToRad(deg);
		auto m = Matrix{	cos(T(rad)),-sin(T(rad)),T(0),
							sin(T(rad)),cos(T(rad)),T(0),
							T(0),T(0),T(1)
		};
		return m;
	}

	template<typename U> static Matrix translate(U x, U y) {
		auto m = Matrix{	T(1),T(0),T(x),
							T(0),T(1),T(y),
							T(0),T(0),T(1)
		};
		return m;
	}

	double static _radToDeg(double rad) { return rad * (180.0f / M_PI); }//  pi/rad = 180/x, x(pi/rad)=180, x=180/(pi/rad)
	double static _degToRad(double deg) { return deg / (180.0f / M_PI); }

private:

	static Matrix mul(const Matrix a, const Matrix b) {
		return Matrix{	a.elems[0] * b.elems[0], a.elems[1] * b.elems[3], a.elems[2] * b.elems[6],
						a.elems[3] * b.elems[1], a.elems[4] * b.elems[4], a.elems[5] * b.elems[7],
						a.elems[6] * b.elems[2], a.elems[7] * b.elems[5], a.elems[8] * b.elems[8]
		};
	}

	void apply(std::vector<Vector<T>>& transform) {
		auto& e = elems;
		std::transform(std::begin(transform), std::end(transform), std::begin(transform), [&e](Vector<T> v) {
			return Vector<T>{	(e[0]*v.x()+e[1]*v.y()+e[2]*v.z()),
								(e[3]*v.x()+e[4]*v.y()+e[5]*v.z()),
								(e[6]*v.x()+e[7]*v.y()+e[8]*v.z())
						};
		});
	}

private:
	std::array<T,9> elems;
};

template<typename T> class Stack : public std::vector<Matrix<T>> {
public:
	Stack() : std::vector<Matrix<T>>() {};

};