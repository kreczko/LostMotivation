#ifndef BristolNTupleTools_ElectronFilter_h
#define BristolNTupleTools_ElectronFilter_h
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"

class ElectronFilter: public edm::EDFilter {
public:
    explicit ElectronFilter(const edm::ParameterSet&);
    ~ElectronFilter();

private:
    virtual void beginJob();
    virtual bool filter(edm::Event&, const edm::EventSetup&);
    virtual void endJob();

    // ----------member data ---------------------------
    int minNelectrons;
    double electronMinPT, electronMaxAbsoluteEta;

    edm::InputTag electronInput;

    int TotalCount;
    int PassedCount;

    edm::Service<TFileService> histServ;
    TH1I* hCount;
};
#endif
