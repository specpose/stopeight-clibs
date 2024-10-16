// Copyright (C) 2009-2016 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#include "stopeight-clibs/grapher_impl.h"
#include "stopeight-clibs/algo.h"

namespace speczilla {

	template<typename T> Buffer<T>::Buffer(std::vector<T>* s)
    : buf(s), _showSamples(s->size()), _samplesPerVector(1)
                , _unitaryLength(1.0), _relative(false), _average(0.0), _angleScale(1.0)
	{
	}
	template Buffer<float>::Buffer(std::vector<float>*);
	template Buffer<double>::Buffer(std::vector<double>*);
	template Buffer<int16_t>::Buffer(std::vector<int16_t>*);

	template<typename T> Buffer<T>::Buffer(std::vector<T>* s, size_t showSamples, size_t samplesPerVector, double unitaryLength, bool relative, double average, double angleScale)
		: Buffer<T>(s)
	{
		_showSamples = showSamples;
		_samplesPerVector = samplesPerVector;
		_unitaryLength = unitaryLength;
		_relative = relative;
		_angleScale = angleScale;
		_average = average;
	}
	template Buffer<float>::Buffer(std::vector<float>*, size_t, size_t, double, bool relative, double, double);
	template Buffer<double>::Buffer(std::vector<double>*, size_t, size_t, double, bool relative, double, double);
	template Buffer<int16_t>::Buffer(std::vector<int16_t>*, size_t, size_t, double, bool relative, double, double);

	template<typename T> Buffer<T>::~Buffer() {}
	template Buffer<float>::~Buffer();
	template Buffer<double>::~Buffer();
	template Buffer<int16_t>::~Buffer();

	template<typename T> std::vector<sp::timecode<T>> Buffer<T>::operator()()
	{
        T vectorLength = grapher::samples_To_VG_vectorLength(_showSamples, _unitaryLength);
		auto output = std::vector<sp::timecode<T>>{};

		if (buf->size() > 2) {
			std::vector<T> differences = std::vector<T>(buf->size(), 0.0);
			std::adjacent_difference(std::begin(*buf), std::end(*buf), std::begin(differences));

			//in general if uneven, middle is on left side
			//-1 differences, -1 size
			auto dvg = (grapher::__differences_To_VG<T>(_samplesPerVector, vectorLength, std::vector<size_t>(1, (((buf->size() - 1) / 2) - 1))));
			if (_relative) {
				angle::relative afunc = angle::relative(std::begin(differences) + 1, std::end(differences),_average,_angleScale);
				output = dvg(differences, afunc);//((vectorSize * 2) + add);
			}
			else {
				angle::independent afunc = angle::independent(std::begin(differences) + 1, std::end(differences),_average,_angleScale);
				output = dvg(differences, afunc);//((vectorSize * 2) + add);
			}			                                                            
		}

		return output;
	}
	template std::vector<sp::timecode<float>> Buffer<float>::operator()();
	template std::vector<sp::timecode<double>> Buffer<double>::operator()();
	template std::vector<sp::timecode<int16_t>> Buffer<int16_t>::operator()();
}