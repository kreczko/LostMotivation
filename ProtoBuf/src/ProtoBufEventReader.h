/*
 * ProtoBufEventReader.h
 *
 *  Created on: 19 Sep 2011
 *      Author: kreczko
 */

#ifndef PROTOBUFEVENTREADER_H_
#define PROTOBUFEVENTREADER_H_
#include <boost/shared_ptr.hpp>
#include <vector>

namespace BAT {
class ProtoBufEventReader;
typedef boost::shared_ptr<ProtoBufEventReader> ProtoBufEventReaderPointer;

class ProtoBufEventReader {
public:
	ProtoBufEventReader();
	virtual ~ProtoBufEventReader();
	std::vector<ProtoBufEventReaderPointer> split(unsigned int numberOfFragments);
	void addInputFile(std::string fileExpression);

private:
	std::vector<std::string> resolveInputFiles(std::string path);
};

} /* namespace BAT */
#endif /* PROTOBUFEVENTREADER_H_ */
