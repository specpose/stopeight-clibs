// Copyright (C) 2009-2015 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#ifndef EditorBase_H
#define EditorBase_H

// Will move into implementations when all are completed, or make interface configuration call?
#define MAX_POINTS 5
//#define LIMIT_TEST M_El
//#define LIMIT_TEST M_PIl
#define LIMIT_ITERATION_STEP 0.1

#include "editorinterface.h"
#include "listbase.h"
#include "listcopyable.h"
#include <QList>
#include "myreal.h"

template<typename T> struct ListStorage{
    //can not be used because compiler will require empty constructor in implementation instantiation
    ListStorage<T>() : input(T()), output(T()){}

    //specialisation:
    //ListStorage<ListBase<dpoint> >(){this.input=ListBase<dpoint>();this->output=ListBase<dpoint>(); }
    //ListStorage(ListBase<dpoint>* a,ListBase<dpoint>* b){input=a;output=b;}
    //ListStorage<ListBase<dpoint> > init(){input=ListBase<dpoint>();output=ListBase<dpoint>();return this;}

    // ptr has to be used because compiler will complain about uninitialized reference
    // input is always the raw data either from file or pen/mouse stroke
    T input;
    // output is initially input but gets reduced to T-C-T... in automatic
    T output;
};

//template ListStorage<ListBase<dpoint> >(ListBase<dpoint> a,ListBase<dpoint> b);

template<typename T> class EditorBase : public EditorInterface<T>
{
public:
    EditorBase<T>();
    //~EditorBase();

    void resetLists();
    void addPoint(QPointF p);
    //dont make getOutput const, see reversal in spiral process
    T& getOutput();
    void flushOutput();

    void automatic();



protected:

    static bool checkPrecision(const ListBase<dpoint>& list);
    //static bool checkPrecision(const ListBase<dpoint> list);
    void setOutput(T list);

    const void mainIterator(const QList<dpoint>& constCliffs,QList<QList<dpoint> >& slicesRef);
    //const void mainIterator(const QList<dpoint> constCliffs,QList<QList<dpoint> >& slicesRef);

private:
    //should ONLY be accessed for implementation instantiation
    ListStorage<T > data;


};

#endif // EditorBase_H
