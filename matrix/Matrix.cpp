// Copyright (C) 2017 Fassio Blatter
// GNU Lesser General Public License, version 2.1

#include "stopeight-clibs/Matrix.h"
#include "stopeight-clibs/shared_types.h"
#include <cmath>
#include <algorithm>
//#include "GLPlatform.h"

// not available on windows:
#ifndef M_PI
#define M_PI        3.14159265358979323846264338327950288
#endif

template<typename T, size_t Size, typename tf> Vector<T, Size,tf>& Vector<T,Size,tf>::__init(std::initializer_list<T> list) {
	std::copy(std::begin(list),std::end(list),std::begin(coords));
	std::fill(std::begin(coords)+list.size(), std::end(coords), T(0));
	return *this;
}
template Vector<double>& Vector<double>::__init(std::initializer_list<double>);
template Vector<float>& Vector<float>::__init(std::initializer_list<float>);

//propagating: par
template<typename Container, typename tf>void Vectors<Container,tf>::apply(Stack<Container,PodClass>& stack) {
	auto& me = *this;
	auto first = std::find_if(std::begin(stack), std::end(stack), [](Matrix<Container,PodClass>& m){ return !m.isSingular();});
	if (first!=std::end(stack)){
#if DEVELOPMENT
		if (*first==Matrix<Container,PodClass>::identity())
			throw std::logic_error("multiplying identity matrix has performance penalty. Check before adding to stack.");
#endif
		Matrix<Container,PodClass> all = *first;
		std::for_each(++first, std::end(stack), [&all](Matrix<Container,PodClass>& m) {
#if DEVELOPMENT
			if (m==Matrix<Container,PodClass>::identity())
				throw std::logic_error("multiplying identity matrix has performance penalty. Check before adding to stack.");
#endif
			if (!m.isSingular())
				all = Matrix<Container,PodClass>::mul(all,m);
		});
		all.apply(me);
	}
	/*std::for_each(std::rbegin(stack), std::rend(stack), [&me](Matrix<PodClass,T>& m) {
		m.apply(me);
	});*/
}
template void Vectors<std::vector<Vector<float>>>::apply(Stack<std::vector<Vector<float>>>& stack);
template void Vectors<std::vector<Vector<double>>>::apply(Stack<std::vector<Vector<double>>>& stack);
//todo span
template void Vectors<std::vector<sp::timecode<float>>>::apply(Stack<std::vector<sp::timecode<float>>>& stack);
template void Vectors<std::vector<sp::timecode<double>>>::apply(Stack<std::vector<sp::timecode<double>>>& stack);

