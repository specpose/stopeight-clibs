// Copyright (C) 2009-2015 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#ifndef SPIRALSCALCULATOR_H
#define SPIRALSCALCULATOR_H

#include "listrotator.h"

template<typename T> class SpiralsCalculator : public ListRotator<T>
{
public:
    SpiralsCalculator<T>();
    template<typename F> SpiralsCalculator<T>(F& list);

private:
    // Segment-Radius-Area
    static qreal area(qreal diameter, qreal base);
};

#endif // SPIRALSCALCULATOR_H
