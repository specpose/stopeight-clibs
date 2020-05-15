// Copyright (C) 2009-2015 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#ifndef CLIFFSNORMALIZER_H
#define CLIFFSNORMALIZER_H

#include "areacalculator.h"
//#include "turnnormalizer.h"
#include "cornernormalizer.h"

template<typename T> class CliffsNormalizer : public AreaCalculator<T>
{
public:
    //using AreaCalculator<T>::AreaCalculator;
CliffsNormalizer<T>(): AreaCalculator<dpoint>() {}
template<typename F> CliffsNormalizer(const F& list) {
    auto copy = F(list);
    *this = static_cast<CliffsNormalizer<dpoint>&>(copy);
}
//Upcast Move Constructor
template<typename F> CliffsNormalizer(F&& list) {
    *this = std::move(static_cast<CliffsNormalizer<dpoint>&&>(list));
}
    // these methods are being used for cleaning up the segments before the corner detection
    void cliffFilters();
};

#endif // CLIFFSNORMALIZER_H
