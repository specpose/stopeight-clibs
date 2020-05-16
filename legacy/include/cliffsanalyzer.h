// Copyright (C) 2009-2015 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#ifndef CLIFFSANALYZER_H
#define CLIFFSANALYZER_H

#include "listbase.h"
#include "cliffsnormalizer.h"

template<typename T> class CliffsAnalyzer : public CliffsNormalizer<T>
{
public:
    using CliffsNormalizer<T>::CliffsNormalizer;

    // This is the replacement for getFirstCliff
    ListSwitchable<T> getFirstLegalSegment();

    ListSwitchable<T> getFirstCliff(qreal limit=M_PIl);
    //ListCopyable<dpoint> getFirstCliffTCT(qreal limit=M_PIl);

};

#endif // CLIFFSANALYZER_H
