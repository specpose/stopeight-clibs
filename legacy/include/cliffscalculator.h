// Copyright (C) 2009-2015 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#ifndef CLIFFSCALCULATOR_H
#define CLIFFSCALCULATOR_H

#include "listswitchable.h"

template<typename T> class CliffsCalculator : public ListSwitchable<T>
{
public:
    //using ListSwitchable<T>::ListSwitchable;
CliffsCalculator<T>() : ListSwitchable<T>() {}
template<typename F> CliffsCalculator(const F& list) {
    auto copy = F(list);
    *this = static_cast<CornerAnalyzer<T>&>(copy);
}
//Upcast Move Constructor
template<typename F> CliffsCalculator(F&& list) {
    auto copy = std::move(list);
    *this = static_cast<CornerAnalyzer<T>>(copy);
}

    QPointF delta1At(int position);
    bool deriv1Crossed(int pos);
    qreal inclin1At(int i);
};

#endif // CLIFFSCALCULATOR_H
