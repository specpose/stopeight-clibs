// Copyright (C) 2009-2015 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#include "include/editorbase.h"

#define debug() QDebug(QtDebugMsg)//::QDebug(QtDebugMsg)
//#define debug() QNoDebug()

template<typename T> EditorBase<T>::EditorBase() : EditorInterface<T>(), data(ListStorage<T>())
{
    //Note: data has to be allocated in subclass!
    debug()<<"EditorBase<T>::EditorBase() constructor called and data initialized";
}

template EditorBase<ListBase<dpoint> >::EditorBase();

//EditorBase::~EditorBase(){
//    data.input.~ListBase();
//    data.output.~ListBase();
//}

template<typename T> T& EditorBase<T>::getOutput(){
    //ListBase<dpoint>& ref(data.output);
    //debug()<<"EditorBase<T>::getOutput sent "<<ref;
    //return ref;
    return data.output;
}

template ListBase<dpoint>& EditorBase<ListBase<dpoint> >::getOutput();

template<typename T> void EditorBase<T>::setOutput(T list){
    data.output=list;
}

template void EditorBase<ListBase<dpoint> >::setOutput(ListBase<dpoint> list);

template<> void EditorBase<ListBase<dpoint> >::resetLists(){
    data.input.clear();
    data.output.clear();
}

template<> void EditorBase<ListBase<dpoint> >::addPoint(QPointF p){
     if (p.x()>=0 && p.y()>=0){
         dpoint newpoint(p);
         newpoint.position = data.input.size();
         data.input.push_back(newpoint);
    }
}

template<> void EditorBase<ListBase<dpoint> >::flushOutput(){
    data.output.clear();
    //output->setQList(input);
    setOutput(data.input);
    //data.output.append(data.input);
}

template<> void EditorBase<ListBase<dpoint> >::automatic(){
    this->flushOutput();
    debug()<<"Computation started with data size "<<this->getOutput().size();
    this->process(this->getOutput());
}

template<> const void EditorBase<ListBase<dpoint> >::mainIterator(const QList<dpoint>& constCliffs,QList<QList<dpoint> >& slicesRef){
    ListCopyable<dpoint> out = ListCopyable<dpoint>(this->getOutput());
    int currentSegment = 0;
    //maemo works: check cliff size
    if (constCliffs.size()==0){
        currentSegment += 1;
        debug()<<"*******************************************************************************";
        debug()<<"Segment Number: " << currentSegment;
        debug()<<"*******************************************************************************";
        slicesRef << this->processSegment(out);
    } else {
        for (int i=0;i<constCliffs.size();i++){
            currentSegment += 1;
            debug()<<"*******************************************************************************";
            debug()<<"Segment Number: " << currentSegment;
            debug()<<"*******************************************************************************";
            if (i==0){
                slicesRef << processSegment(out.chopCopy(out.first().position,constCliffs[i].position-1));
                // the last one does not have an illegal point in the end:
                // but has to be omitted to be consistent with rest. see bug below
            } else if (i==constCliffs.size()-1) {
                //slicesRef << processSegment(out.chopCopy(constCliffs[i-1].position,constCliffs[i].position));
                slicesRef << processSegment(out.chopCopy(constCliffs[i-1].position,constCliffs[i].position-1));
            } else {
                slicesRef << processSegment(out.chopCopy(constCliffs[i-1].position,constCliffs[i].position-1));
            }
        }
        currentSegment += 1;
        debug()<<"*******************************************************************************";
        debug()<<"Segment Number: " << currentSegment;
        debug()<<"*******************************************************************************";
        // it might have to hop over last point of second last segment? - bug.
        // dangerous: +1
        //slicesRef << processSegment(out.chopCopy(constCliffs[constCliffs.size()-1].position+1,out.last().position));
        slicesRef << processSegment(out.chopCopy(constCliffs[constCliffs.size()-1].position,out.last().position));
    }
}


template<> bool EditorBase<ListBase<dpoint> >::checkPrecision(const ListBase<dpoint> &list){
    /*
      Check if the list contains float values and set precision to high
      */
    for (int i=0;i<list.size();i++){
        if (!MyReal(list.at(i).x()).isInt() ||
            !MyReal(list.at(i).y()).isInt())
        {
            debug() << "ShapeMatcher::eatLegalSegments detected highPrecision";
            return true;
        }
    }
    debug() << "ShapeMatcher::eatLegalSegments found low precision";
    return false;
}


//void EditorBase::process(ListAnalyzer<dpoint> toBeProcessed){
//    throw "ERROR: EditorBase::process called. this should be superclass-call";
//}
