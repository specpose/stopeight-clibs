#ifndef LISTBASE_H
#define LISTBASE_H

#include <QList>
#include "dpoint.h"

//this will go
#include <QFile>

template<typename T> class ListBase : public QList<T>
{
public:
    //ListBase() { id=0;};
    ListBase<T>();
    //~ListBase<T>();

    //this will go into external library, extending class ListAnalyzer
    ListBase<dpoint> loadSPFile(QString& fileName);
    //ListAnalyzer<T> loadSPFile(QString& fileName);

    //used for line db record id
    int id;
};

#endif // LISTBASE_H
