// Copyright (C) 2009-2016 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#include "stopeight-clibs/grapher_impl.h"
#include "stopeight-clibs/algo.h"
#include "stopeight-clibs/error.hpp"

namespace speczilla {

	template<typename T> VectorGraph<T>::VectorGraph(std::vector<T>* s)
    : output(std::vector<sp::timecode<T>>{}), buf(s), _showSamples(s->size()), _samplesPerVector(1)
                , _unitaryLength(1.0), _relative(false), _average(0.0), _angleScale(1.0)
	{
		if (buf->size() % 2 != 0)
			throw SFA::util::runtime_error("Number of samples has to be even",__FILE__,__func__);
		if (buf->size() < 4)
			throw SFA::util::runtime_error("Graph needs at least 4 samples", __FILE__, __func__);
	}
	template VectorGraph<float>::VectorGraph(std::vector<float>*);
	template VectorGraph<double>::VectorGraph(std::vector<double>*);
	template VectorGraph<int16_t>::VectorGraph(std::vector<int16_t>*);

	template<typename T> VectorGraph<T>::VectorGraph(std::vector<T>* s, size_t showSamples, size_t samplesPerVector, double unitaryLength, bool relative, double average, double angleScale)
		: VectorGraph<T>(s)
	{
		_showSamples = showSamples;
		_samplesPerVector = samplesPerVector;
		_unitaryLength = unitaryLength;
		_relative = relative;
		_angleScale = angleScale;
		_average = average;
	}
	template VectorGraph<float>::VectorGraph(std::vector<float>*, size_t, size_t, double, bool relative, double, double);
	template VectorGraph<double>::VectorGraph(std::vector<double>*, size_t, size_t, double, bool relative, double, double);
	template VectorGraph<int16_t>::VectorGraph(std::vector<int16_t>*, size_t, size_t, double, bool relative, double, double);

	template<typename T> VectorGraph<T>::~VectorGraph() {}
	template VectorGraph<float>::~VectorGraph();
	template VectorGraph<double>::~VectorGraph();
	template VectorGraph<int16_t>::~VectorGraph();

	template<typename T> std::vector<sp::timecode<T>> VectorGraph<T>::operator()()
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
	template std::vector<sp::timecode<float>> VectorGraph<float>::operator()();
	template std::vector<sp::timecode<double>> VectorGraph<double>::operator()();
	template std::vector<sp::timecode<int16_t>> VectorGraph<int16_t>::operator()();
}