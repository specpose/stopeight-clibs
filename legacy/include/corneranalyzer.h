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
CornerAnalyzer<T>(): CornerNormalizer<dpoint>() {}
template<typename F> CornerAnalyzer(const F& list) {
    auto copy = F(list);
    *this = static_cast<CornerAnalyzer<dpoint>&>(copy);
}
//Upcast Move Constructor
template<typename F> CornerAnalyzer(F&& list) {
    *this = std::move(static_cast<CornerAnalyzer<dpoint>&&>(list));
}
    // implementation of "clean" math; as opposed to old_code shrinkToDeltas
    ListSwitchable<dpoint> getFirstCorner();
};

#endif // CORNERANALYZER_H
