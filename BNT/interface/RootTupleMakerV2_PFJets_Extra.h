#ifndef RootTupleMakerV2PFJetsExtra
#define RootTupleMakerV2PFJetsExtra

#include "FWCore/Framework/interface/EDProducer.h"

class RootTupleMakerV2_PFJets_Extra : public edm::EDProducer {
 public:
  explicit RootTupleMakerV2_PFJets_Extra(const edm::ParameterSet&);

 private:
  void produce( edm::Event &, const edm::EventSetup & );
  const edm::InputTag   inputTag;
  const std::string     prefix,suffix;
  const unsigned int    maxSize;
//  const std::string     jecUncPath;
//  const bool            applyResJEC;
//  const std::string     resJEC;
};

#endif
