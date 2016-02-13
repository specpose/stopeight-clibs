// Copyright (C) 2009-2015 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

//#ifndef TURNS_H
//#define TURNS_H

#include "listswitchable.h"
#include "listcopyable.h"
#include "turnanalyzer.h"

template<typename T> class Turns : public ListSwitchable<T>
{
public:
    Turns<T>();
    template<typename F> Turns<T>(F& list);

    static QList<dpoint> findTurns(ListCopyable<dpoint> toBeProcessed);

};

//#endif // TURNS_H
