// Copyright (C) 2009-2015 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#ifndef LISTSWITCHABLE_H
#define LISTSWITCHABLE_H

#define HIGHPASS_LOW_LIMIT 0.0001

//#include <QList>
#include "listrotator.h"
//#include <limits>

template<typename T> class ListSwitchable : public ListRotator<dpoint>
{
public:
    // Overrides of QList
    ListSwitchable();
    template<typename F> ListSwitchable<T>(F& list);
    template<typename F> void operator=(F& list);

    void removeAt(int i);

    //void appendTail();
    //void removeTail();
    //int getListElementNumber(int position);

    // just for debugging, otherwise private
    //QList<dpoint> calcTail;

protected:
    //void addTail(QList<dpoint> tail){calcTail=QList<dpoint>();calcTail=tail;}

private:
    template<typename F> ListSwitchable<T>(const F& list);
    //void removeAtPos(int pos);

};





#endif // LISTSWITCHABLE_H
