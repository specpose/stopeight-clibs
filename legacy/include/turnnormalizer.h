// Copyright (C) 2009-2015 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#ifndef TURNNORMALIZER_H
#define TURNNORMALIZER_H

#include "turncalculator.h"
#include "listinitializer.h"

template<typename T> class TurnNormalizer : public TurnCalculator<T>
{
public:
    TurnNormalizer<T>();
    template<typename F> TurnNormalizer<T>(F& list);
    template<typename F> void operator=(F& list);


    //ACL: foreign
    void smoothingJitter(int pos);


};

#endif // TURNNORMALIZER_H
