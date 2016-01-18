// Copyright (C) 2009-2015 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#ifndef AREAANALYZER_H
#define AREAANALYZER_H

#include "areacalculator.h"

template<typename T> class AreaAnalyzer : public AreaCalculator<T>
{
public:
    AreaAnalyzer<T>();
    template<typename F> AreaAnalyzer<T>(F& list);

protected:
    // these methods are being used for cleaning up the segments before the corner detection
    void areaFilters();

};

#endif // AREAANALYZER_H
