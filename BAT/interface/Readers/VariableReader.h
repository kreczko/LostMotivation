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

	VariableReader(boost::shared_ptr<TChain> chain, TString varName) :
		input(chain), variable(0), variableName(varName) {

	}

	~VariableReader() {
	}

	variableType getVariable() {
		return variable;
	}

	void initialise() {
		if (doesVariableExist()) {
			enableVariable();
			readVariableFromInput();
		} else
			throw VariableNotFoundException("Variable '" + variableName + "' was not found.");
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

	void enableVariable() {
		input->SetBranchStatus(variableName, true);
	}
};

template<>
class VariableReader<MultiFloatPointer>{
public:
	VariableReader() :
		input(), variable(0), variableName("") {

	}

	VariableReader(boost::shared_ptr<TChain> chain, TString varName) :
		input(chain), variable(0), variableName(varName) {

	}

	~VariableReader() {
		delete variable;
	}

	MultiFloatPointer getVariable() {
		return variable;
	}

	float getVariableAt(unsigned int index){
		return variable->at(index);
	}

	void initialise() {
		if (doesVariableExist()) {
			enableVariable();
			readVariableFromInput();
		} else
			throw VariableNotFoundException("Variable '" + variableName + "' was not found.");
	}
private:
	boost::shared_ptr<TChain> input;
	MultiFloatPointer variable;
	TString variableName;

	void readVariableFromInput() {
		input->SetBranchAddress(variableName, &variable);
	}

	bool doesVariableExist() {
		return input->GetBranch(variableName) != NULL;
	}

	void enableVariable() {
		input->SetBranchStatus(variableName, true);
	}
};
}

#endif /* READER_H_ */
