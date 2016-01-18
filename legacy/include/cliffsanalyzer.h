// Copyright (C) 2009-2015 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#ifndef CLIFFSANALYZER_H
#define CLIFFSANALYZER_H

#include "listbase.h"
#include "listrotator.h"

template<typename T> class CliffsAnalyzer : public ListRotator<T>
{
public:
    CliffsAnalyzer<T>();
    template<typename F> CliffsAnalyzer<T>(F& list);

    // This is the replacement for getFirstCliff
    ListBase<dpoint> getFirstLegalSegment();

private:
    // used by filters and analyzer
    int hasIllegalSegment();

};

#endif // CLIFFSANALYZER_H
