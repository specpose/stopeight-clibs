// Copyright (C) 2009-2016 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#include "stdafx.h"

#include "grapher_impl.h"

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
		, _average(0.0f)
		, _angleScale(1.0f)
	{
	}
	template grapher::Buffer<float>::Buffer(std::vector<float>* s);
	template grapher::Buffer<double>::Buffer(std::vector<double>* s);

	template<typename T> grapher::Buffer<T>::Buffer(std::vector<T>* s, int showSamples, int samplesPerVector, double unitaryLength, bool relative, double average, double angleScale)
		: grapher::Buffer<T>(s)
	{
		_showSamples = showSamples;
		_samplesPerVector = samplesPerVector;
		_unitaryLength = unitaryLength;
		_relative = relative;
		_angleScale = angleScale;
		_average = average;
	}
	template grapher::Buffer<float>::Buffer(std::vector<float>* s, int showSamples, int samplesPerVector, double unitaryLength, bool relative, double average, double angleScale);
	template grapher::Buffer<double>::Buffer(std::vector<double>* s, int showSamples, int samplesPerVector, double unitaryLength, bool relative, double average, double angleScale);

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
		int vectorSize = grapher::samples_To_VG_vectorSize((size), _samplesPerVector);
		double vectorLength = grapher::samples_To_VG_vectorLength(_showSamples, _unitaryLength);
		std::vector<sp::element> output;

		//par
		//(grapher::samples_To_VG(samplesPerPixel))(std::experimental::parallel::par_vec, std::begin(*buf), std::end(*buf), std::begin(output));
		grapher::averageScaled* afunc = nullptr;
		if (size > 0) {
			std::vector<double> differences = std::vector<double>(size, 0.0f);
			__differences()(dummy_policy, std::begin(*buf), std::end(*buf), std::begin(differences));

			if (_relative) {
				afunc = new relative(std::begin(differences) + 1, std::end(differences),_average,_angleScale);
			}
			else {
				afunc = new independent(std::begin(differences) + 1, std::end(differences),_average,_angleScale);
			}
			output = std::vector<sp::element>{};//((vectorSize * 2) + add);

			(__differences_To_VG(_samplesPerVector, vectorLength, std::vector<int>(1, (size / 2) - 1)))(dummy_policy, std::begin(differences) + 1, std::end(differences), std::back_inserter(output), *afunc);
			//(grapher::samples_To_VG(_samplesPerVector, vectorLength, std::vector<int>(1, (size / 2) - 1)))(dummy_policy, std::begin(*buf), std::end(*buf), std::back_inserter(output), *afunc);

		}
		delete afunc;

		return sp::result{ output };
	}
	//specialization
	template sp::result Buffer<float>::operator()();
	template sp::result Buffer<double>::operator()();

}

//weird double defined symbol error for sycl::device from msvc
#include "algo.cpp"