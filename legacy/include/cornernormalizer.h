// Copyright (C) 2009-2015 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#ifndef CORNERNORMALIZER_H
#define CORNERNORMALIZER_H

#include "cornercalculator.h"
#include "calculator.h"

template<typename T> class CornerNormalizer : public CornerCalculator<T>
{
public:
    //using CornerCalculator<T>::CornerCalculator;
CornerNormalizer<T>(): CornerCalculator<dpoint>() {}
template<typename F> CornerNormalizer(const F& list) {
    auto copy = F(list);
    *this = static_cast<CornerNormalizer<dpoint>&>(copy);
}
//Upcast Move Constructor
template<typename F> CornerNormalizer(F&& list) {
    *this = std::move(static_cast<CornerNormalizer<dpoint>&&>(list));
}
    void requireMinimumLength(qreal length);
	void intRaster(qreal threshold);

    // utilities for line-detection
    dpoint getPointInTheMiddle();

    void cornerFilters();
};

#endif // CORNERNORMALIZER_H
