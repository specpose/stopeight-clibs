// Copyright (C) 2009-2016 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#include "stdafx.h"

#include "grapher_impl.h"
//#include "algo_impl.h"
//#include <experimental/algorithm>

namespace grapher {

	/*template<typename T> grapher::Buffer<T>::Buffer(const T* storage, size_t size)
		: buf(std::vector<T>(size))
	{
		buf.assign(storage, (storage + size));
	}
	template grapher::Buffer<float>::Buffer(const float* storage, size_t size);
	template grapher::Buffer<double>::Buffer(const double* storage, size_t size);*/

	template<typename T> grapher::Buffer<T>::Buffer(std::unique_ptr<std::vector<T>>& s)
		: PreloaderIF{ *this }
		, buf(s)
	{
	}
	template grapher::Buffer<float>::Buffer(std::unique_ptr<std::vector<float>>& s);
	template grapher::Buffer<double>::Buffer(std::unique_ptr<std::vector<double>>& s);

	template<typename T> grapher::Buffer<T>::~Buffer() {
	}
	template grapher::Buffer<float>::~Buffer();
	template grapher::Buffer<double>::~Buffer();

	template<typename T> std::vector<T> Buffer<T>::operator()(int samplesPerPixel)
	{
				//par
				//grapher::samples_To_VG(std::experimental::parallel::par, std::begin(buf), std::end(buf), std::begin(buf));//its doing queue stuff internally -> not sycl inside sycl
		return std::vector<T>(0);
	}
	//specialization
	template std::vector<float> Buffer<float>::operator()(int samplesPerPixel);
	//explicit instantiation
	//template template void Buffer<float>::execute_stl(void(iteratorstart, iteratorend), iteratorstart, iteratorend);

	/*template<typename T> size_t Buffer<T>::size()
	{
		return buf.size();
	}
	template size_t Buffer<float>::size();
	template size_t Buffer<double>::size();

	template<typename T> T& Buffer<T>::at(size_t _Pos)
	{
		return buf.at(_Pos);
	}

	template float& Buffer<float>::at(size_t _Pos);
	//template double& Buffer<double>::at(size_t _Pos);

	template<typename T>
	std::_Vector_iterator<std::_Vector_val<std::_Simple_types<T>>> Buffer<T>::rmrbegin()
	{
		return buf.begin();
	}
	template std::_Vector_iterator<std::_Vector_val<std::_Simple_types<float>>> Buffer<float>::rmrbegin();

	template<typename T>
	std::_Vector_iterator<std::_Vector_val<std::_Simple_types<T>>> Buffer<T>::rmrend()
	{
		return buf.end();
	}
	template std::_Vector_iterator<std::_Vector_val<std::_Simple_types<float>>> Buffer<float>::rmrend();*/

}

//weird double defined symbol error for sycl::device from msvc
//#include "algo.cpp"