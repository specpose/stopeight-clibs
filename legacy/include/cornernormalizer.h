// Copyright (C) 2009-2015 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#ifndef CORNERNORMALIZER_H
#define CORNERNORMALIZER_H

#include "cornercalculator.h"
#include "calculator.h"

template<typename T> class CornerNormalizer : public CornerCalculator<T>
{
public:
    using CornerCalculator::CornerCalculator;

    void requireMinimumLength(qreal length);
	void intRaster(qreal threshold);

    // utilities for line-detection
    dpoint getPointInTheMiddle();

    void cornerFilters();
};

#endif // CORNERNORMALIZER_H
