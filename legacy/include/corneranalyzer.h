// Copyright (C) 2009-2015 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#ifndef CORNERANALYZER_H
#define CORNERANALYZER_H

#include "cornernormalizer.h"
#include "analyzer.h"
#include "cliffscalculator.h"

template<typename T> class CornerAnalyzer : public CornerNormalizer<T>
{
public:
    //using CornerNormalizer<T>::CornerNormalizer;
CornerAnalyzer<T>(): CornerNormalizer<T>() {}
CornerAnalyzer<T>(const CornerAnalyzer<T>&) = default;
CornerAnalyzer<T>(CornerAnalyzer<T>&&) = default;
CornerAnalyzer<T>& operator=(const CornerAnalyzer<T>&) = default;
CornerAnalyzer<T>& operator=(CornerAnalyzer<T>&&) = default;
template<typename F> CornerAnalyzer(const F& list) {
    auto copy = F(list);
    *this = static_cast<CornerAnalyzer<T>&>(copy);
}
//Upcast Move Constructor
template<typename F> CornerAnalyzer(F&& list) {
    auto copy = std::move(list);
    *this = static_cast<CornerAnalyzer<T>>(copy);
}
    // implementation of "clean" math; as opposed to old_code shrinkToDeltas
    ListSwitchable<T> getFirstCorner();
};

#endif // CORNERANALYZER_H
