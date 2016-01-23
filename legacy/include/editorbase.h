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
#include "listiteration.h"
#include <QList>
#include "myreal.h"

template<typename T> struct ListStorage{
    // input is always the raw data either from file or pen/mouse stroke
    T input;
    // output is initially input but gets reduced to T-C-T... in automatic
    T output;
};

class EditorBase : public EditorInterface
{
public:
    EditorBase();
    virtual ~EditorBase();// =0;

    void resetLists();
    void addPoint(QPointF p);
    ListBase<dpoint>& getOutput();
    void flushOutput();

    void automatic();

    //only these two have to be provided by implementations
    //static QList<dpoint> processSegment(QList<dpoint> list);
    //void process(ListBase<dpoint> toBeProcessed);
    QList<dpoint> (*processSegment)(QList<dpoint> list);// =0;
    //static QList<dpoint> (*processSegment)(QList<dpoint> list);// =0;
    virtual void process(ListBase<dpoint> toBeProcessed) =0;

protected:

    static bool checkPrecision(const ListBase<dpoint>& list);
    //static bool checkPrecision(const ListBase<dpoint> list);
    void setOutput(ListBase<dpoint> list);

    const void mainIterator(const QList<dpoint>& constCliffs,QList<QList<dpoint> >& slicesRef);
    //const void mainIterator(const QList<dpoint> constCliffs,QList<QList<dpoint> >& slicesRef);



private:
    ListStorage<ListBase<dpoint> > data;

};

#endif // EditorBase_H
