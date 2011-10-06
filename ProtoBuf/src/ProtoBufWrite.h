#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include <boost/iostreams/device/file.hpp>
#include <boost/iostreams/copy.hpp>
#include "EventCollection.pb.h"
#include "TChain.h"
#include "TROOT.h"
#include <iostream>
#include <fstream>
#include "Variables.h"
#include <boost/format.hpp>
#include <boost/shared_ptr.hpp>

using namespace boost::iostreams;
using namespace boost;
using namespace std;

class ProtoBufWriter {
public:
	ProtoBufWriter(TChain* chain) :
			data(chain), vars(chain) {
		vars.Init(chain);

	}

	~ProtoBufWriter() {

	}

	void store(string outputFolder, string outputfile, unsigned int numberOfEventsPerFile,
			unsigned short compressionLevel, unsigned long maxFiles){
		cout << "Number of events found " << data->GetEntries() << endl;
		data->SetBranchStatus("*", 1);
		storeChain(outputFolder, outputfile, numberOfEventsPerFile, compressionLevel, maxFiles);
	}

private:
	shared_ptr<TChain> data;
	Variables vars;

	int writeEventCollection(shared_ptr<HEP::EventCollection> eCollection, std::string filename, unsigned int compressionLevel) {
		filtering_ostream out;
		out.push(gzip_compressor(compressionLevel));
		out.push(file_sink(filename, ios_base::out | ios_base::binary));

		if (!eCollection->SerializeToOstream(&out)) {
			cerr << "Failed to write event collection." << endl;
			return -1;
		}

		return 0;
	}

