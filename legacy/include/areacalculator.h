// Copyright (C) 2009-2015 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#ifndef AREACALCULATOR_H
#define AREACALCULATOR_H

#include "listswitchable.h"
#include "calculator.h"

template<typename T> class AreaCalculator : public ListSwitchable<T>
{
public:
    //using ListSwitchable<T>::ListSwitchable;
AreaCalculator<T>(): ListSwitchable<T>() {}
AreaCalculator<T>(const AreaCalculator<T>&) = default;
AreaCalculator<T>(AreaCalculator<T>&&) = default;
template<typename F> AreaCalculator(const F& list) {
    auto copy = F(list);//BUG calls Upcast constructor from Upcast constructor
    *this = static_cast<AreaCalculator<T>&>(copy);
}
//Upcast Move Constructor
template<typename F> AreaCalculator(F&& list) {
    auto copy = std::move(list);//BUG calls Upcast constructor from Upcast constructor
    *this = static_cast<AreaCalculator<T>>(copy);
}
    // a.k.a integration up to triangle / curvature not included
    qreal sumOfDxAreasRotY();

    // should be static OR member of List
    qreal triangleArea(QPointF A, QPointF B, QPointF C);
    // "pure" diameter
    qreal lengthFromStartToEnd();


};

#endif // AREACALCULATOR_H
