// Copyright (C) 2009-2015 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#ifndef LISTBASE_H
#define LISTBASE_H

#include "legacy_global.h"

#include <QtCore/QString>
#include <QtCore/QFile>

#include "dpoint.h"

/* This is being used by both the qt-based editor AND python legacy-wrappers! */
template<typename T> class ListBase : public QList<T>
{
public:
    //has to be templated because of QList
    ListBase<T>();
    //virtual ~ListBase()=0;

    //this should be C++11 move F&& constructor
    //is there a copy created when using F& instead of F?
    template<typename F> ListBase<T>(F& list);

    // method for access from python
    static ListBase<dpoint> open(const char* fileName);
    // method for access from legacy editor
    static ListBase<dpoint> loadSPFile(const QString &fileName);

};

//GCC bug?
//extern template class ListBase<dpoint>;
template class ListBase<dpoint>;

//Windows
//template class LEGACYSHARED_EXPORT ListBase<dpoint>;

#endif // LISTBASE_H
