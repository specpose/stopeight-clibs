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

    //this should be C++11 move F&& constructor
    //template<typename F> ListBase<T>(F& list);
    //template<typename F> void operator=(F& list);

    // method for access from python
    static ListBase<dpoint> open(const std::string fileName);
    // method for access from legacy editor
    static ListBase<dpoint> loadSPFile(const QString &fileName);

};

//template<typename From, typename To> static To convert(From list);


#endif // LISTBASE_H
