// Copyright (C) 2009-2015 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#include "calculator.h"

template <> void Calculator<dpoint>::reverse(){
    ListSwitchable<dpoint> reversed= ListSwitchable<dpoint>();
    for (int i=this->size()-1;i>=0;i--){
        reversed << this->at(i);
    }
    this->clear();
    this->append(reversed);
}
