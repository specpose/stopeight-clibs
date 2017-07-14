// Copyright (C) 2017 Fassio Blatter
// GNU Lesser General Public License, version 2.1

#pragma once

#include <vector>

#include "shared_types.h"

#include "preloaderif.h"

namespace speczilla {

	template<typename T>class Buffer : public PreloaderIF<T, sp::result<T>>
	{
	public:
		Buffer<T>(std::vector<T>* s);
		explicit Buffer<T>(std::vector<T>* s, int showSamples, int samplesPerVector=1, double unitaryLength = 1, bool relative = false, double average = 0.0f, double angleScale = 1.0f);

		~Buffer<T>();

		sp::result<T> operator()();

	private:
		std::vector<T>* buf;
		int _samplesPerVector,_showSamples;
		double _unitaryLength;
		bool _relative;
		double _average;
		double _angleScale;
	};
}
