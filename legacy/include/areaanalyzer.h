// Copyright (C) 2009-2015 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#ifndef AREAANALYZER_H
#define AREAANALYZER_H

#include "areanormalizer.h"
#include "cliffsanalyzer.h"

template<typename T> class AreaAnalyzer : public AreaNormalizer<T>
{
public:
    //using AreaNormalizer<T>::AreaNormalizer;
AreaAnalyzer<T>() : AreaNormalizer<T>() {}
AreaAnalyzer<T>(const AreaAnalyzer<T>&) = default;
AreaAnalyzer<T>(AreaAnalyzer<T>&&) = default;
AreaAnalyzer<T>& operator=(const AreaAnalyzer<T>&) = default;
AreaAnalyzer<T>& operator=(AreaAnalyzer<T>&&) = default;
template<typename F> AreaAnalyzer(const F & list) {
    auto copy = F(list);//BUG calls Upcast constructor from Upcast constructor
    *this = static_cast<AreaAnalyzer<T>&>(copy);
}
//Upcast Move Constructor
template<typename F> AreaAnalyzer(F && list) {
    auto copy = std::move(list);//BUG calls Upcast constructor from Upcast constructor
    *this = static_cast<AreaAnalyzer<T>>(copy);
}

    ListSwitchable<dpoint> getFirstArea(qreal limit);

    // new Area function
    ListSwitchable<dpoint> getArea(qreal limit,QPointF START,qreal preceding=0);
protected:

    // Segment-Radius-Area; should be non-static with diameter=lengthStartToEnd from instance
    static qreal area(qreal diameter, qreal base);


};

#endif // AREAANALYZER_H
