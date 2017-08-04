// Copyright (C) 2017 Fassio Blatter
// GNU Lesser General Public License, version 2.1

#pragma once
#include <array>
#include <vector>

template<typename T> class Vector {
public:
	using value_type = T;

	template<typename U> explicit Vector(U x,U y, U z=1);

	T x();
	T y();
	T z();
private:
	std::array<T,3> elems;
};

template<typename T> class Vectors;

/* Row Major 2D*/
template<typename T> class Matrix {
public:
	friend class Matrix;
	friend class Vectors<T>;
	using value_type = T;
	
	Matrix(Matrix&& other) = default;
	template<typename U> explicit Matrix(U x1, U x2, U x3, U y1, U y2, U y3, U z1, U z2, U z3);
	
	static Matrix identity();

	template<typename U> static Matrix scale(U x, U y);
	
	template<typename U> static Matrix rotate(U deg);
	
	template<typename U> static Matrix translate(U x, U y);
	double static _radToDeg(double rad);
	double static _degToRad(double deg);

private:

	static Matrix mul(const Matrix a, const Matrix b);
	void apply(std::vector<Vector<T>>& transform);
private:
	std::array<T,9> elems;
};

template<typename T> class Stack : public std::vector<Matrix<T>> {
public:
	Stack();

};

template<typename T> class Vectors : public std::vector<Vector<T>> {
public:
	using value_type = T;
	Vectors();
	
	void apply(Stack<T>& stack);
};
