// Copyright (C) 2017 Fassio Blatter
// GNU Lesser General Public License, version 2.1

#pragma once
#include <array>
#include <vector>
#include <iterator>

template<typename T, size_t Size = 3,
	typename tf= typename std::enable_if_t<std::is_arithmetic<T>::value>
	> class Vector {
public:
	using element = typename std::array<T, Size>;
	typedef typename element::value_type value_type;
	typedef typename element::reference reference;

	//template<typename U> Vector(U x,U y, U z=1)=delete;
	template<typename U> Vector<T, Size,tf>& __init(U x = U(0), U y = U(0), U z = U(1));

	std::array<T, Size> coords;
};

template<typename Container, typename PodClass= typename Container::value_type, typename T= typename PodClass::value_type, typename tf = typename std::enable_if_t<std::is_pod<PodClass>::value>> class Vectors;//forward declaration! same as in real declaration below

/* Row Major 2D*/
template<typename Container, typename PodClass= typename Container::value_type,typename T = typename PodClass::value_type> class Matrix {
public:
	friend class Matrix;
	friend class Vectors<Container,PodClass,T>;
	
	Matrix(const Matrix& other) = default;
	Matrix(Matrix&& other) = default;
	template<typename U> explicit Matrix(U x1, U x2, U x3, U y1, U y2, U y3, U z1, U z2, U z3);
	std::array<T,9>* data();

	Matrix& operator=(const Matrix& other) = default;
	bool operator!=(const Matrix& other){
		return (elems != other.elems);
	}
	bool operator==(const Matrix& other){
		return (elems == other.elems);
	}
	
	static Matrix identity();

	T det();
	
	bool isSingular();
	
	template<typename U> static Matrix scale(U x, U y);
	
	template<typename U> static Matrix rotate(U deg);
	
	template<typename U> static Matrix translate(U x, U y);
	double static _radToDeg(double rad);
	double static _degToRad(double deg);

private:
	static Matrix mul(const Matrix a, const Matrix b);
	void apply(Vectors<Container,PodClass,T>& transform);
private:
	std::array<T,9> elems;
};

//todo disable type conversions here?
template<typename Container, typename PodClass= typename Container::value_type> class Stack : public std::vector<Matrix<Container>> {
	using T = typename PodClass::value_type;

public:
	Stack();
	
	void identity();
	template<typename U> void scale(U x, U y);
	//this was void rotate(float deg); why?!
	template<typename U> void rotate(U deg);
	template<typename U> void translate(U x, U y);
};

template<typename Container,
	typename PodClass,//= typename Container::value_type,
	typename T,// = typename PodClass::value_type,
	typename// = typename std::enable_if_t<std::is_pod<PodClass>::value>
> // same as in forward declaration above!
class Vectors : public Container {
	//todo
	//we cannot make Vectors a pod type
	//AND std::vector can not use memory of numpy_array; (they're both in stack)
	//-> no move constructor from numpy array
public:
	//Vectors();
	using Container::vector;
	
	void apply(Stack<Container,PodClass>& stack);

	const T* _to_C_array(){
		if (this->size()>0)
			return &(this->at(0))[0];
		else
			return nullptr;
	}
};
