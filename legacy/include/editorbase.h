#ifndef EditorBase_H
#define EditorBase_H

// Will move into implementations when all are completed, or make interface configuration call?
#define MAX_POINTS 5
//#define LIMIT_TEST M_El
//#define LIMIT_TEST M_PIl
#define LIMIT_ITERATION_STEP 0.1

#include "editorinterface.h"
#include "listbase.h"
#include "myreal.h"

template<typename T> struct ListStorage{
    T input;
    T output;
};

class EditorBase : public virtual EditorInterface
{
public:
    EditorBase();
    virtual ~EditorBase();

    void resetLists();
    void addPoint(QPointF p);
    ListBase<dpoint> getOutput();
    void flushOutput();

    virtual void automatic() =0;

protected:
    bool checkPrecision(const ListBase<dpoint> list);
    ListStorage<ListBase<dpoint> > data;

};

#endif // EditorBase_H
