#ifndef STROKEITERATOR_H
#define STROKEITERATOR_H

#include "dpoint.h"
#include <QList>

template<typename T> class ListIteration : public QList<T>
{
public:

    template<typename F> ListIteration<T>(F& list);

    QList<dpoint> chopCopy(int startPosition, int endPosition);

};

#endif // STROKEITERATOR_H
