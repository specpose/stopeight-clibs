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

    //templated function to return ListBase T from any ListBase implementation F specified here.
    //this should be C++11 move F&& constructor
    template<typename F> ListBase<T>(F& list);

    // method for access from python
    ListBase<dpoint> open(const std::string fileName);
    // method for access from legacy editor
    ListBase<dpoint> loadSPFile(const QString &fileName);

};

//template<typename From, typename To> static To convert(From list);

#endif // LISTBASE_H
