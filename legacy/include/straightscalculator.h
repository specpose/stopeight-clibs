// Copyright (C) 2009-2015 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#ifndef STRAIGHTSCALCULATOR_H
#define STRAIGHTSCALCULATOR_H

#include "listinitializer.h"
#include "calculator.h"

template<typename T> class StraightsCalculator : public ListInitializer<T>
{
public:
    StraightsCalculator<T>();
    template<typename F> StraightsCalculator<T>(F& list);

    // length of curve between "all"! points / curvature not included
    // turncalculator.h
    // getPointInTheMiddle
    qreal sumLength();
};

#endif // STRAIGHTSCALCULATOR_H