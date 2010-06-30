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
#include "TBranch.h"

namespace BAT {
template<typename variableType = unsigned int>
class VariableReader {
public:
	VariableReader() :
		input(0), variable(0), variableName("") {

	}

	VariableReader(TChain* chain, std::string varName) :
		input(chain), variable(0), variableName(varName) {
		readVariableFromInput();
	}

	~VariableReader() {
		delete variable;
		delete variableName;
		delete input;
	}
//	std::string getVariableName() {
//		return variableName;
//	}
//	void setVariableName(std::string varName) {
//		if (VariableReader::isValidVariableName(varName)) {
//			variableName = varName;
//		}
//	}
	static bool isValidVariableName(std::string varName) {
		return varName != "";
	}
	variableType getVariable() {
		return variable;
	}
private:
	boost::shared_ptr<TChain> input;
	variableType variable;
	std::string variableName;

	void readVariableFromInput() {
		input->SetBranchAddress(variableName.c_str(), &variable);
	}
};

}

#endif /* READER_H_ */
