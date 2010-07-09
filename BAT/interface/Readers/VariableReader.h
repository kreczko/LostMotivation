/*
 * VariableReader.h
 *
 *  Created on: Jun 24, 2010
 *      Author: lkreczko
 */

#ifndef READER_H_
#define READER_H_
#include <boost/shared_ptr.hpp>
#include "TChain.h"
#include "TBranch.h"
#include "TString.h"
#include <exception>

typedef std::vector<float>* MultiFloatPointer;
namespace BAT {
struct VariableNotFoundException: public std::exception {
	TString msg;
	VariableNotFoundException(TString message) :
		msg(message) {
	}
	~VariableNotFoundException() throw () {
	}

	const char* what() const throw () {
		return msg;
	}
};

template<typename variableType = unsigned int>
class VariableReader {
public:
	VariableReader() :
		input(), variable(0), variableName("") {

	}

	VariableReader(TChain* chain, TString varName) :
		input(chain), variable(0), variableName(varName) {
		if	(doesVariableExist()){
			enableVariable();
			readVariableFromInput();
		}
		else throw VariableNotFoundException("Variable '" + varName + "' was not found.");


	}

	~VariableReader() {
//		delete variable;
		delete variableName;
	}

	variableType getVariable() {
		return variable;
	}
private:
	boost::shared_ptr<TChain> input;
	variableType variable;
	TString variableName;

	void readVariableFromInput() {
		input->SetBranchAddress(variableName, &variable);
	}

	bool doesVariableExist() {
		return input->GetBranch(variableName) != NULL;
	}

	bool isVariableEnabled(){
		return input->GetBranchStatus(variableName);
	}

	void enableVariable(){
		input->SetBranchStatus(variableName, true);
	}
};

}

#endif /* READER_H_ */
