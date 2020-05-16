// Copyright (C) 2009-2015 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#ifndef AREANORMALIZER_H
#define AREANORMALIZER_H

#include "areacalculator.h"
//#include "turnnormalizer.h"
#include "cornernormalizer.h"

template<typename T> class AreaNormalizer : public AreaCalculator<T>
{
public:
    //using AreaCalculator<T>::AreaCalculator;
AreaNormalizer<T>() : AreaCalculator<T>() {}
AreaNormalizer<T>(const AreaNormalizer<T>&) = default;
AreaNormalizer<T>(AreaNormalizer<T>&&) = default;
template<typename F> AreaNormalizer(const F & list) {
    auto copy = F(list);//BUG calls Upcast constructor from Upcast constructor
    *this = static_cast<AreaNormalizer<T>&>(copy);
}
//Upcast Move Constructor
template<typename F> AreaNormalizer(F && list) {
    auto copy = std::move(list);//BUG calls Upcast constructor from Upcast constructor
    *this = static_cast<AreaNormalizer<T>>(copy);
}

    // these methods are being used for cleaning up the segments before the corner detection
    void areaFilters();

    // crafting out spirals: 3point segment direction change
    void removeInlays();
};

#endif // AREANORMALIZER_H
