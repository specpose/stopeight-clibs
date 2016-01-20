// Copyright (C) 2009-2015 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#ifndef STROKEITERATOR_H
#define STROKEITERATOR_H

#include "dpoint.h"
#include "listbase.h"

template<typename T> class ListIteration : public ListBase<T>
{
public:
    ListIteration();

    template<typename F> ListIteration<T>(F& list);
    template<typename F> void operator=(F& list);

    ListBase<dpoint> chopCopy(int startPosition, int endPosition);

};

#endif // STROKEITERATOR_H
