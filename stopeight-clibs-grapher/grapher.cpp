// Copyright (C) 2009-2016 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#include "stdafx.h"

#include "grapher_impl.h"

namespace grapher {

	template<typename T> grapher::Buffer<T>::Buffer(const T* storage, size_t size)
		: buf(std::vector<T>(size))
	{
		buf.assign(storage, (storage + size));
	}
	template grapher::Buffer<float>::Buffer(const float* storage, size_t size);
	template grapher::Buffer<double>::Buffer(const double* storage, size_t size);

	template<typename T> grapher::Buffer<T>::~Buffer() {
	}
	template grapher::Buffer<float>::~Buffer();
	template grapher::Buffer<double>::~Buffer();

	//template<typename T> template<typename... stl_args> void Buffer<T>::execute_stl(void(*_func)(stl_args...))
	template<typename T> void Buffer<T>::execute_stl()
	{
				//par
				//grapher::samples_To_VG(task1, sycl::helpers::begin(buf), sycl::helpers::end(buf), sycl::helpers::begin(buf));//its doing queue stuff internally -> not sycl inside sycl
	}
	//specialization
	//template<> template<typename... stl_args> void Buffer<float>::execute_stl(void(*_func)(stl_args...));
	template void Buffer<float>::execute_stl();
	//explicit instantiation
	//template template void Buffer<float>::execute_stl(void(iteratorstart, iteratorend), iteratorstart, iteratorend);

	template<typename T> size_t Buffer<T>::size()
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
	template std::_Vector_iterator<std::_Vector_val<std::_Simple_types<float>>> Buffer<float>::rmrend();

}

//weird double defined symbol error for sycl::device from msvc
//#include "algo.cpp"