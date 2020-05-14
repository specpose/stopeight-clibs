// Copyright (C) 2009-2015 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#ifndef TURNANALYZER_H
#define TURNANALYZER_H

//#include "turnnormalizer.h"
//#include "corneranalyzer.h"
#include "straightsanalyzer.h"

template<typename T> class TurnAnalyzer : public TurnNormalizer<T>
{
public:
    using TurnNormalizer::TurnNormalizer;

    //ListCopyable<dpoint> getFirstTurnByTriplets();
    // This is replacement for old_code scalar/crest approach
    ListCopyable<dpoint> getFirstTriplet();
};

#endif // TURNANALYZER_H
