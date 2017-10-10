// Copyright (C) 2017 Fassio Blatter
// GNU Lesser General Public License, version 2.1
#include <pybind11/pybind11.h>
#include <stopeight-clibs/algo.h>

PYBIND11_PLUGIN(grapher) {
  pybind11::module m("grapher", "Converting time-based series to Vector Graph");
  return m.ptr();
}
