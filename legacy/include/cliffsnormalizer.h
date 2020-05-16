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
CliffsNormalizer<T>(): AreaCalculator<T>() {}
CliffsNormalizer<T>(const CliffsNormalizer<T>&) = default;
CliffsNormalizer<T>(CliffsNormalizer<T>&&) = default;
CliffsNormalizer<T>& operator=(const CliffsNormalizer<T>&) = default;
CliffsNormalizer<T>& operator=(CliffsNormalizer<T>&&) = default;
template<typename F> CliffsNormalizer(const F& list) {
    auto copy = F(list);
    *this = static_cast<CliffsNormalizer<T>&>(copy);
}
//Upcast Move Constructor
template<typename F> CliffsNormalizer(F&& list) {
    auto copy = std::move(list);
    *this = static_cast<CliffsNormalizer<T>>(copy);
}
    // these methods are being used for cleaning up the segments before the corner detection
    void cliffFilters();
};

#endif // CLIFFSNORMALIZER_H
