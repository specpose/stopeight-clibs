// Copyright (C) 2009-2015 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#ifndef CLIFFSANALYZER_H
#define CLIFFSANALYZER_H

#include "listbase.h"
#include "cliffscalculator.h"
#include "listcopyable.h"

template<typename T> class CliffsAnalyzer : public CliffsCalculator<T>
{
public:
    CliffsAnalyzer<T>();
    template<typename F> CliffsAnalyzer<T>(F& list);

    // This is the replacement for getFirstCliff
    ListCopyable<dpoint> getFirstLegalSegment();

private:
    // used by filters and analyzer
    int hasIllegalSegment();

};

#endif // CLIFFSANALYZER_H
