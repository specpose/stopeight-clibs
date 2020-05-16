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
CornerNormalizer<T>(): CornerCalculator<T>() {}
CornerNormalizer<T>(const CornerNormalizer<T>&) = default;
CornerNormalizer<T>(CornerNormalizer<T>&&) = default;
template<typename F> CornerNormalizer(const F& list) {
    auto copy = F(list);
    *this = static_cast<CornerNormalizer<T>&>(copy);
}
//Upcast Move Constructor
template<typename F> CornerNormalizer(F&& list) {
    auto copy = std::move(list);
    *this = static_cast<CornerNormalizer<T>>(copy);
}
    void requireMinimumLength(qreal length);
	void intRaster(qreal threshold);

    // utilities for line-detection
    T getPointInTheMiddle();

    void cornerFilters();
};

#endif // CORNERNORMALIZER_H
