#ifndef CLIFFS_H
#define CLIFFS_H

#include "editorbase.h"
#include "listiteration.h"

// is the storage for spirals different from cliffs?
//template<typename T>
class EditorCliffs : public EditorBase
{
public:
    EditorCliffs();

private:
    void process(ListBase<dpoint> toBeProcessed);

    QList<dpoint> processSegment(ListBase<dpoint> cliff);
};

#endif // CLIFFS_H
