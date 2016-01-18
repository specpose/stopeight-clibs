// Copyright (C) 2009-2015 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#ifndef SPIRALSANALYZER_H
#define SPIRALSANALYZER_H

#include "listiteration.h"

#include "cliffsanalyzer.h"
#include "areaanalyzer.h"

template<typename T> class SpiralsAnalyzer : public AreaAnalyzer<T>
{
public:
    SpiralsAnalyzer<T>();
    template<typename F> SpiralsAnalyzer<T>(F& list);
    template<typename F> void operator=(F& list);

    /*** META-FUNCTION ***/
    ListBase<dpoint> getFirstArea(qreal limit);

private:
    // new Area function
    ListBase<dpoint> getArea(qreal limit,QPointF START,qreal preceding=0);

};

#endif // SPIRALSANALYZER_H
