// Copyright (C) 2009-2015 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#ifndef ANALYZER_H
#define ANALYZER_H

#include "calculator.h"
#include "listinitializer.h"

template<typename T> class Analyzer : public Calculator<T>
{
public:
    Analyzer<T>();
    template<typename F> Analyzer<T>(F& list);
    template<typename F> void operator=(F& list);

    // careful: this is changing order
    // does not change index-numbering variable
    void reverseOrder();

};

#endif // ANALYZER_H
