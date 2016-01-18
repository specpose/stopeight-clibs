// Copyright (C) 2009-2015 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#include "include/areaanalyzer.h"

template<> AreaAnalyzer<dpoint>::AreaAnalyzer() : AreaCalculator<dpoint>() {}

// Note: ALL datamembers of target class destroyed
template<>template<typename F> AreaAnalyzer<dpoint>::AreaAnalyzer(F& list){
    *this = static_cast<AreaAnalyzer<dpoint>& >(list);
}

template <>void AreaAnalyzer<dpoint>::areaFilters(){
    this->smoothingJitter(0);
    this->requireMinimumLength(9);
    this->rotateSegmentToXAxis();
    //this->risingJitter(0);
    //debug()<<"Before removeInlays: "<<this->size();
    this->removeInlays();
    //debug()<<"After removeInlays: "<<this->size();
}

