// Copyright (C) 2009-2015 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#include "include/analyzer.h"

template<> Analyzer<dpoint>::Analyzer() : Calculator<dpoint>() {}

// Note: ALL datamembers of target class destroyed
template<>template<typename F> Analyzer<dpoint>::Analyzer(F& list){
    *this = static_cast<Analyzer<dpoint>& >(list);
}

// Note: ALL datamembers of target class destroyed
template<>template<typename F> void Analyzer<dpoint>::operator=(F& list){
    this->swap(list);
}

template <> void Analyzer<dpoint>::reverseOrder(){
    ListInitializer<dpoint> reversed= ListInitializer<dpoint>();
    int pointer = 0;
    for (int i=this->size()-1;i>=0;i--){
        dpoint point = this->at(i);
        point.position=pointer;
        reversed << this->at(i);
        pointer++;
    }
    this->clear();
    this->append(reversed);
}



