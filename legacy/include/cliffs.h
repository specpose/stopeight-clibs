// Copyright (C) 2009-2015 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

//#ifndef CLIFFS_H
//#define CLIFFS_H

#include "listswitchable.h"
#include "analyzer.h"
#include "cliffsanalyzer.h"

template<typename T> class Cliffs : public ListSwitchable<T>
{
public:
    using ListSwitchable<T>::ListSwitchable;

    static ListSwitchable<dpoint> findCliffs(ListSwitchable<dpoint> output);

};

//#endif // CLIFFS_H