	void fillElectron(HEP::Electron* electron, string prefix, unsigned int index) {
		if (prefix == "selectedPatElectrons") {
			electron->set_type(HEP::Electron::Calo);

			electron->set_energy(vars.selectedPatElectrons_Energy->at(index));
			electron->set_px(vars.selectedPatElectrons_Px->at(index));
			electron->set_py(vars.selectedPatElectrons_Py->at(index));
			electron->set_pz(vars.selectedPatElectrons_Pz->at(index));

			electron->set_caloenergy(vars.selectedPatElectrons_CaloEnergy->at(index));

			electron->set_dcottheta(vars.selectedPatElectrons_DCotTheta->at(index));
			electron->set_deltaetatrksc(vars.selectedPatElectrons_DeltaEtaTrkSC->at(index));
			electron->set_deltaphitrksc(vars.selectedPatElectrons_DeltaPhiTrkSC->at(index));
			electron->set_dist(vars.selectedPatElectrons_Dist->at(index));
			electron->set_ecaliso(vars.selectedPatElectrons_EcalIso->at(index));
			electron->set_ecaliso03(vars.selectedPatElectrons_EcalIso03->at(index));
			electron->set_ecalisoheep(vars.selectedPatElectrons_EcalIsoHeep->at(index));
			electron->set_eoverp(vars.selectedPatElectrons_EoverP->at(index));
			electron->set_eta(vars.selectedPatElectrons_Eta->at(index));
			HEP::Electron_GSFTrack* gsf = electron->add_track();
			gsf->set_eta(vars.selectedPatElectrons_GSFTrack_Eta->at(index));
			gsf->set_phi(vars.selectedPatElectrons_GSFTrack_Phi->at(index));
			gsf->set_pt(vars.selectedPatElectrons_GSFTrack_Pt->at(index));
			gsf->set_theta(vars.selectedPatElectrons_GSFTrack_Theta->at(index));
			gsf->set_d0(vars.selectedPatElectrons_GSFTrack_d0->at(index));
			gsf->set_charge(vars.selectedPatElectrons_GSFTrack_Charge->at(index));

			electron->set_hcaliso(vars.selectedPatElectrons_HcalIso->at(index));
			electron->set_hcaliso03(vars.selectedPatElectrons_HcalIso03->at(index));
			electron->set_hcalisod1heep(vars.selectedPatElectrons_HcalIsoD1Heep->at(index));
			electron->set_hcalisod2heep(vars.selectedPatElectrons_HcalIsoD2Heep->at(index));
			electron->set_hoe(vars.selectedPatElectrons_HoE->at(index));
			electron->set_phi(vars.selectedPatElectrons_Phi->at(index));
			electron->set_pt(vars.selectedPatElectrons_Pt->at(index));
			electron->set_sceta(vars.selectedPatElectrons_SCEta->at(index));
			electron->set_scphi(vars.selectedPatElectrons_SCPhi->at(index));
			electron->set_scpt(vars.selectedPatElectrons_SCPt->at(index));
			electron->set_scrawenergy(vars.selectedPatElectrons_SCRawEnergy->at(index));
			electron->set_sigmaetaeta(vars.selectedPatElectrons_SigmaEtaEta->at(index));
			electron->set_sigmaietaieta(vars.selectedPatElectrons_SigmaIEtaIEta->at(index));
			electron->set_trkiso(vars.selectedPatElectrons_TrkIso->at(index));
			electron->set_trkiso03(vars.selectedPatElectrons_TrkIso03->at(index));
			electron->set_trkisoheep(vars.selectedPatElectrons_TrkIsoHeep->at(index));
			electron->set_vertexx(vars.selectedPatElectrons_Vertex_X->at(index));
			electron->set_vertexy(vars.selectedPatElectrons_Vertex_Y->at(index));
			electron->set_vertexz(vars.selectedPatElectrons_Vertex_Z->at(index));
			electron->set_vtxdistxy(vars.selectedPatElectrons_VtxDistXY->at(index));
			electron->set_vtxdistz(vars.selectedPatElectrons_VtxDistZ->at(index));
			electron->set_db(vars.selectedPatElectrons_dB->at(index));
			electron->set_eseedclusteroverpout(vars.selectedPatElectrons_eSeedClusterOverPout->at(index));
			electron->set_fbrem(vars.selectedPatElectrons_fbrem->at(index));
			electron->set_shfracinnerhits(vars.selectedPatElectrons_shFracInnerHits->at(index));

			//ints
			electron->set_charge(vars.selectedPatElectrons_Charge->at(index));
			electron->set_missinghits(vars.selectedPatElectrons_MissingHits->at(index));
			electron->set_passid(vars.selectedPatElectrons_PassID->at(index));
			electron->set_vtxindex(vars.selectedPatElectrons_VtxIndex->at(index));
			electron->set_closestctftrackref(vars.selectedPatElectrons_closestCtfTrackRef->at(index));
		}

		if (prefix == "selectedPatElectronsLoosePFlow") {
			electron->set_type(HEP::Electron::ParticleFlow);
			electron->set_energy(vars.selectedPatElectronsLoosePFlow_Energy->at(index));
			electron->set_px(vars.selectedPatElectronsLoosePFlow_Px->at(index));
			electron->set_py(vars.selectedPatElectronsLoosePFlow_Py->at(index));
			electron->set_pz(vars.selectedPatElectronsLoosePFlow_Pz->at(index));

			electron->set_caloenergy(vars.selectedPatElectronsLoosePFlow_CaloEnergy->at(index));

			electron->set_dcottheta(vars.selectedPatElectronsLoosePFlow_DCotTheta->at(index));
			electron->set_deltaetatrksc(vars.selectedPatElectronsLoosePFlow_DeltaEtaTrkSC->at(index));
			electron->set_deltaphitrksc(vars.selectedPatElectronsLoosePFlow_DeltaPhiTrkSC->at(index));
			electron->set_dist(vars.selectedPatElectronsLoosePFlow_Dist->at(index));
			electron->set_ecaliso(vars.selectedPatElectronsLoosePFlow_EcalIso->at(index));
			electron->set_ecaliso03(vars.selectedPatElectronsLoosePFlow_EcalIso03->at(index));
			electron->set_ecalisoheep(vars.selectedPatElectronsLoosePFlow_EcalIsoHeep->at(index));
			electron->set_eoverp(vars.selectedPatElectronsLoosePFlow_EoverP->at(index));
			electron->set_eta(vars.selectedPatElectronsLoosePFlow_Eta->at(index));
			HEP::Electron_GSFTrack* gsf = electron->add_track();
			gsf->set_eta(vars.selectedPatElectronsLoosePFlow_GSFTrack_Eta->at(index));
			gsf->set_phi(vars.selectedPatElectronsLoosePFlow_GSFTrack_Phi->at(index));
			gsf->set_pt(vars.selectedPatElectronsLoosePFlow_GSFTrack_Pt->at(index));
			gsf->set_theta(vars.selectedPatElectronsLoosePFlow_GSFTrack_Theta->at(index));
			gsf->set_d0(vars.selectedPatElectronsLoosePFlow_GSFTrack_d0->at(index));
			gsf->set_charge(vars.selectedPatElectronsLoosePFlow_GSFTrack_Charge->at(index));

			electron->set_hcaliso(vars.selectedPatElectronsLoosePFlow_HcalIso->at(index));
			electron->set_hcaliso03(vars.selectedPatElectronsLoosePFlow_HcalIso03->at(index));
			electron->set_hcalisod1heep(vars.selectedPatElectronsLoosePFlow_HcalIsoD1Heep->at(index));
			electron->set_hcalisod2heep(vars.selectedPatElectronsLoosePFlow_HcalIsoD2Heep->at(index));
			electron->set_hoe(vars.selectedPatElectronsLoosePFlow_HoE->at(index));
			electron->set_phi(vars.selectedPatElectronsLoosePFlow_Phi->at(index));
			electron->set_pt(vars.selectedPatElectronsLoosePFlow_Pt->at(index));
			electron->set_sceta(vars.selectedPatElectronsLoosePFlow_SCEta->at(index));
			electron->set_scphi(vars.selectedPatElectronsLoosePFlow_SCPhi->at(index));
			electron->set_scpt(vars.selectedPatElectronsLoosePFlow_SCPt->at(index));
			electron->set_scrawenergy(vars.selectedPatElectronsLoosePFlow_SCRawEnergy->at(index));
			electron->set_sigmaetaeta(vars.selectedPatElectronsLoosePFlow_SigmaEtaEta->at(index));
			electron->set_sigmaietaieta(vars.selectedPatElectronsLoosePFlow_SigmaIEtaIEta->at(index));
			electron->set_trkiso(vars.selectedPatElectronsLoosePFlow_TrkIso->at(index));
			electron->set_trkiso03(vars.selectedPatElectronsLoosePFlow_TrkIso03->at(index));
			electron->set_trkisoheep(vars.selectedPatElectronsLoosePFlow_TrkIsoHeep->at(index));
			electron->set_vertexx(vars.selectedPatElectronsLoosePFlow_Vertex_X->at(index));
			electron->set_vertexy(vars.selectedPatElectronsLoosePFlow_Vertex_Y->at(index));
			electron->set_vertexz(vars.selectedPatElectronsLoosePFlow_Vertex_Z->at(index));
			electron->set_vtxdistxy(vars.selectedPatElectronsLoosePFlow_VtxDistXY->at(index));
			electron->set_vtxdistz(vars.selectedPatElectronsLoosePFlow_VtxDistZ->at(index));
			electron->set_db(vars.selectedPatElectronsLoosePFlow_dB->at(index));
			electron->set_eseedclusteroverpout(vars.selectedPatElectronsLoosePFlow_eSeedClusterOverPout->at(index));
			electron->set_fbrem(vars.selectedPatElectronsLoosePFlow_fbrem->at(index));
			electron->set_shfracinnerhits(vars.selectedPatElectronsLoosePFlow_shFracInnerHits->at(index));

			//ints
			electron->set_charge(vars.selectedPatElectronsLoosePFlow_Charge->at(index));
			electron->set_missinghits(vars.selectedPatElectronsLoosePFlow_MissingHits->at(index));
			electron->set_passid(vars.selectedPatElectronsLoosePFlow_PassID->at(index));
			electron->set_vtxindex(vars.selectedPatElectronsLoosePFlow_VtxIndex->at(index));
			electron->set_closestctftrackref(vars.selectedPatElectronsLoosePFlow_closestCtfTrackRef->at(index));

			//PF only
			electron->set_pfchargedhadroniso(vars.selectedPatElectronsLoosePFlow_PfChargedHadronIso->at(index));
			electron->set_pfgammaiso(vars.selectedPatElectronsLoosePFlow_PFGammaIso->at(index));
			electron->set_pfneutralhadroniso(vars.selectedPatElectronsLoosePFlow_PfNeutralHadronIso->at(index));
		}

	}

	void fillElectrons(HEP::Event* event) {
		unsigned int nCaloEle = vars.selectedPatElectrons_Energy->size();

		for (unsigned int index = 0; index < nCaloEle; ++index) {
			fillElectron(event->add_selectedpatelectrons(), "selectedPatElectrons", index);
		}

		unsigned int nPFEle = vars.selectedPatElectronsLoosePFlow_Energy->size();

		for (unsigned int index = 0; index < nPFEle; ++index) {
			fillElectron(event->add_selectedpatelectronsloosepflow(), "selectedPatElectronsLoosePFlow", index);
		}

	}

