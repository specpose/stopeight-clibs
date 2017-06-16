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
		, _showSamples(0)
		, _samplesPerVector(1)
		, _unitaryLength(1.0f)
		, _relative(false)
	{
	}
	template grapher::Buffer<float>::Buffer(std::vector<float>* s);
	template grapher::Buffer<double>::Buffer(std::vector<double>* s);

	template<typename T> grapher::Buffer<T>::Buffer(std::vector<T>* s, int showSamples, int samplesPerVector, double unitaryLength, bool relative)
		: grapher::Buffer<T>(s)
	{
		_showSamples = showSamples;
		_samplesPerVector = samplesPerVector;
		_unitaryLength = unitaryLength;
		_relative = relative;
	}
	template grapher::Buffer<float>::Buffer(std::vector<float>* s, int showSamples, int samplesPerVector, double unitaryLength, bool relative);
	template grapher::Buffer<double>::Buffer(std::vector<double>* s, int showSamples, int samplesPerVector, double unitaryLength, bool relative);

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

	template<typename T> sp::result Buffer<T>::operator()()
	{
		const int size = buf->size();
		int add = 0;
		if ((size % 2) != 0)
			add = 1;
		//	throw std::exception("Uneven number of samples can not be split in two");
		int vectorSize = grapher::samples_To_VG_vectorSize((size/2), _samplesPerVector);
		double vectorLength = grapher::samples_To_VG_vectorLength(_showSamples, _unitaryLength);
		std::vector<sp::element> output;

		//par
		//(grapher::samples_To_VG(samplesPerPixel))(std::experimental::parallel::par_vec, std::begin(*buf), std::end(*buf), std::begin(output));
		grapher::averageScaled* afunc;
		if (_relative) {
			afunc = new relative(0.0f);
		}
		else {
			afunc = new independent(0.0f);
		}
		if (vectorSize > 1) {
			//+ hard-coded middle; only if samplesPervector !=1
			if (_samplesPerVector != 1)
				add++;
			output = std::vector<sp::element>((vectorSize * 2) + add);
			(grapher::samples_To_VG(_samplesPerVector, vectorLength,std::vector<int>(1,size/2)))(dummy_policy, std::begin(*buf), std::end(*buf), std::begin(output), *afunc);
		
		}
		else if (vectorSize ==1) {
			//case add=1 untested
			add += 2;
			output = std::vector<sp::element>((vectorSize * 2)+ add);
			(grapher::samples_To_VG(_samplesPerVector, vectorLength, std::vector<int>(1, 1)))(dummy_policy, std::begin(*buf), std::end(*buf), std::begin(output), *afunc);
		}
		delete afunc;

		return sp::result{ output };
	}
	//specialization
	template sp::result Buffer<float>::operator()();
	template sp::result Buffer<double>::operator()();
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