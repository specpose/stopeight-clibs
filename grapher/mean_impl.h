// Copyright (C) 2017 Fassio Blatter
// GNU Lesser General Public License, version 2.1

#pragma once

#include <vector>

#include "shared_types.h"

#include "preloaderif.h"

namespace speczilla {

	template<typename T>class Mean : public PreloaderIF<T, double>
	{
	public:
		Mean<T>(std::vector<T>* s);

		~Mean<T>();

		double operator()();


	private:
		std::vector<T>* buf;
	};
}