	void fillMET(HEP::MET* met, string prefix, unsigned int index) {
		if (prefix == "patMETs") {
			met->set_type(HEP::MET::Calo);
			met->set_et(vars.patMETs_ET->at(index));
			met->set_etuncorr(vars.patMETs_ETUncorr->at(index));
			met->set_ex(vars.patMETs_Ex->at(index));
			met->set_ey(vars.patMETs_Ey->at(index));
			met->set_phi(vars.patMETs_Phi->at(index));
			met->set_phiuncorr(vars.patMETs_PhiUncorr->at(index));
			met->set_significance(vars.patMETs_Significance->at(index));
			met->set_sumet(vars.patMETs_SumET->at(index));
			met->set_sumetuncorr(vars.patMETs_SumETUncorr->at(index));
		}

		if (prefix == "patMETsPFlow") {
			met->set_type(HEP::MET::ParticleFlow);
			met->set_et(vars.patMETsPFlow_ET->at(index));
			met->set_etuncorr(vars.patMETsPFlow_ETUncorr->at(index));
			met->set_ex(vars.patMETsPFlow_Ex->at(index));
			met->set_ey(vars.patMETsPFlow_Ey->at(index));
			met->set_phi(vars.patMETsPFlow_Phi->at(index));
			met->set_phiuncorr(vars.patMETsPFlow_PhiUncorr->at(index));
			met->set_significance(vars.patMETsPFlow_Significance->at(index));
			met->set_sumet(vars.patMETsPFlow_SumET->at(index));
			met->set_sumetuncorr(vars.patMETsPFlow_SumETUncorr->at(index));
		}

	}

	void fillMETs(HEP::Event* event) {
		unsigned int nCaloMET = vars.patMETs_ET->size();
		for (unsigned int index = 0; index < nCaloMET; ++index) {
			fillMET(event->add_patmets(), "patMETs", index);
		}

		unsigned int nPFMET = vars.patMETs_ET->size();
		for (unsigned int index = 0; index < nPFMET; ++index) {
			fillMET(event->add_patmetspflow(), "patMETsPFlow", index);
		}

	}

	void fillMuon(HEP::Muon* muon, string prefix, unsigned int index) {
		if (prefix == "selectedPatMuons") {
			muon->set_type(HEP::Muon::Default);

			muon->set_energy(vars.selectedPatMuons_Energy->at(index));
			muon->set_px(vars.selectedPatMuons_Px->at(index));
			muon->set_py(vars.selectedPatMuons_Py->at(index));
			muon->set_pz(vars.selectedPatMuons_Pz->at(index));
			muon->set_charge(vars.selectedPatMuons_Charge->at(index));
			muon->set_cocktailcharge(vars.selectedPatMuons_CocktailCharge->at(index));
			muon->set_cocktaileta(vars.selectedPatMuons_CocktailEta->at(index));
			muon->set_cocktailglobalchi2(vars.selectedPatMuons_CocktailGlobalChi2->at(index));
			muon->set_cocktailp(vars.selectedPatMuons_CocktailP->at(index));
			muon->set_cocktailphi(vars.selectedPatMuons_CocktailPhi->at(index));
			muon->set_cocktailpt(vars.selectedPatMuons_CocktailPt->at(index));
			muon->set_cocktailtrkd0(vars.selectedPatMuons_CocktailTrkD0->at(index));
			muon->set_cocktailtrkd0error(vars.selectedPatMuons_CocktailTrkD0Error->at(index));
			muon->set_cocktailtrkdz(vars.selectedPatMuons_CocktailTrkDz->at(index));
			muon->set_cocktailtrkdzerror(vars.selectedPatMuons_CocktailTrkDzError->at(index));
			muon->set_cocktailtrkhits(vars.selectedPatMuons_CocktailTrkHits->at(index));
			muon->set_ecaliso(vars.selectedPatMuons_EcalIso->at(index));
			muon->set_ecaliso03(vars.selectedPatMuons_EcalIso03->at(index));
			muon->set_eta(vars.selectedPatMuons_Eta->at(index));
			muon->set_globalchi2(vars.selectedPatMuons_GlobalChi2->at(index));
			muon->set_hoiso(vars.selectedPatMuons_HOIso->at(index));
			muon->set_hcaliso(vars.selectedPatMuons_HcalIso->at(index));
			muon->set_hcaliso03(vars.selectedPatMuons_HcalIso03->at(index));
			muon->set_p(vars.selectedPatMuons_P->at(index));
			muon->set_phi(vars.selectedPatMuons_Phi->at(index));
			muon->set_pt(vars.selectedPatMuons_Pt->at(index));
			muon->set_trkd0(vars.selectedPatMuons_TrkD0->at(index));
			muon->set_trkd0error(vars.selectedPatMuons_TrkD0Error->at(index));
			muon->set_trkdz(vars.selectedPatMuons_TrkDz->at(index));
			muon->set_trkdzerror(vars.selectedPatMuons_TrkDzError->at(index));
			muon->set_trkhits(vars.selectedPatMuons_TrkHits->at(index));
			muon->set_trkiso(vars.selectedPatMuons_TrkIso->at(index));
			muon->set_trkiso03(vars.selectedPatMuons_TrkIso03->at(index));
			muon->set_vtxdistxy(vars.selectedPatMuons_VtxDistXY->at(index));
			muon->set_vtxdistz(vars.selectedPatMuons_VtxDistZ->at(index));
			muon->set_vtxindex(vars.selectedPatMuons_VtxIndex->at(index));
			muon->set_isgoodglobalmuon(vars.selectedPatMuons_isGoodGlobalMuon->at(index));
		}

		if (prefix == "selectedPatMuonsLoosePFlow") {
			muon->set_type(HEP::Muon::ParticleFlow);

			muon->set_energy(vars.selectedPatMuonsLoosePFlow_Energy->at(index));
			muon->set_px(vars.selectedPatMuonsLoosePFlow_Px->at(index));
			muon->set_py(vars.selectedPatMuonsLoosePFlow_Py->at(index));
			muon->set_pz(vars.selectedPatMuonsLoosePFlow_Pz->at(index));
			muon->set_charge(vars.selectedPatMuonsLoosePFlow_Charge->at(index));
			muon->set_cocktailcharge(vars.selectedPatMuonsLoosePFlow_CocktailCharge->at(index));
			muon->set_cocktaileta(vars.selectedPatMuonsLoosePFlow_CocktailEta->at(index));
			muon->set_cocktailglobalchi2(vars.selectedPatMuonsLoosePFlow_CocktailGlobalChi2->at(index));
			muon->set_cocktailp(vars.selectedPatMuonsLoosePFlow_CocktailP->at(index));
			muon->set_cocktailphi(vars.selectedPatMuonsLoosePFlow_CocktailPhi->at(index));
			muon->set_cocktailpt(vars.selectedPatMuonsLoosePFlow_CocktailPt->at(index));
			muon->set_cocktailtrkd0(vars.selectedPatMuonsLoosePFlow_CocktailTrkD0->at(index));
			muon->set_cocktailtrkd0error(vars.selectedPatMuonsLoosePFlow_CocktailTrkD0Error->at(index));
			muon->set_cocktailtrkdz(vars.selectedPatMuonsLoosePFlow_CocktailTrkDz->at(index));
			muon->set_cocktailtrkdzerror(vars.selectedPatMuonsLoosePFlow_CocktailTrkDzError->at(index));
			muon->set_cocktailtrkhits(vars.selectedPatMuonsLoosePFlow_CocktailTrkHits->at(index));
			muon->set_ecaliso(vars.selectedPatMuonsLoosePFlow_EcalIso->at(index));
			muon->set_ecaliso03(vars.selectedPatMuonsLoosePFlow_EcalIso03->at(index));
			muon->set_eta(vars.selectedPatMuonsLoosePFlow_Eta->at(index));
			muon->set_globalchi2(vars.selectedPatMuonsLoosePFlow_GlobalChi2->at(index));
			muon->set_hoiso(vars.selectedPatMuonsLoosePFlow_HOIso->at(index));
			muon->set_hcaliso(vars.selectedPatMuonsLoosePFlow_HcalIso->at(index));
			muon->set_hcaliso03(vars.selectedPatMuonsLoosePFlow_HcalIso03->at(index));
			muon->set_p(vars.selectedPatMuonsLoosePFlow_P->at(index));
			muon->set_phi(vars.selectedPatMuonsLoosePFlow_Phi->at(index));
			muon->set_pt(vars.selectedPatMuonsLoosePFlow_Pt->at(index));
			muon->set_trkd0(vars.selectedPatMuonsLoosePFlow_TrkD0->at(index));
			muon->set_trkd0error(vars.selectedPatMuonsLoosePFlow_TrkD0Error->at(index));
			muon->set_trkdz(vars.selectedPatMuonsLoosePFlow_TrkDz->at(index));
			muon->set_trkdzerror(vars.selectedPatMuonsLoosePFlow_TrkDzError->at(index));
			muon->set_trkhits(vars.selectedPatMuonsLoosePFlow_TrkHits->at(index));
			muon->set_trkiso(vars.selectedPatMuonsLoosePFlow_TrkIso->at(index));
			muon->set_trkiso03(vars.selectedPatMuonsLoosePFlow_TrkIso03->at(index));
			muon->set_vtxdistxy(vars.selectedPatMuonsLoosePFlow_VtxDistXY->at(index));
			muon->set_vtxdistz(vars.selectedPatMuonsLoosePFlow_VtxDistZ->at(index));
			muon->set_vtxindex(vars.selectedPatMuonsLoosePFlow_VtxIndex->at(index));
			muon->set_isgoodglobalmuon(vars.selectedPatMuonsLoosePFlow_isGoodGlobalMuon->at(index));

			muon->set_pfgammaiso(vars.selectedPatMuonsLoosePFlow_PFGammaIso->at(index));
			muon->set_pfchargedhadroniso(vars.selectedPatMuonsLoosePFlow_PfChargedHadronIso->at(index));
			muon->set_pfneutralhadroniso(vars.selectedPatMuonsLoosePFlow_PfNeutralHadronIso->at(index));
		}
	}

