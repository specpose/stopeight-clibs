// Copyright (C) 2017 Fassio Blatter
// GNU Lesser General Public License, version 2.1

#include "stopeight-clibs/Matrix.h"
#include <math.h>
//#include "GLPlatform.h"
#include <algorithm>

// not available on windows:
#ifndef M_PI
#define M_PI        3.14159265358979323846264338327950288
#endif

template<typename T>template<typename U> Vector<T>::Vector(U x,U y, U z) : std::array<T,3>{T(x),T(y),T(z)}{
}
template Vector<double>::Vector(double x,double y, double z);
template Vector<float>::Vector(float x,float y, float z);
template Vector<float>::Vector(double x,double y, double z);

template<typename T> Vectors<T>::Vectors() : std::vector<Vector<T>>() {
	auto a = sizeof(Vector<T>);
	auto b = (3*sizeof(T));
	if (a!=b)
		throw std::logic_error("Implementation of Vector is not supposed to exceed size of 3 consecutive Ts");
};
template Vectors<float>::Vectors();
template Vectors<double>::Vectors();

template<typename T>void Vectors<T>::apply(Stack<T>& stack) {
	auto& me = *this;
	auto first = std::find_if(std::begin(stack), std::end(stack), [](Matrix<T>& m){ return !m.isSingular();});
	if (first!=std::end(stack)){
#if DEVELOPMENT
		if (*first==Matrix<T>::identity())
			throw std::logic_error("multiplying identity matrix has performance penalty. Check before adding to stack.");
#endif
		Matrix<T> all = *first;
		std::for_each(++first, std::end(stack), [&all](Matrix<T>& m) {
#if DEVELOPMENT
			if (m==Matrix<T>::identity())
				throw std::logic_error("multiplying identity matrix has performance penalty. Check before adding to stack.");
#endif
			if (!m.isSingular())
				all = Matrix<T>::mul(all,m);
		});
		all.apply(me);
	}
	/*std::for_each(std::rbegin(stack), std::rend(stack), [&me](Matrix<T>& m) {
		m.apply(me);
	});*/
}
template void Vectors<float>::apply(Stack<float>& stack);
template void Vectors<double>::apply(Stack<double>& stack);

template<typename T> const T* Vectors<T>::_to_C_array(){
	if (this->size()>0)
		return &(this->at(0))[0];
	else
		return nullptr;
}
template const float* Vectors<float>::_to_C_array();
template const double* Vectors<double>::_to_C_array();

/* Row Major 2D*/
template<typename T>template<typename U> Matrix<T>::Matrix(U x1, U x2, U x3, U y1, U y2, U y3, U z1, U z2, U z3) 
//: elems(std::make_shared<std::array<T,9>>())
{
	auto& e = elems;
	e[0] = x1;
	e[1] = x2;
	e[2] = x3;
	e[3] = y1;
	e[4] = y2;
	e[5] = y3;
	e[6] = z1;
	e[7] = z2;
	e[8] = z3;
}
template Matrix<float>::Matrix(float x1, float x2, float x3, float y1,
							   float y2, float y3, float z1, float z2, float z3);
template Matrix<double>::Matrix(double x1, double x2, double x3, double y1,
							   double y2, double y3, double z1, double z2, double z3);

template<typename T> bool Matrix<T>::operator!=(const Matrix& other){
	return (elems != (other.elems));
}
template bool Matrix<float>::operator!=(const Matrix& other);
template bool Matrix<double>::operator!=(const Matrix& other);

template<typename T> bool Matrix<T>::operator==(const Matrix& other){
	return (elems == (other.elems));
}
template bool Matrix<float>::operator==(const Matrix& other);
template bool Matrix<double>::operator==(const Matrix& other);

template<typename T> std::array<T,9>* Matrix<T>::data() {
	return &elems;
};
template std::array<float,9>* Matrix<float>::data();
template std::array<double,9>* Matrix<double>::data();

template<typename T> Matrix<T> Matrix<T>::identity() {
	auto m = Matrix{	T(1),T(0),T(0),
		T(0),T(1),T(0),
		T(0),T(0),T(1)
	};
	return std::move(m);
}
template Matrix<float> Matrix<float>::identity();
template Matrix<double> Matrix<double>::identity();

