// Copyright (C) 2009-2015 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#include "include/listswitchable.h"

//#define debug() QDebug::QDebug(QtDebugMsg)
#define debug() QNoDebug()

template<> ListSwitchable<dpoint>::ListSwitchable() : ListRotator<dpoint>(){
    //calcTail = QList<dpoint>();
}

#include "include/listswitchable.h"
template ListSwitchable<dpoint>::ListSwitchable(ListSwitchable<dpoint>& list);

// Note: ALL datamembers of target class destroyed
template<>template<typename F> ListSwitchable<dpoint>::ListSwitchable(F& list){
    *this = static_cast<ListSwitchable<dpoint>& >(list);
}

// Note: ALL datamembers of target class destroyed
template<>template<typename F> void ListSwitchable<dpoint>::operator=(F& list){
    this->swap(list);
}

template <> void ListSwitchable<dpoint>::removeAt(int i) {
    if (i<0) {
        debug()<<"Illegal position for point removal: "<<i;
        return;
    }
    if (i>this->size()-1) {
        debug()<<"Illegal position for point removal: "<<i;
        return;
    }
    if ( (i==0 )|| (i==this->size()-1) ){
        debug() << "WARNING: deleting first or last point in subsegment, pos: "<< this->at(i).position;
    }
    QList<dpoint>::removeAt(i);
    // watch out, this happens AFTER remove
    if ( (i==0 )|| (i==this->size()) ){
        //this has to change to steepest possible
        rotateSegmentToXAxis();
        //this->append(calcTail);
        //this->rotateLastVectorToYAxis();
        //for (int i=0;i<calcTail.size();i++){
        //    this->removeLast();
        //}
    }
}

/*template <> int ListSwitchable<dpoint>::getListElementNumber(int pos){
    for (int i=0;i<this->size();i++){
        if (this->at(i).position==pos){
            return i;
        }
    }
    debug()<<this;
    return -1;
}*/

/*template <> void ListSwitchable<dpoint>::removeAtPos(int pos){
    // this only works because we're deleting just one!
    // performance issue
    if (getListElementNumber(pos)!=-1){
        this->removeAt(getListElementNumber(pos));
    } else {
        throw "ListSwitchable<dpoint>::removeAtPos request to remove illegal position";
    }
}*/

/*template <> void ListSwitchable<dpoint>::removeTail(){
    QListIterator<dpoint> i(calcTail);
    while (i.hasNext()){
        dpoint point1 = i.next();
        QListIterator<dpoint> p(*this);
        if ( p.findNext(point1) ) {
            if (p.hasPrevious()){
                dpoint point1 = p.previous();
                removeAtPos(point1.position);
            }
        }
    }
}*/

/*template <> void ListSwitchable<dpoint>::appendTail(){
        QListIterator<dpoint> i(calcTail);
        while ( i.hasNext() ) {
            dpoint point1 = i.next();
            this->append(point1);
        }
}*/
