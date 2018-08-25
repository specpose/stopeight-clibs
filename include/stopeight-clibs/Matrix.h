// Copyright (C) 2017 Fassio Blatter
// GNU Lesser General Public License, version 2.1

#pragma once
#include <array>
#include <vector>
#include <iterator>
#include <memory>

template<typename T> class Vector : public std::array<T,3>{
public:
	using value_type = T;

	template<typename U> explicit Vector(U x,U y, U z=1);

};

template<typename T> class Vectors;

template<typename T> using basetype = std::iterator<std::forward_iterator_tag,Vectors<T>>;

/* Row Major 2D*/
template<typename T> class Matrix {
public:
	friend class Matrix;
	friend class Vectors<T>;
	using value_type = T;
	
	Matrix(const Matrix& other) = default;
	Matrix(Matrix&& other) = default;
	template<typename U> explicit Matrix(U x1, U x2, U x3, U y1, U y2, U y3, U z1, U z2, U z3);
	Matrix& operator=(const Matrix& other) = default;
	bool operator!=(const Matrix& other);
	bool operator==(const Matrix& other);
	std::shared_ptr<std::array<T,9>> data();
	
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
	void apply(Vectors<T>& transform);
private:
	std::shared_ptr<std::array<T,9>> elems;
};

template<typename T> class Stack : public std::vector<Matrix<T>> {
public:
	Stack();
	
	void identity();
	template<typename U> void scale(U x, U y);
	void rotate(float deg);
	template<typename U> void translate(U x, U y);

};

template<typename T> class Vectors : public std::vector<Vector<T>> {
public:
	Vectors();
	//using value_type = typename std::vector<Vector<T>>::value_type;
	void push_back(const typename std::vector<Vector<T>>::value_type val){
		return std::vector<Vector<T>>::push_back(val);
	}
	
	void apply(Stack<T>& stack);

	const T* _to_C_array();
};
