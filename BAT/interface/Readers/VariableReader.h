/*
 * VariableReader.h
 *
 *  Created on: Jun 24, 2010
 *      Author: lkreczko
 */

#ifndef READER_H_
#define READER_H_
#include <string>
#include <boost/shared_ptr.hpp>
#include "TChain.h"

namespace BAT {
template<typename variableType = unsigned int>
class VariableReader {
public:
	VariableReader() :
		variableName("") {

	}

	VariableReader(TChain* chain, std::string varName):variableInput(chain), variableName(varName){
		variableInput->SetBranchAddress(varName, &variable);
	}
	~VariableReader() {
		delete variable;
	}
	std::string getVariableName() {
		return variableName;
	}
	void setVariableName(std::string varName) {
		if (VariableReader::isValidVariableName(varName)) {
			variableName = varName;
		}
	}
	static bool isValidVariableName(std::string varName) {
		return varName != "";
	}
	variableType getVariable();
private:
	std::string variableName;
	variableType variable;
	boost::shared_ptr<TChain> variableInput;
};

}

#endif /* READER_H_ */
