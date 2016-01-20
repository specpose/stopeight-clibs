// Copyright (C) 2009-2015 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "listinitializer.h"


template<typename T> class Calculator : public ListInitializer<T>
{
public:
    Calculator<T>();
    template<typename F> Calculator<T>(F& list);

    qreal lengthAt(int i);

private:
    qreal lengthOf(QPointF difference);


};

#endif // CALCULATOR_H
