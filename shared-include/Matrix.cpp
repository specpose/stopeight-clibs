// Copyright (C) 2017 Fassio Blatter
// GNU Lesser General Public License, version 2.1

#include "Matrix.h"
#include <Math.h>

// not available on windows:
#ifndef M_PIl
#define M_PIl		3.1415926535897932384626433832795029L  /* pi */
#endif //M_PIl

template<typename T>template<typename U> Vector<T>::Vector(U x,U y, U z) {
	elems[0] = x;
	elems[1] = y;
	elems[2] = z;
}
template Vector<double>::Vector(double x,double y, double z);
template Vector<float>::Vector(float x,float y, float z);
template Vector<float>::Vector(double x,double y, double z);


template<typename T>T Vector<T>::x() { return elems[0]; };
template float Vector<float>::x();
template<typename T>T Vector<T>::y() { return elems[1]; };
template float Vector<float>::y();
template<typename T>T Vector<T>::z() { return elems[2]; };

template<typename T> Vectors<T>::Vectors() : std::vector<Vector<T>>() {};
template Vectors<float>::Vectors();


template<typename T>void Vectors<T>::apply(Stack<T>& stack) {
	auto& me = *this;
	/*Matrix<T> all = *std::rbegin(stack);
		std::for_each(++std::rbegin(stack), std::rend(stack), [&all](Matrix<T>& m) {
	 all = Matrix<T>::mul(all,m);
		});
		all.apply(me);*/
	std::for_each(std::rbegin(stack), std::rend(stack), [&me](Matrix<T>& m) {
		m.apply(me);
	});
}
template void Vectors<float>::apply(Stack<float>& stack);

/* Row Major 2D*/
template<typename T>template<typename U> Matrix<T>::Matrix(U x1, U x2, U x3, U y1, U y2, U y3, U z1, U z2, U z3) {
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
template Matrix<float>::Matrix(float x1, float x2, float x3, float y1,
							   float y2, float y3, float z1, float z2, float z3);

template<typename T> Matrix<T> Matrix<T>::identity() {
	auto m = Matrix{	T(1),T(0),T(0),
		T(0),T(1),T(0),
		T(0),T(0),T(1)
	};
	return std::move(m);
}
template Matrix<float> Matrix<float>::identity();


template<typename T>template<typename U> Matrix<T> Matrix<T>::scale(U x, U y) {
	auto m = Matrix{	T(x),T(0),T(0),
		T(0),T(y),T(0),
		T(0),T(0),T(1)
	};
	return std::move(m);
}
template Matrix<float> Matrix<float>::scale(double x, double y);

template<typename T>template<typename U>  Matrix<T> Matrix<T>::rotate(U deg) {
	U rad = _degToRad(deg);
	auto m = Matrix<T>{	T(cos(rad)),T(-sin(rad)),T(0),
						T(sin(rad)),T(cos(rad)),T(0),
						T(0),T(0),T(1)
	};
	//auto m = Matrix<T>(0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f);
	return std::move(m);
}
template Matrix<float> Matrix<float>::rotate(double deg);

template<typename T>template<typename U> Matrix<T> Matrix<T>::translate(U x, U y) {
	auto m = Matrix{	T(1),T(0),T(x),
		T(0),T(1),T(y),
		T(0),T(0),T(1)
	};
	return std::move(m);
}
template Matrix<float> Matrix<float>::translate(double x, double y);

template<typename T>double Matrix<T>::_radToDeg(double rad) { return rad * (180.0f / M_PI); }//  pi/rad = 180/x, x(pi/rad)=180, x=180/(pi/rad)
template double Matrix<float>::_radToDeg(double rad);
template<typename T>double Matrix<T>::_degToRad(double deg) { return deg / (180.0f / M_PI); }

template<typename T> Matrix<T> Matrix<T>::mul(const Matrix a, const Matrix b) {
	return Matrix{	a.elems[0] * b.elems[0], a.elems[1] * b.elems[3], a.elems[2] * b.elems[6],
		a.elems[3] * b.elems[1], a.elems[4] * b.elems[4], a.elems[5] * b.elems[7],
		a.elems[6] * b.elems[2], a.elems[7] * b.elems[5], a.elems[8] * b.elems[8]
	};
}

template<typename T> void Matrix<T>::apply(std::vector<Vector<T>>& transform) {
	auto& e = elems;
	std::transform(std::begin(transform), std::end(transform), std::begin(transform), [&e](Vector<T> v) {
		return Vector<T>{	(e[0]*v.x()+e[1]*v.y()+e[2]*v.z()),
			(e[3]*v.x()+e[4]*v.y()+e[5]*v.z()),
			(e[6]*v.x()+e[7]*v.y()+e[8]*v.z())
		};
	});
}

template<typename T> Stack<T>::Stack() : std::vector<Matrix<T>>() {};
template<> Stack<float>::Stack() : std::vector<Matrix<float>>() {};

