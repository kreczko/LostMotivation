/*
 * VariableReader.cpp
 *
 *  Created on: Jun 24, 2010
 *      Author: lkreczko
 */

#include "../../interface/Readers/VariableReader.h"

namespace BAT {
template <typename variableType>
variableType VariableReader<variableType>::getVariable(){
	return variable;
}
}
