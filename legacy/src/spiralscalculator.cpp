// Copyright (C) 2009-2015 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#include "include/spiralscalculator.h"

template<> SpiralsCalculator<dpoint>::SpiralsCalculator() : ListRotator<dpoint>() {}

// Note: ALL datamembers of target class destroyed
template<>template<typename F> SpiralsCalculator<dpoint>::SpiralsCalculator(F& list){
    *this = static_cast<SpiralsCalculator<dpoint>& >(list);
}

// Segment-Radius-Area
template<> qreal SpiralsCalculator<dpoint>::area(qreal diameter, qreal base){
    qreal squareOfRadius = pow(diameter/2,2);
    //qreal criteria = (squareOfRadius*(base))/2;
    // accounting for integration error; dangerous when iterating limit
    qreal criteria = (squareOfRadius*(base-M_LOG10El))/2;

    if (criteria<0){throw "ListCalculator.h::area criteria below zero";}
    return criteria;
}
