/*
 * VariableReader.h
 *
 *  Created on: Jun 24, 2010
 *      Author: lkreczko
 */

#ifndef READER_H_
#define READER_H_
#include <string>

namespace BAT {
template <typename T = unsigned int>
class VariableReader {
public:
	typedef T variableType;
	VariableReader<variableType>();
	VariableReader<variableType>(std::string varName);
	virtual ~VariableReader<variableType>();
	std::string getVariableName();
	void setVariableName(std::string varName);
	bool isValidVariableName(std::string varName);
	variableType getVariable();
private:
	std::string variableName;
	variableType variable;

};

}

#endif /* READER_H_ */
