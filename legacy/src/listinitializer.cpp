// Copyright (C) 2009-2015 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#include "include/listinitializer.h"

//#define debug() QDebug::QDebug(QtDebugMsg)
#define debug() QNoDebug()

template<> ListInitializer<dpoint>::ListInitializer() : ListRotator<dpoint>(){
    //calcTail = QList<dpoint>();
}

#include "include/listinitializer.h"
template ListInitializer<dpoint>::ListInitializer(ListInitializer<dpoint>& list);

// Note: ALL datamembers of target class destroyed
template<>template<typename F> ListInitializer<dpoint>::ListInitializer(F& list){
    *this = static_cast<ListInitializer<dpoint>& >(list);
}

// Note: ALL datamembers of target class destroyed
template<>template<typename F> void ListInitializer<dpoint>::operator=(F& list){
    this->swap(list);
}

template <> void ListInitializer<dpoint>::removeAt(int i) {
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

/*template <> int ListInitializer<dpoint>::getListElementNumber(int pos){
    for (int i=0;i<this->size();i++){
        if (this->at(i).position==pos){
            return i;
        }
    }
    debug()<<this;
    return -1;
}*/

/*template <> void ListInitializer<dpoint>::removeAtPos(int pos){
    // this only works because we're deleting just one!
    // performance issue
    if (getListElementNumber(pos)!=-1){
        this->removeAt(getListElementNumber(pos));
    } else {
        throw "ListInitializer<dpoint>::removeAtPos request to remove illegal position";
    }
}*/

/*template <> void ListInitializer<dpoint>::removeTail(){
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

/*template <> void ListInitializer<dpoint>::appendTail(){
        QListIterator<dpoint> i(calcTail);
        while ( i.hasNext() ) {
            dpoint point1 = i.next();
            this->append(point1);
        }
}*/