	void fillMuons(HEP::Event* event) {
		unsigned int nDefMuons = vars.selectedPatMuons_Energy->size();
		for (unsigned int index = 0; index < nDefMuons; ++index) {
			fillMuon(event->add_selectedpatmuons(), "selectedPatMuons", index);
		}

		unsigned int nPFMuons = vars.selectedPatMuonsLoosePFlow_Energy->size();
		for (unsigned int index = 0; index < nPFMuons; ++index) {
			fillMuon(event->add_selectedpatmuonsloosepflow(), "selectedPatMuonsLoosePFlow", index);
		}
	}

	void fillJet(HEP::Jet* jet, string prefix, unsigned int index) {
		if (prefix == "goodPatJets") {
			jet->set_type(HEP::Jet::Calo_AntiKT_Cone05);

			jet->set_charge(vars.goodPatJets_Charge->at(index));
			jet->set_combinedsvbjettag(vars.goodPatJets_CombinedSVBJetTag->at(index));
			jet->set_combinedsvmvabjettag(vars.goodPatJets_CombinedSVMVABJetTag->at(index));
			jet->set_emf(vars.goodPatJets_EMF->at(index));
			jet->set_energy(vars.goodPatJets_Energy->at(index));
			jet->set_energyraw(vars.goodPatJets_EnergyRaw->at(index));
			jet->set_eta(vars.goodPatJets_Eta->at(index));
			jet->set_fhpd(vars.goodPatJets_fHPD->at(index));
			jet->set_frbx(vars.goodPatJets_fRBX->at(index));
			jet->set_hadf(vars.goodPatJets_HADF->at(index));
			jet->set_jecunc(vars.goodPatJets_JECUnc->at(index));
			jet->set_jetbprobabilitybtag(vars.goodPatJets_JetBProbabilityBTag->at(index));
			jet->set_jetprobabilitybtag(vars.goodPatJets_JetProbabilityBTag->at(index));
			jet->set_l1offjec(vars.goodPatJets_L1OffJEC->at(index));
			jet->set_l2reljec(vars.goodPatJets_L2RelJEC->at(index));
			jet->set_l2l3resjec(vars.goodPatJets_L2L3ResJEC->at(index));
			jet->set_l3absjec(vars.goodPatJets_L3AbsJEC->at(index));
			jet->set_mass(vars.goodPatJets_Mass->at(index));
			jet->set_partonflavour(vars.goodPatJets_PartonFlavour->at(index));
			jet->set_passlooseid(vars.goodPatJets_PassLooseID->at(index));
			jet->set_passtightid(vars.goodPatJets_PassTightID->at(index));
			jet->set_phi(vars.goodPatJets_Phi->at(index));
			jet->set_pt(vars.goodPatJets_Pt->at(index));
			jet->set_ptraw(vars.goodPatJets_PtRaw->at(index));
			jet->set_px(vars.goodPatJets_Px->at(index));
			jet->set_py(vars.goodPatJets_Py->at(index));
			jet->set_pz(vars.goodPatJets_Pz->at(index));
			jet->set_sigmaeta(vars.goodPatJets_SigmaEta->at(index));
			jet->set_sigmaphi(vars.goodPatJets_SigmaPhi->at(index));
			jet->set_simplesecondaryvertexhigheffbtag(vars.goodPatJets_SimpleSecondaryVertexHighEffBTag->at(index));
			jet->set_simplesecondaryvertexhighpurbtag(vars.goodPatJets_SimpleSecondaryVertexHighPurBTag->at(index));
			jet->set_softelectronbjettag(vars.goodPatJets_SoftElectronBJetTag->at(index));
			jet->set_softmuonbjettag(vars.goodPatJets_SoftMuonBJetTag->at(index));
			jet->set_softmuonnoipbjettag(vars.goodPatJets_SoftMuonNoIPBJetTag->at(index));
			jet->set_trackcountinghigheffbtag(vars.goodPatJets_TrackCountingHighEffBTag->at(index));
			jet->set_trackcountinghighpurbtag(vars.goodPatJets_TrackCountingHighPurBTag->at(index));
			jet->set_n90hits(vars.goodPatJets_n90Hits->at(index));
			jet->set_resemf(vars.goodPatJets_resEMF->at(index));
		}

		if (prefix == "goodPatJetsCA8PF") {
			jet->set_type(HEP::Jet::CA08PF);

			jet->set_charge(vars.goodPatJetsCA8PF_Charge->at(index));
			jet->set_energy(vars.goodPatJetsCA8PF_Energy->at(index));
			jet->set_energyraw(vars.goodPatJetsCA8PF_EnergyRaw->at(index));
			jet->set_eta(vars.goodPatJetsCA8PF_Eta->at(index));
			jet->set_jecunc(vars.goodPatJetsCA8PF_JECUnc->at(index));
			jet->set_jetbprobabilitybtag(vars.goodPatJetsCA8PF_JetBProbabilityBTag->at(index));
			jet->set_jetprobabilitybtag(vars.goodPatJetsCA8PF_JetProbabilityBTag->at(index));
			jet->set_l1offjec(vars.goodPatJetsCA8PF_L1OffJEC->at(index));
			jet->set_l2reljec(vars.goodPatJetsCA8PF_L2RelJEC->at(index));
			jet->set_l2l3resjec(vars.goodPatJetsCA8PF_L2L3ResJEC->at(index));
			jet->set_l3absjec(vars.goodPatJetsCA8PF_L3AbsJEC->at(index));
			jet->set_mass(vars.goodPatJetsCA8PF_Mass->at(index));
			jet->set_partonflavour(vars.goodPatJetsCA8PF_PartonFlavour->at(index));
			jet->set_passlooseid(vars.goodPatJetsCA8PF_PassLooseID->at(index));
			jet->set_passtightid(vars.goodPatJetsCA8PF_PassTightID->at(index));
			jet->set_phi(vars.goodPatJetsCA8PF_Phi->at(index));
			jet->set_pt(vars.goodPatJetsCA8PF_Pt->at(index));
			jet->set_ptraw(vars.goodPatJetsCA8PF_PtRaw->at(index));
			jet->set_px(vars.goodPatJetsCA8PF_Px->at(index));
			jet->set_py(vars.goodPatJetsCA8PF_Py->at(index));
			jet->set_pz(vars.goodPatJetsCA8PF_Pz->at(index));
			jet->set_simplesecondaryvertexhigheffbtag(
					vars.goodPatJetsCA8PF_SimpleSecondaryVertexHighEffBTag->at(index));
			jet->set_simplesecondaryvertexhighpurbtag(
					vars.goodPatJetsCA8PF_SimpleSecondaryVertexHighPurBTag->at(index));
			jet->set_trackcountinghigheffbtag(vars.goodPatJetsCA8PF_TrackCountingHighEffBTag->at(index));
			jet->set_trackcountinghighpurbtag(vars.goodPatJetsCA8PF_TrackCountingHighPurBTag->at(index));

			//PF Only
			jet->set_bestvertextrackassociationfactor(
					vars.goodPatJetsCA8PF_BestVertexTrackAssociationFactor->at(index));
			jet->set_bestvertextrackassociationindex(vars.goodPatJetsCA8PF_BestVertexTrackAssociationIndex->at(index));
			jet->set_chargedemenergyfraction(vars.goodPatJetsCA8PF_ChargedEmEnergyFraction->at(index));
			jet->set_chargedemenergyfractionraw(vars.goodPatJetsCA8PF_ChargedEmEnergyFractionRAW->at(index));
			jet->set_chargedhadronenergyfraction(vars.goodPatJetsCA8PF_ChargedHadronEnergyFraction->at(index));
			jet->set_chargedhadronenergyfractionraw(vars.goodPatJetsCA8PF_ChargedHadronEnergyFractionRAW->at(index));
			jet->set_chargedhadronmultiplicity(vars.goodPatJetsCA8PF_ChargedHadronMultiplicity->at(index));
			jet->set_chargedmuenergyfraction(vars.goodPatJetsCA8PF_ChargedMuEnergyFraction->at(index));
			jet->set_chargedmultiplicity(vars.goodPatJetsCA8PF_ChargedMultiplicity->at(index));
			jet->set_neutralemenergyfraction(vars.goodPatJetsCA8PF_NeutralEmEnergyFraction->at(index));
			jet->set_neutralemenergyfractionraw(vars.goodPatJetsCA8PF_NeutralEmEnergyFractionRAW->at(index));
			jet->set_neutralhadronenergyfraction(vars.goodPatJetsCA8PF_NeutralHadronEnergyFraction->at(index));
			jet->set_neutralhadronenergyfractionraw(vars.goodPatJetsCA8PF_NeutralHadronEnergyFractionRAW->at(index));
			jet->set_neutralhadronmultiplicity(vars.goodPatJetsCA8PF_NeutralHadronMultiplicity->at(index));
			jet->set_neutralmultiplicity(vars.goodPatJetsCA8PF_NeutralMultiplicity->at(index));
			jet->set_closestvertex3dindex(vars.goodPatJetsCA8PF_ClosestVertex3DIndex->at(index));
			jet->set_closestvertexweighted3dseparation(
					vars.goodPatJetsCA8PF_ClosestVertexWeighted3DSeparation->at(index));
			jet->set_closestvertexweightedxyseparation(
					vars.goodPatJetsCA8PF_ClosestVertexWeightedXYSeparation->at(index));
			jet->set_closestvertexweightedzseparation(
					vars.goodPatJetsCA8PF_ClosestVertexWeightedZSeparation->at(index));
			jet->set_closestvertexxyindex(vars.goodPatJetsCA8PF_ClosestVertexXYIndex->at(index));

			jet->set_closestvertexzindex(vars.goodPatJetsCA8PF_ClosestVertexZIndex->at(index));
			jet->set_electronenergyfraction(vars.goodPatJetsCA8PF_ElectronEnergyFraction->at(index));
			jet->set_muonenergyfraction(vars.goodPatJetsCA8PF_MuonEnergyFraction->at(index));
			jet->set_muonmultiplicity(vars.goodPatJetsCA8PF_MuonMultiplicity->at(index));
			jet->set_electronmultiplicity(vars.goodPatJetsCA8PF_ElectronMultiplicity->at(index));
			jet->set_photonenergyfraction(vars.goodPatJetsCA8PF_PhotonEnergyFraction->at(index));
			jet->set_photonmultiplicity(vars.goodPatJetsCA8PF_PhotonMultiplicity->at(index));
			jet->set_nconstituents(vars.goodPatJetsCA8PF_NConstituents->at(index));
		}

		if (prefix == "goodPatJetsPFlow") {
			jet->set_type(HEP::Jet::PF2PAT);

			jet->set_charge(vars.goodPatJetsPFlow_Charge->at(index));
			jet->set_energy(vars.goodPatJetsPFlow_Energy->at(index));
			jet->set_energyraw(vars.goodPatJetsPFlow_EnergyRaw->at(index));
			jet->set_eta(vars.goodPatJetsPFlow_Eta->at(index));
			jet->set_jecunc(vars.goodPatJetsPFlow_JECUnc->at(index));
			jet->set_jetbprobabilitybtag(vars.goodPatJetsPFlow_JetBProbabilityBTag->at(index));
			jet->set_jetprobabilitybtag(vars.goodPatJetsPFlow_JetProbabilityBTag->at(index));
			jet->set_l1offjec(vars.goodPatJetsPFlow_L1OffJEC->at(index));
			jet->set_l2reljec(vars.goodPatJetsPFlow_L2RelJEC->at(index));
			jet->set_l2l3resjec(vars.goodPatJetsPFlow_L2L3ResJEC->at(index));
			jet->set_l3absjec(vars.goodPatJetsPFlow_L3AbsJEC->at(index));
			jet->set_mass(vars.goodPatJetsPFlow_Mass->at(index));
			jet->set_partonflavour(vars.goodPatJetsPFlow_PartonFlavour->at(index));
			jet->set_passlooseid(vars.goodPatJetsPFlow_PassLooseID->at(index));
			jet->set_passtightid(vars.goodPatJetsPFlow_PassTightID->at(index));
			jet->set_phi(vars.goodPatJetsPFlow_Phi->at(index));
			jet->set_pt(vars.goodPatJetsPFlow_Pt->at(index));
			jet->set_ptraw(vars.goodPatJetsPFlow_PtRaw->at(index));
			jet->set_px(vars.goodPatJetsPFlow_Px->at(index));
			jet->set_py(vars.goodPatJetsPFlow_Py->at(index));
			jet->set_pz(vars.goodPatJetsPFlow_Pz->at(index));
			jet->set_simplesecondaryvertexhigheffbtag(
					vars.goodPatJetsPFlow_SimpleSecondaryVertexHighEffBTag->at(index));
			jet->set_simplesecondaryvertexhighpurbtag(
					vars.goodPatJetsPFlow_SimpleSecondaryVertexHighPurBTag->at(index));
			jet->set_trackcountinghigheffbtag(vars.goodPatJetsPFlow_TrackCountingHighEffBTag->at(index));
			jet->set_trackcountinghighpurbtag(vars.goodPatJetsPFlow_TrackCountingHighPurBTag->at(index));

			//PF Only
			jet->set_bestvertextrackassociationfactor(
					vars.goodPatJetsPFlow_BestVertexTrackAssociationFactor->at(index));
			jet->set_bestvertextrackassociationindex(vars.goodPatJetsPFlow_BestVertexTrackAssociationIndex->at(index));
			jet->set_chargedemenergyfraction(vars.goodPatJetsPFlow_ChargedEmEnergyFraction->at(index));
			jet->set_chargedemenergyfractionraw(vars.goodPatJetsPFlow_ChargedEmEnergyFractionRAW->at(index));
			jet->set_chargedhadronenergyfraction(vars.goodPatJetsPFlow_ChargedHadronEnergyFraction->at(index));
			jet->set_chargedhadronenergyfractionraw(vars.goodPatJetsPFlow_ChargedHadronEnergyFractionRAW->at(index));
			jet->set_chargedhadronmultiplicity(vars.goodPatJetsPFlow_ChargedHadronMultiplicity->at(index));
			jet->set_chargedmuenergyfraction(vars.goodPatJetsPFlow_ChargedMuEnergyFraction->at(index));
			jet->set_chargedmultiplicity(vars.goodPatJetsPFlow_ChargedMultiplicity->at(index));
			jet->set_neutralemenergyfraction(vars.goodPatJetsPFlow_NeutralEmEnergyFraction->at(index));
			jet->set_neutralemenergyfractionraw(vars.goodPatJetsPFlow_NeutralEmEnergyFractionRAW->at(index));
			jet->set_neutralhadronenergyfraction(vars.goodPatJetsPFlow_NeutralHadronEnergyFraction->at(index));
			jet->set_neutralhadronenergyfractionraw(vars.goodPatJetsPFlow_NeutralHadronEnergyFractionRAW->at(index));
			jet->set_neutralhadronmultiplicity(vars.goodPatJetsPFlow_NeutralHadronMultiplicity->at(index));
			jet->set_neutralmultiplicity(vars.goodPatJetsPFlow_NeutralMultiplicity->at(index));
			jet->set_closestvertex3dindex(vars.goodPatJetsPFlow_ClosestVertex3DIndex->at(index));
			jet->set_closestvertexweighted3dseparation(
					vars.goodPatJetsPFlow_ClosestVertexWeighted3DSeparation->at(index));
			jet->set_closestvertexweightedxyseparation(
					vars.goodPatJetsPFlow_ClosestVertexWeightedXYSeparation->at(index));
			jet->set_closestvertexweightedzseparation(
					vars.goodPatJetsPFlow_ClosestVertexWeightedZSeparation->at(index));
			jet->set_closestvertexxyindex(vars.goodPatJetsPFlow_ClosestVertexXYIndex->at(index));
			jet->set_closestvertexzindex(vars.goodPatJetsPFlow_ClosestVertexZIndex->at(index));
			jet->set_electronenergyfraction(vars.goodPatJetsPFlow_ElectronEnergyFraction->at(index));
			jet->set_muonenergyfraction(vars.goodPatJetsPFlow_MuonEnergyFraction->at(index));
			jet->set_muonmultiplicity(vars.goodPatJetsPFlow_MuonMultiplicity->at(index));
			jet->set_electronmultiplicity(vars.goodPatJetsPFlow_ElectronMultiplicity->at(index));
			jet->set_photonenergyfraction(vars.goodPatJetsPFlow_PhotonEnergyFraction->at(index));
			jet->set_photonmultiplicity(vars.goodPatJetsPFlow_PhotonMultiplicity->at(index));
			jet->set_nconstituents(vars.goodPatJetsPFlow_NConstituents->at(index));
		}
	}

