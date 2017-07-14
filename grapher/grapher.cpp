// Copyright (C) 2009-2016 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#include "grapher_impl.h"
#include "algo_impl.h"
#include "dummy.h"

namespace speczilla {

	template<typename T> Buffer<T>::Buffer(std::vector<T>* s)
    : PreloaderIF<T,sp::result<T>>( *this )
		, buf(s)
		, _showSamples(0)
		, _samplesPerVector(1)
		, _unitaryLength(1.0f)
		, _relative(false)
		, _average(0.0f)
		, _angleScale(1.0f)
	{
	}
	template Buffer<float>::Buffer(std::vector<float>* s);
	template Buffer<double>::Buffer(std::vector<double>* s);

	template<typename T> Buffer<T>::Buffer(std::vector<T>* s, int showSamples, int samplesPerVector, double unitaryLength, bool relative, double average, double angleScale)
		: Buffer<T>(s)
	{
		_showSamples = showSamples;
		_samplesPerVector = samplesPerVector;
		_unitaryLength = unitaryLength;
		_relative = relative;
		_angleScale = angleScale;
		_average = average;
	}
	template Buffer<float>::Buffer(std::vector<float>* s, int showSamples, int samplesPerVector, double unitaryLength, bool relative, double average, double angleScale);
	template Buffer<double>::Buffer(std::vector<double>* s, int showSamples, int samplesPerVector, double unitaryLength, bool relative, double average, double angleScale);

/*	template<typename T> Buffer<T>::Buffer(std::unique_ptr<std::vector<T>> s)
//		: PreloaderIF{ *this }
		: PreloaderIF()
//		, buf(s)
		, buf{s}
	{
	}
	template Buffer<float>::Buffer(std::unique_ptr<std::vector<float>> s);
	template Buffer<double>::Buffer(std::unique_ptr<std::vector<double>> s);*/

	template<typename T> Buffer<T>::~Buffer() {
	}
	template Buffer<float>::~Buffer();
	template Buffer<double>::~Buffer();

	template<typename T> sp::result<T> Buffer<T>::operator()()
	{
		const int size = buf->size();
        int vectorSize = grapher::samples_To_VG_vectorSize((size), _samplesPerVector);
        T vectorLength = grapher::samples_To_VG_vectorLength(_showSamples, _unitaryLength);
		std::vector<sp::element<T>> output;

		//par
		//(samples_To_VG(samplesPerPixel))(std::experimental::parallel::par_vec, std::begin(*buf), std::end(*buf), std::begin(output));
		angle::angle* afunc = nullptr;
		if (size > 2) {
			std::vector<T> differences = std::vector<T>(size, 0.0f);
            auto d = grapher::__differences();
            d(dummy_policy, std::begin(*buf), std::end(*buf), std::begin(differences));

			if (_relative) {
				afunc = new angle::relative(std::begin(differences) + 1, std::end(differences),_average,_angleScale);
			}
			else {
				afunc = new angle::independent(std::begin(differences) + 1, std::end(differences),_average,_angleScale);
			}
			output = std::vector<sp::element<T>>{};//((vectorSize * 2) + add);
			
			//in general if uneven, middle is on left side
			//-1 differences, -1 size
            auto dvg = (grapher::__differences_To_VG(_samplesPerVector, vectorLength, std::vector<int>(1, (((size - 1)/ 2) - 1) )));
            dvg(dummy_policy, std::begin(differences) + 1, std::end(differences), std::back_inserter(output), *afunc);
                                                            
			//(samples_To_VG(_samplesPerVector, vectorLength, std::vector<int>(1, (size / 2) - 1)))(dummy_policy, std::begin(*buf), std::end(*buf), std::back_inserter(output), *afunc);

		}
		delete afunc;

		return sp::result<T>{ output };
	}
	//specialization
	template sp::result<float> Buffer<float>::operator()();
	template sp::result<double> Buffer<double>::operator()();

}

//weird double defined symbol error for sycl::device from msvc
//Windows #include "algo.cpp"
