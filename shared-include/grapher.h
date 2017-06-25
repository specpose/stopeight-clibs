// Copyright (C) 2017 Fassio Blatter
// GNU Lesser General Public License, version 2.1

#ifndef GRAPHER_H
#define GRAPHER_H

#include <memory>
#include <vector>

// grapher.h is compiled by msvc, grapher_impl.h is compiled by llvm4
// Hide everything SYCL
// For hiding and dual implementation, NAME MUST BE THE SAME
// AND NO IMPLEMENTATIONS IN HERE

#include "preloaderif.h"

namespace grapher {

	template<typename T>class Buffer : public PreloaderIF<T, sp::result>
	{
	public:
		Buffer<T>(std::vector<T>* s);
		Buffer<T>(std::vector<T>* s, int showSamples, int samplesPerVector=1, double unitaryLength = 1, bool relative=false, double average = 1.0f, double angleScale=1.0f);
		~Buffer<T>();

		sp::result operator()();

	private:
		//needs to be there to avoid crt error
		//hack: length of pointer on amd_win10_64
		//doesnt work; crash when remove in debug from presonus
		char buf[6];//sizeofPTR
		char _samplesPerVectorp[sizeof(int)], _showSamples[sizeof(int)];
		char _unitaryLength[sizeof(double)];
		bool _relative;
		char _average[sizeof(double)];
		char _angleScale[sizeof(double)];
		//char _center[sizeof(std::pair<std::pair<double, double>, std::pair<double, double>>)];
	};
}
#endif