	void fillJets(HEP::Event* event) {
		unsigned int nCaloJets = vars.goodPatJets_Energy->size();
		for (unsigned int index = 0; index < nCaloJets; ++index) {
			fillJet(event->add_goodpatjets(), "goodPatJets", index);
		}

		unsigned int nPFJets = vars.goodPatJetsPFlow_Energy->size();
		for (unsigned int index = 0; index < nPFJets; ++index) {
			fillJet(event->add_goodpatjetspflow(), "goodPatJetsPFlow", index);
		}

		unsigned int nPFCAJets = vars.goodPatJetsCA8PF_Energy->size();
		for (unsigned int index = 0; index < nPFCAJets; ++index) {
			fillJet(event->add_goodpatjetsca8pf(), "goodPatJetsCA8PF", index);
		}

	}

	void fillVertex(HEP::Vertex* vertex, unsigned int index) {
		vertex->set_chi2(vars.goodOfflinePrimaryVertices_Chi2->at(index));
		vertex->set_x(vars.goodOfflinePrimaryVertices_X->at(index));
		vertex->set_y(vars.goodOfflinePrimaryVertices_Y->at(index));
		vertex->set_z(vars.goodOfflinePrimaryVertices_Z->at(index));
		vertex->set_xerr(vars.goodOfflinePrimaryVertices_XErr->at(index));
		vertex->set_yerr(vars.goodOfflinePrimaryVertices_YErr->at(index));
		vertex->set_zerr(vars.goodOfflinePrimaryVertices_ZErr->at(index));
		vertex->set_isfake(vars.goodOfflinePrimaryVertices_IsFake->at(index));
		vertex->set_ndf(vars.goodOfflinePrimaryVertices_NDF->at(index));
		vertex->set_ntracks(vars.goodOfflinePrimaryVertices_NTracks->at(index));
		vertex->set_ntracksw05(vars.goodOfflinePrimaryVertices_NTracksW05->at(index));
		vertex->set_rho(vars.goodOfflinePrimaryVertices_Rho->at(index));
	}

