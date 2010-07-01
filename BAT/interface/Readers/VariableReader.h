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
#include "TString.h"
#include <exception>

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
		input(0), variable(0), variableName("") {

	}

	VariableReader(TChain* chain, TString varName) :
		input(chain), variable(0), variableName(varName) {
		if	(variableExist())
			readVariableFromInput();
		else throw VariableNotFoundException("Variable '" + varName + "' was not found.");


	}

	~VariableReader() {
		delete variable;
		delete variableName;
		delete input;
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

	bool variableExist() {
		return input->GetBranch(variableName) != NULL;
	}
};

}

#endif /* READER_H_ */
