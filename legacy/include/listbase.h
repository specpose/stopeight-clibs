// Copyright (C) 2009-2015 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#ifndef LISTBASE_H
#define LISTBASE_H

#include "legacy_global.h"

#include <QtCore/QDebug>
#define debug() QDebug(QtDebugMsg)
//#define debug() QNoDebug()

#include <QtCore/QString>
#include <QtCore/QFile>

#include "dpoint.h"

/* This is being used by both the qt-based editor AND python legacy-wrappers! */
template<typename T> class LEGACYSHARED_EXPORT ListBase : public QList<T>
{
public:
    //has to be templated because of QList
    ListBase<T>();
    //virtual ~ListBase()=0;
    //virtual ~ListBase();

    //this should be C++11 move F&& constructor
    //is there a copy created when using F& instead of F?
    template<typename F> ListBase<T>(F& list);

    // method for access from python
    static ListBase<dpoint> open(const char* fileName);
    // method for access from legacy editor
    static ListBase<dpoint> loadSPFile(const QString &fileName);

};

template class ListBase<dpoint>;
//template ListBase<dpoint>::ListBase(ListBase<dpoint>& list);
//template void ListBase<dpoint>::operator=(ListBase<dpoint>& list);
//template<typename From, typename To> static To convert(From list);


#endif // LISTBASE_H
