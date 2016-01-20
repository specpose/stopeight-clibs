// Copyright (C) 2009-2015 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#include "include/spiralsanalyzer.h"

template<> SpiralsAnalyzer<dpoint>::SpiralsAnalyzer() : SpiralsCalculator<dpoint>() {}

// Note: ALL datamembers of target class destroyed
template<>template<typename F> SpiralsAnalyzer<dpoint>::SpiralsAnalyzer(F& list){
    *this = static_cast<SpiralsAnalyzer<dpoint>& >(list);
}

// Note: ALL datamembers of target class destroyed
template<>template<typename F> void SpiralsAnalyzer<dpoint>::operator=(F& list){
    this->swap(list);
}



