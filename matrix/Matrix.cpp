// Copyright (C) 2017 Fassio Blatter
// GNU Lesser General Public License, version 2.1

#include "stopeight-clibs/Matrix.h"
#include <cmath>
#include <algorithm>
//#include "GLPlatform.h"

// not available on windows:
#ifndef M_PI
#define M_PI        3.14159265358979323846264338327950288
#endif

template<typename T, size_t Size, typename tf>template<typename U> Vector<T, Size,tf>& Vector<T,Size,tf>::__init(U x,U y, U z) {
	std::get<0>(coords) = T(x);
	std::get<1>(coords) = T(y);
	std::get<2>(coords) = T(z);
	std::fill(std::begin(coords)+3, std::end(coords), value_type(0));
	return *this;
}
template Vector<double>& Vector<double>::__init(double x,double y, double z);
template Vector<float>& Vector<float>::__init(float x,float y, float z);
template Vector<float>& Vector<float>::__init(double x,double y, double z);

template<typename PodClass,typename T, typename tf> Vectors<PodClass,T,tf>::Vectors() : std::vector<PodClass>() {
};
//template Vectors<Vector<float,3,void>,float,void>::Vectors();
template Vectors<Vector<float>>::Vectors();
template Vectors<Vector<double>>::Vectors();

//propagating: par
template<typename PodClass,typename T, typename tf>void Vectors<PodClass,T,tf>::apply(Stack<PodClass>& stack) {
	auto& me = *this;
	auto first = std::find_if(std::begin(stack), std::end(stack), [](Matrix<PodClass>& m){ return !m.isSingular();});
	if (first!=std::end(stack)){
#if DEVELOPMENT
		if (*first==Matrix<PodClass>::identity())
			throw std::logic_error("multiplying identity matrix has performance penalty. Check before adding to stack.");
#endif
		Matrix<PodClass> all = *first;
		std::for_each(++first, std::end(stack), [&all](Matrix<PodClass>& m) {
#if DEVELOPMENT
			if (m==Matrix<PodClass>::identity())
				throw std::logic_error("multiplying identity matrix has performance penalty. Check before adding to stack.");
#endif
			if (!m.isSingular())
				all = Matrix<PodClass>::mul(all,m);
		});
		all.apply(me);
	}
	/*std::for_each(std::rbegin(stack), std::rend(stack), [&me](Matrix<PodClass,T>& m) {
		m.apply(me);
	});*/
}
template void Vectors<Vector<float>>::apply(Stack<Vector<float>>& stack);
template void Vectors<Vector<double>>::apply(Stack<Vector<double>>& stack);

