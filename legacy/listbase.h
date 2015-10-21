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

    ListBase<dpoint> loadSPFile(QString& fileName);

};

#endif // LISTBASE_H