	void fillVerticies(HEP::Event* event) {
		unsigned int nVertex = vars.goodOfflinePrimaryVertices_Chi2->size();
		for (unsigned int index = 0; index < nVertex; ++index) {
			fillVertex(event->add_goodofflineprimaryvertices(), index);
		}
	}

	void fillBeamSpot(HEP::BeamSpot* beamSpot, unsigned int index) {
		beamSpot->set_widthx(vars.BeamSpot_WidthX->at(index));
		beamSpot->set_widthxerror(vars.BeamSpot_WidthXError->at(index));
		beamSpot->set_widthy(vars.BeamSpot_WidthY->at(index));
		beamSpot->set_widthyerror(vars.BeamSpot_WidthYError->at(index));
		beamSpot->set_x0(vars.BeamSpot_X0->at(index));
		beamSpot->set_x0error(vars.BeamSpot_X0Error->at(index));
		beamSpot->set_y0(vars.BeamSpot_Y0->at(index));
		beamSpot->set_y0error(vars.BeamSpot_Y0Error->at(index));
		beamSpot->set_z0(vars.BeamSpot_Z0->at(index));
		beamSpot->set_z0error(vars.BeamSpot_Z0Error->at(index));
		beamSpot->set_dxdz(vars.BeamSpot_dxdz->at(index));
		beamSpot->set_dxdzerror(vars.BeamSpot_dxdzError->at(index));
		beamSpot->set_dydz(vars.BeamSpot_dydz->at(index));
		beamSpot->set_dydzerror(vars.BeamSpot_dydzError->at(index));
		beamSpot->set_sigmaz(vars.BeamSpot_sigmaZ->at(index));
		beamSpot->set_sigmazerror(vars.BeamSpot_sigmaZError->at(index));
	}

