// Copyright (C) 2009-2015 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "listswitchable.h"


template<typename T> class Calculator : public ListSwitchable<T>
{
public:
    using ListSwitchable::ListSwitchable;


    // Note: this is simple reversal. it is not checking order. Should be static.
    void reverse();



};

#endif // CALCULATOR_H