template<typename T> T Matrix<T>::det() {
	auto& e = elems;
	auto det = e[0]*e[4]*e[8]+e[1]*e[5]*e[6]+e[2]*e[3]*e[7]-e[0]*e[5]*e[6]-e[1]*e[3]*e[8]-e[2]*e[4]*e[6];
	return det;
}
template float Matrix<float>::det();
template double Matrix<double>::det();

template<typename T> bool Matrix<T>::isSingular(){
#if DEVELOPMENT
	return (det()==0);
#else
	return false;
#endif
}

template<typename T>template<typename U> Matrix<T> Matrix<T>::scale(U x, U y) {
	auto m = Matrix{	T(x),T(0),T(0),
		T(0),T(y),T(0),
		T(0),T(0),T(1)
	};
	return std::move(m);
}
template Matrix<float> Matrix<float>::scale(double x, double y);
template Matrix<double> Matrix<double>::scale(double x, double y);

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
template Matrix<double> Matrix<double>::rotate(double deg);

template<typename T>template<typename U> Matrix<T> Matrix<T>::translate(U x, U y) {
	auto m = Matrix{	T(1),T(0),T(x),
		T(0),T(1),T(y),
		T(0),T(0),T(1)
	};
	return std::move(m);
}
template Matrix<float> Matrix<float>::translate(double x, double y);
template Matrix<double> Matrix<double>::translate(double x, double y);

template<typename T>double Matrix<T>::_radToDeg(double rad) { return rad * (180.0 / M_PI); }//  pi/rad = 180/x, x(pi/rad)=180, x=180/(pi/rad)
template double Matrix<float>::_radToDeg(double rad);
template double Matrix<double>::_radToDeg(double rad);
template<typename T>double Matrix<T>::_degToRad(double deg) { return deg / (180.0 / M_PI); }

template<typename T> Matrix<T> Matrix<T>::mul(const Matrix a, const Matrix b) {
	auto& ae = a.elems;
	auto& be = b.elems;
	auto m = Matrix{	ae[0] * be[0]+ae[1] * be[3]+ae[2] * be[6],	//c00
						ae[0] * be[1]+ae[1] * be[4]+ae[2] * be[7],	//c01
						ae[0] * be[2]+ae[1] * be[5]+ae[2] * be[8],	//c02
						ae[3] * be[0]+ae[4] * be[3]+ae[5] * be[6],	//c10
						ae[3] * be[1]+ae[4] * be[4]+ae[5] * be[7],	//c11
						ae[3] * be[2]+ae[4] * be[5]+ae[5] * be[8],	//c12
						ae[6] * be[0]+ae[7] * be[3]+ae[8] * be[6],	//c20
						ae[6] * be[1]+ae[7] * be[4]+ae[8] * be[7],	//c21
						ae[6] * be[2]+ae[7] * be[5]+ae[8] * be[8]		//c22
	};
	return std::move(m);
}

template<typename T> void Matrix<T>::apply(Vectors<T>& transform) {
	auto& e = elems;
	std::transform(std::begin(transform), std::end(transform), std::begin(transform), [e](Vector<T> a) {
		auto v = a;
		return Vector<T>{	(e[0]*v[0]+e[1]*v[1]+e[2]*v[2]),
			(e[3]*v[0]+e[4]*v[1]+e[5]*v[2]),
			(e[6]*v[0]+e[7]*v[1]+e[8]*v[2])
		};
	});
}

template<typename T> Stack<T>::Stack() : std::vector<Matrix<T>>() {};
template<> Stack<float>::Stack() : std::vector<Matrix<float>>() {};
template<> Stack<double>::Stack() : std::vector<Matrix<double>>() {};

template<typename T> void Stack<T>::identity(){
	this->clear();
}
template void Stack<float>::identity();
template void Stack<double>::identity();

template<typename T>template<typename U> void Stack<T>::scale(U x,U y){
	if (!((1.0==x)&&(1.0==y)))
		this->push_back( Matrix<T>::scale(x,y));
}
template void Stack<float>::scale(double x,double y);
template void Stack<double>::scale(double x,double y);

template<typename T> void Stack<T>::rotate(float deg){
	if (!(deg==0.0f))
		this->push_back( Matrix<T>::rotate(deg));
}
template void Stack<float>::rotate(float deg);
template void Stack<double>::rotate(float deg);

template<typename T>template<typename U> void Stack<T>::translate(U x,U y){
	if (!((0.0==x)&&(0.0==y)))
		this->push_back( Matrix<T>::translate(x, y));
}
template void Stack<float>::translate(double x,double y);
template void Stack<double>::translate(double x,double y);
