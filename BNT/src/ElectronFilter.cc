#include "BristolNTupelTools/interface/ElectronFilter.h"

ElectronFilter::ElectronFilter(const edm::ParameterSet& iConfig) :
electronInput(iConfig.getParameter<edm::InputTag> ("electronInput")),
    minNelectrons(iConfig.getParameter<int> ("minNelectrons")),
    electronMinPT(iConfig.getParameter<double> ("electronMinPT")),
    electronMaxAbsoluteEta(iConfig.getParameter<double> ("electronMaxAbsoluteEta")){

    TotalCount = 0;
    PassedCount = 0;
    TFileDirectory COUNT = histServ->mkdir("EventCount");
    hCount = COUNT.make<TH1I> ("EventCounter", "Event Counter", 2, -0.5, 1.5);
    hCount->GetXaxis()->SetBinLabel(1, "all events");
    hCount->GetXaxis()->SetBinLabel(2, "passed");
}

ElectronFilter::~ElectronFilter() {

    // do anything here that needs to be done at desctruction time
    // (e.g. close files, deallocate resources etc.)

}

bool
ElectronFilter::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  ++TotalCount;

  // get superclusters
  edm::Handle<reco::SuperClusterCollection> superClustersEB;
  iEvent.getByLabel(scLabelEB_, superClustersEB);

  edm::Handle<reco::SuperClusterCollection> superClustersEE;
  iEvent.getByLabel(scLabelEE_, superClustersEE);

  // get jets
  edm::Handle<edm::View<reco::Candidate> > jets;
  iEvent.getByLabel(jetLabel_, jets);

  // get leptons
  edm::Handle<edm::View<reco::Candidate> > electrons;
  iEvent.getByLabel(elecLabel_, electrons);

  edm::Handle<edm::View<reco::Candidate> > muons;
  iEvent.getByLabel(muLabel_, muons);

  // Step 0:  Count SuperClusters
  int nsc=0;

  for (reco::SuperClusterCollection::const_iterator it = superClustersEB->begin(); it != superClustersEB->end(); ++it)
    {
      if (debug_) cout << "EB SuperCluster:" << endl;
      if (debug_) cout << "ET: " << it->energy()/cosh(it->eta()) << " eta: " <<  it->eta() << " phi: " <<  it->phi() << endl;
      const reco::SuperCluster* sc_pnt = &(*it);
      HoECalculator calc_HoE; // requires HCAL RecHits that are only available in RECO files
      double hoe = calc_HoE(sc_pnt,iEvent,iSetup);
      if ((it->energy()/cosh(it->eta()))>scET_ && fabs(it->eta())<scEta_ && hoe<scHoE_)
        {
          ++nsc;
        }
    }
  for (reco::SuperClusterCollection::const_iterator it = superClustersEE->begin(); it != superClustersEE->end(); ++it)
    {
      if (debug_) cout << "EE SuperCluster:" << endl;
      if (debug_) cout << "ET: " << it->energy()/cosh(it->eta()) << " eta: " <<  it->eta() << " phi: " <<  it->phi() << endl;
      const reco::SuperCluster* sc_pnt = &(*it);
      HoECalculator calc_HoE; // requires HCAL RecHits that are only available in RECO files
      double hoe = calc_HoE(sc_pnt,iEvent,iSetup);
      if ((it->energy()/cosh(it->eta()))>scET_ && fabs(it->eta())<scEta_ && hoe<scHoE_)
        {
          ++nsc;
        }
    }

  if (debug_) cout <<"# SuperClusters = "<<nsc<<endl;
  // If not enough superclusters found (or too many found), return false
  if (scMin_>-1 && nsc<scMin_) return false;
  if (scMax_>-1 && nsc>scMax_) return false;

  // Step 1:  Count jets
  int njets=0;

  for (edm::View<reco::Candidate>::const_iterator it = jets->begin(); it != jets->end(); ++it)
    {
      if (debug_) cout << "Jet:" << endl;
      if (debug_) cout << "pT: " << it->pt() << " eta: " <<  it->eta() << " phi: " <<  it->phi() << endl;
      if (it->pt()>jetPT_ && fabs(it->eta())<jetEta_)
        {
          ++njets;
        }
    }


  if (debug_) cout <<"# Jets = "<<njets<<endl;
  // If not enough jets found (or too many found), return false
  if (jetsMin_>-1 && njets<jetsMin_) return false;
  if (jetsMax_>-1 && njets>jetsMax_) return false;

  // Step 2:  Count leptons
  int nmuons=0;
  int nelectrons=0;
  // count muons
  for (edm::View<reco::Candidate>::const_iterator it = muons->begin(); it != muons->end();++it)
    {
      if (debug_) cout << "Muon:" << endl;
      if (debug_) cout << "pT: " << it->pt() << " eta: " <<  it->eta() << " phi: " <<  it->phi() << endl;
      bool passID = true;

      if (useMuID_)
        {
          const pat::Muon *muon = dynamic_cast<const pat::Muon *>(&*it);
          if (!(muon->muonID(muID_))) passID = false;
        }

      if (it->pt()>muPT_ && fabs(it->eta())<muEta_ && passID)
        {
          ++nmuons;
        }
    }

  if (debug_) cout <<"# Muons = "<<nmuons<<endl;

  // count electrons
  for (edm::View<reco::Candidate>::const_iterator it = electrons->begin(); it != electrons->end();++it)
    {
      if (debug_) cout << "Electron:" << endl;
      if (debug_) cout << "pT: " << it->pt() << " eta: " <<  it->eta() << " phi: " <<  it->phi() << endl;
      bool passID = true;

      if (useElecID_)
        {
          const pat::Electron *electron = dynamic_cast<const pat::Electron *>(&*it);
          if (!(electron->electronID(elecID_)>0.)) passID = false;
        }

      if (it->pt()>elecPT_ && fabs(it->eta())<elecEta_ && passID)
        {
          ++nelectrons;
        }
    }

  if (debug_) cout <<"# Electrons = "<<nelectrons<<endl;

  // If we require both electron and muon condition to be met, check electron here
  if (counteitherleptontype_==false)
    {
      if (electronsMin_>-1 && nelectrons<electronsMin_) return false;
      if (electronsMax_>-1 && nelectrons>electronsMax_) return false;
    }

  // If we require both electron and muon condition to be met, check muon here
  if (counteitherleptontype_==false)
    {
      if (muonsMin_>-1 && nmuons<muonsMin_) return false;
      if (muonsMax_>-1 && nmuons>muonsMax_) return false;
    }

  // Otherwise, only fail cut if neither electron nor muon meet expectations
  if (counteitherleptontype_==true)
    {
      if ((muonsMin_>-1 && nmuons<muonsMin_) && (electronsMin_>-1 && nelectrons<electronsMin_)) return false;
      if ((muonsMax_>-1 && nmuons>muonsMax_) && (electronsMax_>-1 && nelectrons>electronsMax_)) return false;
    }

  ++PassedCount;
  if (debug_) cout <<"PASSED!"<<endl;
   return true;
}

// ------------ method called once each job just before starting event loop  ------------
void ElectronFilter::beginJob() {
}

// ------------ method called once each job just after ending the event loop  ------------
void ElectronFilter::endJob() {
    hCount->SetBinContent(1, TotalCount);
    hCount->SetBinContent(2, PassedCount);
    cout << "Total events = " << TotalCount << "  Events Passed = " << PassedCount << endl;
}

//define this as a plug-in
DEFINE_FWK_MODULE(ElectronFilter);
