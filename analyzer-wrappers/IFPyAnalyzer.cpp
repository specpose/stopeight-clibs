// Copyright (C) 2019 Fassio Blatter
// GNU Lesser General Public License, version 2.1
#include <stopeight-clibs/analyzer.h>
#include <stopeight-clibs/Matrix.h>
#include <stopeight-clibs/shared_types.h>

#include <pybind11/pybind11.h>

#undef NDEBUG

using namespace pybind11;

PYBIND11_MODULE(analyzer, m){
	object matrix_module = module::import("stopeight.matrix");
	m.def("legal_segments", [](Vectors<std::vector<sp::timecode<double>>>& vectors)->Vectors<std::vector<sp::timecode<double>>>&{
		return vectors;
    },arg("vectors"));

}