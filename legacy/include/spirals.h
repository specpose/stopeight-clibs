// Copyright (C) 2009-2015 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

//#ifndef SPIRALS_H
//#define SPIRALS_H

#include "listswitchable.h"
#include "areaanalyzer.h"
#include "analyzer.h"

template<typename T> class Spirals : public ListSwitchable<T>
{
public:
    //using ListSwitchable<T>::ListSwitchable;
Spirals<T>() : ListSwitchable<T>() {}
Spirals<T>(const Spirals<T>&) = default;
Spirals<T>(Spirals<T>&&) = default;
Spirals<T>& operator=(const Spirals<T>&) = default;
Spirals<T>& operator=(Spirals<T>&&) = default;
template<typename F> Spirals(const F& list) {
    auto copy = F(list);
    *this = static_cast<Spirals<T>&>(copy);
}
//Upcast Move Constructor
template<typename F> Spirals(F&& list) {
    auto copy = std::move(list);
    *this = static_cast<Spirals<T>>(copy);
}

    static QList<T> findSpiralCliffs(const ListSwitchable<T> output);

private:
    static QList<T> findAreas(const ListSwitchable<T> stroke, qreal limit);
    //auxiliary function for findAreas
    static qreal findLimit(const ListSwitchable<T> toBeProcessed);

};

//#endif // SPIRALS_H