	void fillBeamSpots(HEP::Event* event) {
		for (unsigned int index = 0; index < vars.BeamSpot_WidthX->size(); ++index) {
			fillBeamSpot(event->add_beamspot(), index);
		}
	}

	void fillTrigger(HEP::Event* event) {
		HEP::Trigger* trigger = event->add_trigger();

		for (unsigned int index = 0; index < vars.Trigger_HLTBits->size(); ++index)
			trigger->add_hltbits(vars.Trigger_HLTBits->at(index));

		for (unsigned int index = 0; index < vars.Trigger_HLTNames->size(); ++index)
			trigger->add_hltnames(vars.Trigger_HLTNames->at(index));

		for (unsigned int index = 0; index < vars.Trigger_HLTPrescales->size(); ++index)
			trigger->add_hltprescales(vars.Trigger_HLTPrescales->at(index));

		for (unsigned int index = 0; index < vars.Trigger_HLTPrescalesOther->size(); ++index)
			trigger->add_hltprescalesother(vars.Trigger_HLTPrescalesOther->at(index));

		for (unsigned int index = 0; index < vars.Trigger_HLTResults->size(); ++index)
			trigger->add_hltresults(vars.Trigger_HLTResults->at(index));

		for (unsigned int index = 0; index < vars.Trigger_HLTResultsOther->size(); ++index)
			trigger->add_hltresultsother(vars.Trigger_HLTResultsOther->at(index));

		for (unsigned int index = 0; index < vars.Trigger_L1PhysBits->size(); ++index)
			trigger->add_l1physbits(vars.Trigger_L1PhysBits->at(index));

		for (unsigned int index = 0; index < vars.Trigger_L1TechBits->size(); ++index)
			trigger->add_l1techbits(vars.Trigger_L1TechBits->at(index));

	}