/* Row Major 2D*/
template<typename Container, typename PodClass,typename T>template<typename U> Matrix<Container,PodClass,T>::Matrix(U x1, U x2, U x3, U y1, U y2, U y3, U z1, U z2, U z3) {
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
template Matrix<std::vector<Vector<float>>>::Matrix(float x1, float x2, float x3, float y1,
							   float y2, float y3, float z1, float z2, float z3);
template Matrix<std::vector<Vector<double>>>::Matrix(double x1, double x2, double x3, double y1,
							   double y2, double y3, double z1, double z2, double z3);
//todo span
template Matrix<std::vector<sp::timecode<float>>>::Matrix(float x1, float x2, float x3, float y1,
							   float y2, float y3, float z1, float z2, float z3);
template Matrix<std::vector<sp::timecode<double>>>::Matrix(double x1, double x2, double x3, double y1,
							   double y2, double y3, double z1, double z2, double z3);

template<typename Container,typename PodClass,typename T> std::array<T,9>* Matrix<Container,PodClass,T>::data(){
	return &elems;
}
template std::array<double,9>* Matrix<std::vector<Vector<double>>>::data();
template std::array<float,9>* Matrix<std::vector<Vector<float>>>::data();
//todo span
template std::array<double,9>* Matrix<std::vector<sp::timecode<double>>>::data();
template std::array<float,9>* Matrix<std::vector<sp::timecode<float>>>::data();

template<typename Container,typename PodClass, typename T> Matrix<Container,PodClass,T> Matrix<Container,PodClass,T>::identity() {
	auto m = Matrix<Container,PodClass>{	T(1),T(0),T(0),
		T(0),T(1),T(0),
		T(0),T(0),T(1)
	};
	return std::move(m);
}
template Matrix<std::vector<Vector<float>>> Matrix<std::vector<Vector<float>>>::identity();
template Matrix<std::vector<Vector<double>>> Matrix<std::vector<Vector<double>>>::identity();

template<typename Container, typename PodClass, typename T> T Matrix<Container,PodClass,T>::det() {
	auto& e = elems;
	auto det = e[0]*e[4]*e[8]+e[1]*e[5]*e[6]+e[2]*e[3]*e[7]-e[0]*e[5]*e[6]-e[1]*e[3]*e[8]-e[2]*e[4]*e[6];
	return det;
}
template float Matrix<std::vector<Vector<float>>>::det();
template double Matrix<std::vector<Vector<double>>>::det();

template<typename Container,typename PodClass, typename T> bool Matrix<Container,PodClass,T>::isSingular(){
#if DEVELOPMENT
	return (det()==0);
#else
	return false;
#endif
}

template<typename Container, typename PodClass, typename T>template<typename U> Matrix<Container,PodClass,T> Matrix<Container,PodClass,T>::scale(U x, U y) {
	auto m = Matrix<Container,PodClass>{	T(x),T(0),T(0),
		T(0),T(y),T(0),
		T(0),T(0),T(1)
	};
	return std::move(m);
}
template Matrix<std::vector<Vector<float>>> Matrix<std::vector<Vector<float>>>::scale(double x, double y);
template Matrix<std::vector<Vector<double>>> Matrix<std::vector<Vector<double>>>::scale(double x, double y);
//todo span
template Matrix<std::vector<sp::timecode<float>>> Matrix<std::vector<sp::timecode<float>>>::scale(double x, double y);
template Matrix<std::vector<sp::timecode<double>>> Matrix<std::vector<sp::timecode<double>>>::scale(double x, double y);

template<typename Container, typename PodClass, typename T>template<typename U>  Matrix<Container,PodClass,T> Matrix<Container,PodClass,T>::rotate(U deg) {
	U rad = _degToRad(deg);
	auto m = Matrix<Container,PodClass>{	T(cos(rad)),T(-sin(rad)),T(0),
						T(sin(rad)),T(cos(rad)),T(0),
						T(0),T(0),T(1)
	};
	return std::move(m);
}
template Matrix<std::vector<Vector<float>>> Matrix<std::vector<Vector<float>>>::rotate(double deg);
template Matrix<std::vector<Vector<double>>> Matrix<std::vector<Vector<double>>>::rotate(double deg);
//todo span
template Matrix<std::vector<sp::timecode<float>>> Matrix<std::vector<sp::timecode<float>>>::rotate(double deg);
template Matrix<std::vector<sp::timecode<double>>> Matrix<std::vector<sp::timecode<double>>>::rotate(double deg);

template<typename Container, typename PodClass, typename T>template<typename U> Matrix<Container,PodClass,T> Matrix<Container,PodClass,T>::translate(U x, U y) {
	auto m = Matrix<Container,PodClass>{	T(1),T(0),T(x),
		T(0),T(1),T(y),
		T(0),T(0),T(1)
	};
	return std::move(m);
}
template Matrix<std::vector<Vector<float>>> Matrix<std::vector<Vector<float>>>::translate(double x, double y);
template Matrix<std::vector<Vector<double>>> Matrix<std::vector<Vector<double>>>::translate(double x, double y);

template<typename Container, typename PodClass, typename T>double Matrix<Container,PodClass,T>::_radToDeg(double rad) { return rad * (180.0 / M_PI); }//  pi/rad = 180/x, x(pi/rad)=180, x=180/(pi/rad)
template double Matrix<std::vector<Vector<float>>>::_radToDeg(double rad);
template double Matrix<std::vector<Vector<double>>>::_radToDeg(double rad);
template<typename Container, typename PodClass, typename T>double Matrix<Container,PodClass,T>::_degToRad(double deg) { return deg / (180.0 / M_PI); }

template<typename Container, typename PodClass, typename T> Matrix<Container, PodClass,T> Matrix<Container,PodClass,T>::mul(const Matrix<Container,PodClass,T> a, const Matrix<Container,PodClass,T> b) {
	auto m = Matrix<Container,PodClass>{	a.elems[0] * b.elems[0]+a.elems[1] * b.elems[3]+a.elems[2] * b.elems[6],	//c00
						a.elems[0] * b.elems[1]+a.elems[1] * b.elems[4]+a.elems[2] * b.elems[7],	//c01
						a.elems[0] * b.elems[2]+a.elems[1] * b.elems[5]+a.elems[2] * b.elems[8],	//c02
						a.elems[3] * b.elems[0]+a.elems[4] * b.elems[3]+a.elems[5] * b.elems[6],	//c10
						a.elems[3] * b.elems[1]+a.elems[4] * b.elems[4]+a.elems[5] * b.elems[7],	//c11
						a.elems[3] * b.elems[2]+a.elems[4] * b.elems[5]+a.elems[5] * b.elems[8],	//c12
						a.elems[6] * b.elems[0]+a.elems[7] * b.elems[3]+a.elems[8] * b.elems[6],	//c20
						a.elems[6] * b.elems[1]+a.elems[7] * b.elems[4]+a.elems[8] * b.elems[7],	//c21
						a.elems[6] * b.elems[2]+a.elems[7] * b.elems[5]+a.elems[8] * b.elems[8]		//c22
	};
	return std::move(m);
}

//this may have to be compiled with a different compiler: NOT HEADER ONLY
//readonly: par_unseq
template<typename Container, typename PodClass, typename T> void Matrix<Container,PodClass,T>::apply(Vectors<Container>& transform) {
	auto& e = elems;
	std::transform(std::begin(transform), std::end(transform), std::begin(transform), [&e](PodClass a) {
		auto v = a;
		return PodClass{}.__init(	{(e[0] * std::get<0>(v.coords) + e[1] * std::get<1>(v.coords) + e[2] * std::get<2>(v.coords)),
			(e[3]*std::get<0>(v.coords)+e[4]* std::get<1>(v.coords) +e[5]* std::get<2>(v.coords)),
			(e[6]* std::get<0>(v.coords) +e[7]* std::get<1>(v.coords) +e[8]* std::get<2>(v.coords))}
		);
	});
}

template<typename Container, typename PodClass> Stack<Container,PodClass>::Stack() : std::vector<Matrix<Container,PodClass>>() {};
template<> Stack<std::vector<Vector<float>>>::Stack() : std::vector<Matrix<std::vector<Vector<float>>>>() {};
template<> Stack<std::vector<Vector<double>>>::Stack() : std::vector<Matrix<std::vector<Vector<double>>>>() {};
//todo span
template<> Stack<std::vector<sp::timecode<float>>>::Stack() : std::vector<Matrix<std::vector<sp::timecode<float>>>>() {};
template<> Stack<std::vector<sp::timecode<double>>>::Stack() : std::vector<Matrix<std::vector<sp::timecode<double>>>>() {};

template<typename Container,typename PodClass> void Stack<Container,PodClass>::identity(){
	this->clear();
}
template void Stack<std::vector<Vector<float>>>::identity();
template void Stack<std::vector<Vector<double>>>::identity();
//todo span
template void Stack<std::vector<sp::timecode<float>>>::identity();
template void Stack<std::vector<sp::timecode<double>>>::identity();

template<typename Container,typename PodClass>template<typename U> void Stack<Container,PodClass>::scale(U x,U y){
	if (!(( U(1.0)==x)&&( U(1.0)==y)))
		this->push_back( Matrix<Container,PodClass>::scale(x,y));
}
template void Stack<std::vector<Vector<float>>>::scale(float x,float y);
template void Stack<std::vector<Vector<float>>>::scale(double x, double y);
template void Stack<std::vector<Vector<double>>>::scale(double x,double y);
//todo span
template void Stack<std::vector<sp::timecode<float>>>::scale(float x,float y);
template void Stack<std::vector<sp::timecode<double>>>::scale(double x,double y);

template<typename Container,typename PodClass>template<typename U> void Stack<Container,PodClass>::rotate(U deg){
	if (!(deg== U(0.0) ))
		this->push_back( Matrix<Container,PodClass>::rotate(deg));
}
template void Stack<std::vector<Vector<float>>>::rotate(float deg);
template void Stack<std::vector<Vector<float>>>::rotate(double deg);
template void Stack<std::vector<Vector<double>>>::rotate(double deg);
//todo span
template void Stack<std::vector<sp::timecode<double>>>::rotate(double deg);
template void Stack<std::vector<sp::timecode<float>>>::rotate(float deg);

template<typename Container,typename PodClass>template<typename U> void Stack<Container,PodClass>::translate(U x,U y){
	if (!(( U(0.0)==x)&&( U(0.0)==y)))
		this->push_back( Matrix<Container,PodClass>::translate(x, y));
}
template void Stack<std::vector<Vector<float>>>::translate(float x,float y);
template void Stack<std::vector<Vector<float>>>::translate(double x, double y);
template void Stack<std::vector<Vector<double>>>::translate(double x,double y);
template void Stack<std::vector<sp::timecode<float>>>::translate(float x,float y);
template void Stack<std::vector<sp::timecode<double>>>::translate(double x,double y);