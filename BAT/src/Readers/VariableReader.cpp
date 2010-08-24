/*
 * VariableReader.cpp
 *
 *  Created on: 24 Aug 2010
 *      Author: kreczko
 */

#include "../../interface/Readers/VariableReader.h"

namespace BAT {

template<>
VariableReader<MultiFloatPointer>::~VariableReader(){
    delete variable;
}

template<>
unsigned int VariableReader<MultiFloatPointer>::size() const{
    return variable->size();
}

template<>
unsigned int VariableReader<MultiDoublePointer>::size() const{
    return variable->size();
}

template<>
double VariableReader<MultiFloatPointer>::getVariableAt(unsigned int index) const{
    return variable->at(index);
}

template<>
double VariableReader<MultiDoublePointer>::getVariableAt(unsigned int index) const{
    return variable->at(index);
}
}