	void fillEvent(HEP::Event* event) {
		event->set_magneticfield(vars.Event_MagneticField);
		event->set_run(vars.Event_Run);
		event->set_number(vars.Event_Number);
		event->set_bunch(vars.Event_Bunch);
		event->set_lumisection(vars.Event_LumiSection);
		event->set_orbit(vars.Event_Orbit);
		event->set_time(vars.Event_Time);
		event->set_isdata(vars.Event_isData);
		event->set_rho(vars.Event_rho);

		fillJets(event);
		fillVerticies(event);
		fillElectrons(event);
		fillMETs(event);
		fillMuons(event);
		fillBeamSpots(event);
		fillTrigger(event);
	}

	void fillGenParticle(HEP::GenParticle* particle, unsigned int index) {
		particle->set_energy(vars.GenParticle_Energy->at(index));
		particle->set_energy(vars.GenParticle_Eta->at(index));
		particle->set_energy(vars.GenParticle_MotherIndex->at(index));
		particle->set_energy(vars.GenParticle_NumDaught->at(index));
		particle->set_energy(vars.GenParticle_PdgId->at(index));
		particle->set_energy(vars.GenParticle_Phi->at(index));
		particle->set_energy(vars.GenParticle_Pt->at(index));
		particle->set_energy(vars.GenParticle_Px->at(index));
		particle->set_energy(vars.GenParticle_Py->at(index));
		particle->set_energy(vars.GenParticle_Pz->at(index));
		particle->set_energy(vars.GenParticle_Status->at(index));
		particle->set_energy(vars.GenParticle_VX->at(index));
		particle->set_energy(vars.GenParticle_VY->at(index));
		particle->set_energy(vars.GenParticle_VZ->at(index));
	}

	void fillGenParticles(HEP::GenEvent* event) {
		for (unsigned int index = 0; index < vars.GenParticle_Energy->size(); ++index) {
			fillGenParticle(event->add_genparticles(), index);
		}
	}

	void fillGenJet(HEP::GenJet* jet, unsigned int index) {
		jet->set_charge(vars.GenJet_Charge->at(index));
		jet->set_charge(vars.GenJet_EMF->at(index));
		jet->set_charge(vars.GenJet_Energy->at(index));
		jet->set_charge(vars.GenJet_Eta->at(index));
		jet->set_charge(vars.GenJet_HADF->at(index));
		jet->set_charge(vars.GenJet_Mass->at(index));
		jet->set_charge(vars.GenJet_Phi->at(index));
		jet->set_charge(vars.GenJet_Pt->at(index));
		jet->set_charge(vars.GenJet_Px->at(index));
		jet->set_charge(vars.GenJet_Py->at(index));
		jet->set_charge(vars.GenJet_Pz->at(index));
	}

	void fillGenJets(HEP::GenEvent* event) {
		for (unsigned int index = 0; index < vars.GenJet_Energy->size(); ++index)
			fillGenJet(event->add_genjets(), index);
	}

	void fillGenEvent(HEP::GenEvent* event) {
		for (unsigned int index = 0; index < vars.GenMETExTrue->size(); ++index) {
			event->add_genmetextrue(vars.GenMETExTrue->at(index));
			event->add_genmeteytrue(vars.GenMETEyTrue->at(index));
		}

		for (unsigned int index = 0; index < vars.Event_PDFWeights->size(); ++index)
			event->add_pdfweights(vars.Event_PDFWeights->at(index));

		for (unsigned int index = 0; index < vars.Event_PileUpInteractions->size(); ++index)
			event->add_pileupinteractions(vars.Event_PileUpInteractions->at(index));

		for (unsigned int index = 0; index < vars.Event_PileUpOriginBX->size(); ++index)
			event->add_pileuporiginbx(vars.Event_PileUpOriginBX->at(index));

		event->set_processid(vars.Event_ProcessID);
		event->set_pthat(vars.Event_PtHat);
		fillGenJets(event);
		fillGenParticles(event);
	}

	void storeChain(string outputFolder, string outputfile, unsigned int numberOfEventsPerFile,
			unsigned short compressionLevel, unsigned long maxFiles) {
		using boost::format;

		unsigned long NprocessedEvents(0), eventCounter(0), nFiles(0);
		shared_ptr<HEP::EventCollection> eventCollection = shared_ptr<HEP::EventCollection>(new HEP::EventCollection());
		bool allWritten(false);

		for (unsigned int index = 0; index < data->GetEntries(); ++index) {
			data->GetEntry(index);
			data->LoadTree(index);

			if (eventCounter >= numberOfEventsPerFile || nFiles >= maxFiles) {
				eventCounter = 0;
				stringstream filename;

				filename << outputFolder << outputfile << "_" << numberOfEventsPerFile << "EventsPerFile_gzip";
				filename << compressionLevel << "_" << format("%09d") % nFiles << ".event";
				writeEventCollection(eventCollection, filename.str(), compressionLevel);
				eventCollection->Clear();
				++nFiles;
				allWritten = true;
				if (nFiles >= maxFiles)
					break;
			}
			fillEvent(eventCollection->add_event());
			if (data->GetBranch("Event.ProcessID") != NULL)
				fillGenEvent(eventCollection->add_genevent());
			allWritten = false;
			++eventCounter;
			++NprocessedEvents;
			if(NprocessedEvents%10000 == 0)
				cout << "Processed " << NprocessedEvents << " events." << endl;

		}

		if(!allWritten){//last few events are not yet written to disc
			stringstream filename;
			filename << outputFolder << outputfile << "_" << numberOfEventsPerFile << "EventsPerFile_gzip";
			filename << compressionLevel << "_" << format("%09d") % nFiles << ".event";
			writeEventCollection(eventCollection, filename.str(), compressionLevel);
			eventCollection->Clear();
		}

	}
};

