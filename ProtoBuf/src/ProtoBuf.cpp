#include <iostream>
#include "EventCollection.pb.h"
#include <fstream>
#include <iostream>
#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include <sstream>
#include <boost/regex.hpp>
#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>
#include <boost/program_options/options_description.hpp>
#include "ProtoBufWrite.h"
#include "Variables.h"

using namespace std;
using namespace boost::iostreams;
namespace po = boost::program_options;

unsigned long numberOfEvents = 0;

void ListEvents(const HEP::EventCollection& eventCollection) {
	for (int index = 0; index < eventCollection.event_size(); ++index) {
		++numberOfEvents;
		const HEP::Event& event = eventCollection.event(index);
		if (numberOfEvents % 10000 == 0) {
			cout << "Processed events: " << numberOfEvents << endl;
			cout << event.run() << ":" << event.lumisection() << ":" << event.number() << endl;
		}

	}
}

const HEP::EventCollection getEventCollection(std::string filename) {
	fstream file(filename.c_str(), ios_base::in | ios_base::binary);
	filtering_streambuf<input> in;
	in.push(gzip_decompressor());
	in.push(file);

	stringstream ss(stringstream::in | stringstream::out);
	boost::iostreams::copy(in, ss); // can I avoid the copy?

	HEP::EventCollection eventCollection;

	if (!eventCollection.ParseFromIstream(&ss)) {
		throw "Failed to parse eventCollection.";
	}
	return eventCollection;
}

std::vector<std::string> getInputFiles(std::string path) {
	std::vector<std::string> all_matching_files;

	size_t found;
	found = path.find("*");
	if (found != string::npos) {
		//found string and take it as wildcard
		cout << "treating as a file" << endl;
		//get path
		found = path.rfind("/");
		string directory("");
		string filename("");

		if (found != string::npos) {
			directory = path.substr(0, found + 1);
			filename = path.substr(found + 1, string::npos - 1);
		}

		found = filename.find("*");
		if (found != string::npos)
			filename.replace(found, 1, ".*\\");
		cout << "dir: " << directory << endl;
		cout << "file: " << filename << endl;
		const boost::regex my_filter(filename);

		boost::filesystem::directory_iterator end_itr; // Default ctor yields past-the-end
		for (boost::filesystem::directory_iterator i(directory); i != end_itr; ++i) {
			// Skip if not a file
			if (!boost::filesystem::is_regular_file(i->status()))
				continue;

			boost::smatch what;

			// Skip if no match
			if (!boost::regex_match(i->leaf(), what, my_filter))
				continue;

			// File matches, store it
			all_matching_files.push_back(directory + i->leaf());
		}

	} else {
		cout << "treating as a file" << endl;
		cout << path << endl;
		all_matching_files.push_back(path);
	}

	return all_matching_files;
}

po::variables_map getInputVariables(int argc, char **argv) {
	// Declare the supported options.
	po::options_description desc("Allowed options");
	desc.add_options()("help,h", "produce help message")("maxNFiles", po::value<unsigned long>(),
			"set maximal number of files to be processed")("nEventsPerFile,n", po::value<unsigned int>(),
			"number of events per file")("outputFolder,o", po::value<string>(), "output folder for ProtoBufFiles")(
			"inputFiles,i", po::value<string>(), "input folder for ProtoBufFiles")("write,w", po::value<bool>(),
			"Switch for writing ProtoBuf instead of reading");

	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, desc), vm);
	po::notify(vm);
	if (vm.count("help")) {
		cout << desc << "\n";
		exit(0);
		return 0;
	}

	return vm;
}

void readProtoBuf(string inputFiles, unsigned long maxNFiles) {
//	std::string test1(
//			"/storage/TopQuarkGroup/mc/TTJets_TuneZ2_7TeV-madgraph-tauola/ProtoBuf_v3_Summer11-PU_S4_START42_V11-v1/TTJet_100EventsPerFile_gzip5_0000000.event");
//	std::string test2(
//			"/storage/TopQuarkGroup/mc/TTJets_TuneZ2_7TeV-madgraph-tauola/ProtoBuf_v3_Summer11-PU_S4_START42_V11-v1/*.event");

	std::vector<std::string> all_matching_files = getInputFiles(inputFiles);
	cout << "nFiles found:" << all_matching_files.size() << endl;
	if (all_matching_files.size() > 0)
		cout << "first file: " << all_matching_files.front() << endl;
	for (unsigned int index = 0; index < all_matching_files.size() && index < maxNFiles; ++index) {
		HEP::EventCollection eventCollection = getEventCollection(all_matching_files.at(index));
		ListEvents(eventCollection);
	}
	cout << "Total number of processed events: " << numberOfEvents << endl;
}

void writeProtobuf(string outputFolder, unsigned short nEventsPerFile, unsigned long maxNFiles) {
	std::string test2(
			"/storage/TopQuarkGroup/mc/TTJets_TuneZ2_7TeV-madgraph-tauola/nTuple_v3_Summer11-PU_S4_START42_V11-v1/0b63e6090f671316354e220e2be2a651/*.root");

	TChain* chain = new TChain("rootTupleTree/tree");
	chain->Add(test2.c_str());
	ProtoBufWriter writer(chain);
	writer.store(outputFolder, "TestingCpp", nEventsPerFile, 5, maxNFiles);
}
int main(int argc, char **argv) {

	GOOGLE_PROTOBUF_VERIFY_VERSION;
	po::variables_map inputVariables = getInputVariables(argc, argv);
	unsigned long maxNFiles(1);
	unsigned int nEventsPerFile(10);
	string outputFolder("/storage/protofiles2/");
	string inputFiles(
			"/storage/TopQuarkGroup/mc/TTJets_TuneZ2_7TeV-madgraph-tauola/ProtoBuf_v3_Summer11-PU_S4_START42_V11-v1/*.event");
	bool writeOn(false);

	if (inputVariables.count("maxNFiles")) {
		maxNFiles = inputVariables["maxNFiles"].as<unsigned long>();
	}

	if (inputVariables.count("nEventsPerFile")) {
		nEventsPerFile = inputVariables["nEventsPerFile"].as<unsigned int>();
	}

	if (inputVariables.count("outputFolder")) {
		outputFolder = inputVariables["outputFolder"].as<string>();
	}

	if (inputVariables.count("inputFiles")) {
		inputFiles = inputVariables["inputFiles"].as<string>();
	}

	if (inputVariables.count("write")) {
		writeOn = inputVariables["write"].as<bool>();
	}

	if (writeOn)
		writeProtobuf(outputFolder, nEventsPerFile, maxNFiles);
	else
		readProtoBuf(inputFiles, maxNFiles);
	// Optional:  Delete all global objects allocated by libprotobuf.
	google::protobuf::ShutdownProtobufLibrary();

	return 0;
}
