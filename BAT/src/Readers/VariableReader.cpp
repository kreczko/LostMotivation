/*
 * VariableReader.cpp
 *
 *  Created on: Jun 24, 2010
 *      Author: lkreczko
 */

#include "../../interface/Readers/VariableReader.h"

namespace BAT {

template<typename variableType>
VariableReader<variableType>::VariableReader() :
	variableName("") {
	// TODO Auto-generated constructor stub
}

template <typename variableType>
VariableReader<variableType>::VariableReader(std::string varName) :
	variableName(varName) {

}

template <typename variableType>
std::string VariableReader<variableType>::getVariableName() {
	return variableName;
}

template <typename variableType>
void VariableReader<variableType>::setVariableName(std::string varName) {
	if (VariableReader::isValidVariableName(varName)) {
		variableName = varName;
	}
}

template <typename variableType>
bool VariableReader<variableType>::isValidVariableName(std::string varName) {
	return varName != "";
}

template <typename variableType>
VariableReader<variableType>::~VariableReader() {
	// TODO Auto-generated destructor stub
}

}
