#include "include/editorbase.h"

EditorBase::EditorBase() : EditorInterface() {
    this->data.input = ListBase<dpoint>();
    this->data.output = ListBase<dpoint>();
}

EditorBase::~EditorBase(){
    this->data.input.~ListBase();
    this->data.output.~ListBase();
}

void EditorBase::resetLists(){
    this->data.input.clear();
    this->data.output.clear();
}

void EditorBase::addPoint(QPointF p){
     if (p.x()>=0 && p.y()>=0){
         dpoint newpoint(p);
         newpoint.position = this->data.input.size();
        this->data.input.push_back(newpoint);
    }
}

ListBase<dpoint> EditorBase::getOutput(){
    return this->data.output;
}

void EditorBase::flushOutput(){
    this->data.output.clear();
    //output.setQList(input);
    this->data.output.append(this->data.input);
}

//void EditorBase::automatic(){
//    throw "ERROR: EditorBase::automatic called. this should be superclass-call";
//}

bool EditorBase::checkPrecision(const ListBase<dpoint> list){
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
