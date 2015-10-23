#ifndef LISTBASE_H
#define LISTBASE_H

#include "legacy_global.h"

#include <QList>
#include "dpoint.h"
#include <QFile>

template<typename T> class LEGACYSHARED_EXPORT ListBase : public QList<T>
{
public:
    ListBase<T>();

    // method for access from cython
    ListBase<dpoint> open(std::string fileName);
    // method for access from legacy editor
    ListBase<dpoint> loadSPFile(QString fileName);

};

#endif // LISTBASE_H
