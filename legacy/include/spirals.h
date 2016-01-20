#ifndef SPIRALS_H
#define SPIRALS_H

#include "analyzer.h"
#include "spiralsanalyzer.h"

template<typename T> class Spirals : public ListBase<T>
{
public:
    Spirals<T>();
    template<typename F> Spirals<T>(F& list);

    static QList<dpoint> findSpirals(ListBase<dpoint> output,bool& pleaseReverse);

private:
    static QList<dpoint> findAreas(ListBase<dpoint>& stroke, qreal limit);
    //auxiliary function for findAreas
    static qreal findLimit(ListBase<dpoint> toBeProcessed);

};

#endif // SPIRALS_H
