// Copyright (C) 2009-2015 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#ifndef LISTCOPYABLE_H
#define LISTCOPYABLE_H

#include "dpoint.h"
#include "listbase.h"

template<typename T> class ListCopyable : public ListBase<T>
{
public:
    ListCopyable();

    template<typename F> ListCopyable<T>(F& list);

    ListBase<dpoint> chopCopy(int startPosition, int endPosition);

};

#endif // LISTCOPYABLE_H
