// Copyright (C) 2009-2016 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#include "stopeight-clibs/grapher_gpx.h"
#include "stopeight-clibs/algo.h"
#include "stopeight-clibs/error.hpp"

namespace speczilla {

	template<typename T> VectorGraph2<T>::VectorGraph2(std::vector<T>* s)
    : output(std::vector<sp::timecode<T>>{}), buf(s), _showSamples(s->size()), _samplesPerVector(1)
                , _unitaryLength(1.0), _relative(false), _average(0.0), _angleScale(1.0)
	{
		if (buf->size() % 2 != 0)
			throw SFA::util::runtime_error("Number of samples has to be even",__FILE__,__func__);
		if (buf->size() < 4)
			throw SFA::util::runtime_error("Graph needs at least 4 samples", __FILE__, __func__);
	}
	template VectorGraph2<float>::VectorGraph2(std::vector<float>*);
	template VectorGraph2<double>::VectorGraph2(std::vector<double>*);
	template VectorGraph2<int16_t>::VectorGraph2(std::vector<int16_t>*);

	template<typename T> VectorGraph2<T>::VectorGraph2(std::vector<T>* s, size_t showSamples, size_t samplesPerVector, double unitaryLength, bool relative, double average, double angleScale)
		: VectorGraph2<T>(s)
	{
		_showSamples = showSamples;
		_samplesPerVector = samplesPerVector;
		_unitaryLength = unitaryLength;
		_relative = relative;
		_angleScale = angleScale;
		_average = average;
	}
	template VectorGraph2<float>::VectorGraph2(std::vector<float>*, size_t, size_t, double, bool relative, double, double);
	template VectorGraph2<double>::VectorGraph2(std::vector<double>*, size_t, size_t, double, bool relative, double, double);
	template VectorGraph2<int16_t>::VectorGraph2(std::vector<int16_t>*, size_t, size_t, double, bool relative, double, double);

	template<typename T> VectorGraph2<T>::~VectorGraph2() {}
	template VectorGraph2<float>::~VectorGraph2();
	template VectorGraph2<double>::~VectorGraph2();
	template VectorGraph2<int16_t>::~VectorGraph2();

	template<typename T> std::vector<sp::timecode<T>> VectorGraph2<T>::operator()()
	{
        T vectorLength = grapher::samples_To_VG_vectorLength(_showSamples, _unitaryLength);
		std::vector<T> differences = std::vector<T>(buf->size(), 0.0);
		std::adjacent_difference(std::begin(*buf), std::end(*buf), std::begin(differences));

		// (4/2)-1=1 or (6/2)-1=2 or (8/2)-1=3
		auto dvg = (grapher::__differences_To_VG<T>(_samplesPerVector, vectorLength, std::vector<size_t>(1, ((buf->size()/2)-1))));
		if (_relative) {
			angle::relative afunc = angle::relative(std::begin(differences) + 1, std::end(differences),_average,_angleScale);
			output = dvg(differences, afunc);//((vectorSize * 2) + add);
		}
		else {
			angle::independent afunc = angle::independent(std::begin(differences) + 1, std::end(differences),_average,_angleScale);
			output = dvg(differences, afunc);//((vectorSize * 2) + add);
		}			                                                            
		return std::move(output);
	}
	template std::vector<sp::timecode<float>> VectorGraph2<float>::operator()();
	template std::vector<sp::timecode<double>> VectorGraph2<double>::operator()();
	template std::vector<sp::timecode<int16_t>> VectorGraph2<int16_t>::operator()();
}