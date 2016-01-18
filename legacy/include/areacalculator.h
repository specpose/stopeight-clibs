// Copyright (C) 2009-2015 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#ifndef AREACALCULATOR_H
#define AREACALCULATOR_H

#include "listrotator.h"

template<typename T> class AreaCalculator : public ListRotator<T>
{
public:
    AreaCalculator<T>();
    template<typename F> AreaCalculator<T>(F& list);

    // a.k.a integration up to triangle / curvature not included
    qreal sumOfDxAreasRotY();

private:
    // Segment-Radius-Area
    static qreal area(qreal diameter, qreal base);
};

#endif // AREACALCULATOR_H