/* Row Major 2D*/
template<typename PodClass,typename T>template<typename U> Matrix<PodClass,T>::Matrix(U x1, U x2, U x3, U y1, U y2, U y3, U z1, U z2, U z3) {
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
template Matrix<Vector<float>>::Matrix(float x1, float x2, float x3, float y1,
							   float y2, float y3, float z1, float z2, float z3);
template Matrix<Vector<double>>::Matrix(double x1, double x2, double x3, double y1,
							   double y2, double y3, double z1, double z2, double z3);

template<typename PodClass,typename T> std::array<T,9>* Matrix<PodClass,T>::data(){
	return &elems;
}
template std::array<double,9>* Matrix<Vector<double>>::data();
template std::array<float,9>* Matrix<Vector<float>>::data();

template<typename PodClass, typename T> Matrix<PodClass,T> Matrix<PodClass,T>::identity() {
	auto m = Matrix<PodClass>{	T(1),T(0),T(0),
		T(0),T(1),T(0),
		T(0),T(0),T(1)
	};
	return std::move(m);
}
template Matrix<Vector<float>> Matrix<Vector<float>>::identity();
template Matrix<Vector<double>> Matrix<Vector<double>>::identity();

template<typename PodClass, typename T> T Matrix<PodClass,T>::det() {
	auto& e = elems;
	auto det = e[0]*e[4]*e[8]+e[1]*e[5]*e[6]+e[2]*e[3]*e[7]-e[0]*e[5]*e[6]-e[1]*e[3]*e[8]-e[2]*e[4]*e[6];
	return det;
}
template float Matrix<Vector<float>>::det();
template double Matrix<Vector<double>>::det();

template<typename PodClass, typename T> bool Matrix<PodClass,T>::isSingular(){
#if DEVELOPMENT
	return (det()==0);
#else
	return false;
#endif
}

template<typename PodClass, typename T>template<typename U> Matrix<PodClass,T> Matrix<PodClass,T>::scale(U x, U y) {
	auto m = Matrix<PodClass>{	T(x),T(0),T(0),
		T(0),T(y),T(0),
		T(0),T(0),T(1)
	};
	return std::move(m);
}
template Matrix<Vector<float>> Matrix<Vector<float>>::scale(double x, double y);
template Matrix<Vector<double>> Matrix<Vector<double>>::scale(double x, double y);


template<typename PodClass, typename T>template<typename U>  Matrix<PodClass,T> Matrix<PodClass,T>::rotate(U deg) {
	U rad = _degToRad(deg);
	auto m = Matrix<PodClass>{	T(cos(rad)),T(-sin(rad)),T(0),
						T(sin(rad)),T(cos(rad)),T(0),
						T(0),T(0),T(1)
	};
	return std::move(m);
}
template Matrix<Vector<float>> Matrix<Vector<float>>::rotate(double deg);
template Matrix<Vector<double>> Matrix<Vector<double>>::rotate(double deg);

template<typename PodClass, typename T>template<typename U> Matrix<PodClass,T> Matrix<PodClass,T>::translate(U x, U y) {
	auto m = Matrix<PodClass>{	T(1),T(0),T(x),
		T(0),T(1),T(y),
		T(0),T(0),T(1)
	};
	return std::move(m);
}
template Matrix<Vector<float>> Matrix<Vector<float>>::translate(double x, double y);
template Matrix<Vector<double>> Matrix<Vector<double>>::translate(double x, double y);

template<typename PodClass, typename T>double Matrix<PodClass,T>::_radToDeg(double rad) { return rad * (180.0 / M_PI); }//  pi/rad = 180/x, x(pi/rad)=180, x=180/(pi/rad)
template double Matrix<Vector<float>>::_radToDeg(double rad);
template double Matrix<Vector<double>>::_radToDeg(double rad);
template<typename PodClass, typename T>double Matrix<PodClass,T>::_degToRad(double deg) { return deg / (180.0 / M_PI); }

template<typename PodClass, typename T> Matrix<PodClass,T> Matrix<PodClass,T>::mul(const Matrix<PodClass,T> a, const Matrix<PodClass,T> b) {
	auto m = Matrix<PodClass>{	a.elems[0] * b.elems[0]+a.elems[1] * b.elems[3]+a.elems[2] * b.elems[6],	//c00
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
template<typename PodClass, typename T> void Matrix<PodClass,T>::apply(Vectors<PodClass,T>& transform) {
	auto& e = elems;
	std::transform(std::begin(transform), std::end(transform), std::begin(transform), [&e](PodClass a) {
		auto v = a;
		return PodClass{}.__init(	(e[0] * std::get<0>(v.coords) + e[1] * std::get<1>(v.coords) + e[2] * std::get<2>(v.coords)),
			(e[3]*std::get<0>(v.coords)+e[4]* std::get<1>(v.coords) +e[5]* std::get<2>(v.coords)),
			(e[6]* std::get<0>(v.coords) +e[7]* std::get<1>(v.coords) +e[8]* std::get<2>(v.coords))
		);
	});
}

template<typename PodClass> Stack<PodClass>::Stack() : std::vector<Matrix<PodClass>>() {};
template<> Stack<Vector<float>>::Stack() : std::vector<Matrix<Vector<float>>>() {};
template<> Stack<Vector<double>>::Stack() : std::vector<Matrix<Vector<double>>>() {};

template<typename PodClass> void Stack<PodClass>::identity(){
	this->clear();
}
template void Stack<Vector<float>>::identity();
template void Stack<Vector<double>>::identity();

template<typename PodClass>template<typename U> void Stack<PodClass>::scale(U x,U y){
	if (!((1.0==x)&&(1.0==y)))
		this->push_back( Matrix<PodClass>::scale(x,y));
}
template void Stack<Vector<float>>::scale(double x,double y);
template void Stack<Vector<double>>::scale(double x,double y);

template<typename PodClass>template<typename U> void Stack<PodClass>::rotate(U deg){
	if (!(deg==0.0))
		this->push_back( Matrix<PodClass>::rotate(deg));
}
template void Stack<Vector<float>>::rotate(float deg);
template void Stack<Vector<double>>::rotate(double deg);
template void Stack<Vector<double>>::rotate(float deg);

template<typename PodClass>template<typename U> void Stack<PodClass>::translate(U x,U y){
	if (!((0.0==x)&&(0.0==y)))
		this->push_back( Matrix<PodClass>::translate(x, y));
}
template void Stack<Vector<float>>::translate(float x,float y);
template void Stack<Vector<double>>::translate(double x,double y);
