// Copyright (C) 2009-2016 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#include "stdafx.h"

#include "grapher_impl.h"

//#include <experimental/algorithm>

//#include "algo.h"

#include "dummy.h"

namespace grapher {

	template<typename T> grapher::Buffer<T>::Buffer() {
	}

	template<typename T> grapher::Buffer<T>::Buffer(std::vector<T>* s)
		: PreloaderIF{ *this }
		, buf(s)
		, _showSamples(1)
		, _samplesPerVector(1)
		, _unitaryLength(1.0f)
	{
		//buf.assign(storage, (storage + size));
	}
	template grapher::Buffer<float>::Buffer(std::vector<float>* s);
	template grapher::Buffer<double>::Buffer(std::vector<double>* s);

	template<typename T> grapher::Buffer<T>::Buffer(std::vector<T>* s, int showSamples, int samplesPerVector, double unitaryLength)
		: grapher::Buffer<T>(s)
	{
		_showSamples = showSamples;
		_samplesPerVector = samplesPerVector;
		_unitaryLength = unitaryLength;
	}
	template grapher::Buffer<float>::Buffer(std::vector<float>* s, int showSamples, int samplesPerVector, double unitaryLength);
	template grapher::Buffer<double>::Buffer(std::vector<double>* s, int showSamples, int samplesPerVector, double unitaryLength);

/*	template<typename T> grapher::Buffer<T>::Buffer(std::unique_ptr<std::vector<T>> s)
//		: PreloaderIF{ *this }
		: PreloaderIF()
//		, buf(s)
		, buf{s}
	{
	}
	template grapher::Buffer<float>::Buffer(std::unique_ptr<std::vector<float>> s);
	template grapher::Buffer<double>::Buffer(std::unique_ptr<std::vector<double>> s);*/

	template<typename T> grapher::Buffer<T>::~Buffer() {
	}
	template grapher::Buffer<float>::~Buffer();
	template grapher::Buffer<double>::~Buffer();

	template<typename T> std::vector<std::pair<float, float>> Buffer<T>::operator()()
	{
		int vectorSize = grapher::samples_To_VG_vectorSize(buf->size(), _samplesPerVector);
		double vectorLength = grapher::samples_To_VG_vectorLength(_showSamples, _unitaryLength);
		std::vector<std::pair<float, float>> output = std::vector<std::pair<float, float>>(vectorSize);
				//par
		//(grapher::samples_To_VG(samplesPerPixel))(std::experimental::parallel::par_vec, std::begin(*buf), std::end(*buf), std::begin(output));
		(grapher::samples_To_VG(_samplesPerVector,vectorLength))(dummy_policy, std::begin(*buf), std::end(*buf), std::begin(output));

		return output;
	}
	//specialization
	template std::vector<std::pair<float, float>> Buffer<float>::operator()();
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
#include "algo.cpp"