// Copyright (C) 2017 Fassio Blatter
// GNU Lesser General Public License, version 2.1

#ifndef PRELOADERIF_H
#define PRELOADERIF_H

#include <memory>
#include <vector>

namespace grapher {

	template<typename T>class PreloaderIF
	{
	public:
		PreloaderIF<T>(std::unique_ptr<std::vector<T>>& s);
		virtual ~PreloaderIF<T>() {};

		virtual std::vector<T> operator()(int samplesPerPixel) =0;
	};
}

#endif
