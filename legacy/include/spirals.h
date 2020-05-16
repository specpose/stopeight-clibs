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
Spirals<T>() : ListSwitchable<dpoint>() {}
template<typename F> Spirals(const F& list) {
    auto copy = F(list);
    *this = static_cast<Spirals<dpoint>&>(copy);
}
//Upcast Move Constructor
template<typename F> Spirals(F&& list) {
    auto copy = std::move(list);
    *this = static_cast<Spirals<dpoint>>(copy);
}

    static QList<dpoint> findSpiralCliffs(const ListSwitchable<dpoint> output);

private:
    static QList<dpoint> findAreas(const ListSwitchable<dpoint> stroke, qreal limit);
    //auxiliary function for findAreas
    static qreal findLimit(const ListSwitchable<dpoint> toBeProcessed);

};

//#endif // SPIRALS_H
