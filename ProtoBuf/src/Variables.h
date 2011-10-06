//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sun Oct  2 18:08:59 2011 by ROOT version 5.30/00
// from TChain rootTupleTree/tree/
//////////////////////////////////////////////////////////

#ifndef Variables_h
#define Variables_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <vector>

using namespace std;

class Variables {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain

   // Declaration of leaf types
   vector<string>  *Trigger_HLTNames;
   Bool_t          Event_isData;
   Double_t        Event_MagneticField;
   Double_t        Event_Time;
   Double_t        Event_rho;
   Double_t        Event_PtHat;
   vector<double>  *selectedPatMuons_CocktailEta;
   vector<double>  *selectedPatMuons_CocktailGlobalChi2;
   vector<double>  *selectedPatMuons_CocktailP;
   vector<double>  *selectedPatMuons_CocktailPhi;
   vector<double>  *selectedPatMuons_CocktailPt;
   vector<double>  *selectedPatMuons_CocktailTrkD0;
   vector<double>  *selectedPatMuons_CocktailTrkD0Error;
   vector<double>  *selectedPatMuons_CocktailTrkDz;
   vector<double>  *selectedPatMuons_CocktailTrkDzError;
   vector<double>  *selectedPatMuons_EcalIso;
   vector<double>  *selectedPatMuons_EcalIso03;
   vector<double>  *selectedPatMuons_Energy;
   vector<double>  *selectedPatMuons_Eta;
   vector<double>  *selectedPatMuons_GlobalChi2;
   vector<double>  *selectedPatMuons_HOIso;
   vector<double>  *selectedPatMuons_HcalIso;
   vector<double>  *selectedPatMuons_HcalIso03;
   vector<double>  *selectedPatMuons_P;
   vector<double>  *selectedPatMuons_Phi;
   vector<double>  *selectedPatMuons_Pt;
   vector<double>  *selectedPatMuons_Px;
   vector<double>  *selectedPatMuons_Py;
   vector<double>  *selectedPatMuons_Pz;
   vector<double>  *selectedPatMuons_TrkD0;
   vector<double>  *selectedPatMuons_TrkD0Error;
   vector<double>  *selectedPatMuons_TrkDz;
   vector<double>  *selectedPatMuons_TrkDzError;
   vector<double>  *selectedPatMuons_TrkIso;
   vector<double>  *selectedPatMuons_TrkIso03;
   vector<double>  *selectedPatMuons_VtxDistXY;
   vector<double>  *selectedPatMuons_VtxDistZ;
   vector<double>  *selectedPatMuonsLoosePFlow_CocktailEta;
   vector<double>  *selectedPatMuonsLoosePFlow_CocktailGlobalChi2;
   vector<double>  *selectedPatMuonsLoosePFlow_CocktailP;
   vector<double>  *selectedPatMuonsLoosePFlow_CocktailPhi;
   vector<double>  *selectedPatMuonsLoosePFlow_CocktailPt;
   vector<double>  *selectedPatMuonsLoosePFlow_CocktailTrkD0;
   vector<double>  *selectedPatMuonsLoosePFlow_CocktailTrkD0Error;
   vector<double>  *selectedPatMuonsLoosePFlow_CocktailTrkDz;
   vector<double>  *selectedPatMuonsLoosePFlow_CocktailTrkDzError;
   vector<double>  *selectedPatMuonsLoosePFlow_EcalIso;
   vector<double>  *selectedPatMuonsLoosePFlow_EcalIso03;
   vector<double>  *selectedPatMuonsLoosePFlow_Energy;
   vector<double>  *selectedPatMuonsLoosePFlow_Eta;
   vector<double>  *selectedPatMuonsLoosePFlow_GlobalChi2;
   vector<double>  *selectedPatMuonsLoosePFlow_HOIso;
   vector<double>  *selectedPatMuonsLoosePFlow_HcalIso;
   vector<double>  *selectedPatMuonsLoosePFlow_HcalIso03;
   vector<double>  *selectedPatMuonsLoosePFlow_P;
   vector<double>  *selectedPatMuonsLoosePFlow_PFGammaIso;
   vector<double>  *selectedPatMuonsLoosePFlow_PfChargedHadronIso;
   vector<double>  *selectedPatMuonsLoosePFlow_PfNeutralHadronIso;
   vector<double>  *selectedPatMuonsLoosePFlow_Phi;
   vector<double>  *selectedPatMuonsLoosePFlow_Pt;
   vector<double>  *selectedPatMuonsLoosePFlow_Px;
   vector<double>  *selectedPatMuonsLoosePFlow_Py;
   vector<double>  *selectedPatMuonsLoosePFlow_Pz;
   vector<double>  *selectedPatMuonsLoosePFlow_TrkD0;
   vector<double>  *selectedPatMuonsLoosePFlow_TrkD0Error;
   vector<double>  *selectedPatMuonsLoosePFlow_TrkDz;
   vector<double>  *selectedPatMuonsLoosePFlow_TrkDzError;
   vector<double>  *selectedPatMuonsLoosePFlow_TrkIso;
   vector<double>  *selectedPatMuonsLoosePFlow_TrkIso03;
   vector<double>  *selectedPatMuonsLoosePFlow_VtxDistXY;
   vector<double>  *selectedPatMuonsLoosePFlow_VtxDistZ;
   vector<double>  *BeamSpot_WidthX;
   vector<double>  *BeamSpot_WidthXError;
   vector<double>  *BeamSpot_WidthY;
   vector<double>  *BeamSpot_WidthYError;
   vector<double>  *BeamSpot_X0;
   vector<double>  *BeamSpot_X0Error;
   vector<double>  *BeamSpot_Y0;
   vector<double>  *BeamSpot_Y0Error;
   vector<double>  *BeamSpot_Z0;
   vector<double>  *BeamSpot_Z0Error;
   vector<double>  *BeamSpot_dxdz;
   vector<double>  *BeamSpot_dxdzError;
   vector<double>  *BeamSpot_dydz;
   vector<double>  *BeamSpot_dydzError;
   vector<double>  *BeamSpot_sigmaZ;
   vector<double>  *BeamSpot_sigmaZError;
   vector<double>  *goodPatJetsCA8PF_BestVertexTrackAssociationFactor;
   vector<double>  *goodPatJetsCA8PF_Charge;
   vector<double>  *goodPatJetsCA8PF_ChargedEmEnergyFraction;
   vector<double>  *goodPatJetsCA8PF_ChargedEmEnergyFractionRAW;
   vector<double>  *goodPatJetsCA8PF_ChargedHadronEnergyFraction;
   vector<double>  *goodPatJetsCA8PF_ChargedHadronEnergyFractionRAW;
   vector<double>  *goodPatJetsCA8PF_ChargedMuEnergyFraction;
   vector<double>  *goodPatJetsCA8PF_ClosestVertexWeighted3DSeparation;
   vector<double>  *goodPatJetsCA8PF_ClosestVertexWeightedXYSeparation;
   vector<double>  *goodPatJetsCA8PF_ClosestVertexWeightedZSeparation;
   vector<double>  *goodPatJetsCA8PF_ElectronEnergyFraction;
   vector<double>  *goodPatJetsCA8PF_Energy;
   vector<double>  *goodPatJetsCA8PF_EnergyRaw;
   vector<double>  *goodPatJetsCA8PF_Eta;
   vector<double>  *goodPatJetsCA8PF_JECUnc;
   vector<double>  *goodPatJetsCA8PF_JetBProbabilityBTag;
   vector<double>  *goodPatJetsCA8PF_JetProbabilityBTag;
   vector<double>  *goodPatJetsCA8PF_L1OffJEC;
   vector<double>  *goodPatJetsCA8PF_L2L3ResJEC;
   vector<double>  *goodPatJetsCA8PF_L2RelJEC;
   vector<double>  *goodPatJetsCA8PF_L3AbsJEC;
   vector<double>  *goodPatJetsCA8PF_Mass;
   vector<double>  *goodPatJetsCA8PF_MuonEnergyFraction;
   vector<double>  *goodPatJetsCA8PF_NeutralEmEnergyFraction;
   vector<double>  *goodPatJetsCA8PF_NeutralEmEnergyFractionRAW;
   vector<double>  *goodPatJetsCA8PF_NeutralHadronEnergyFraction;
   vector<double>  *goodPatJetsCA8PF_NeutralHadronEnergyFractionRAW;
   vector<double>  *goodPatJetsCA8PF_Phi;
   vector<double>  *goodPatJetsCA8PF_PhotonEnergyFraction;
   vector<double>  *goodPatJetsCA8PF_Pt;
   vector<double>  *goodPatJetsCA8PF_PtRaw;
   vector<double>  *goodPatJetsCA8PF_Px;
   vector<double>  *goodPatJetsCA8PF_Py;
   vector<double>  *goodPatJetsCA8PF_Pz;
   vector<double>  *goodPatJetsCA8PF_SimpleSecondaryVertexHighEffBTag;
   vector<double>  *goodPatJetsCA8PF_SimpleSecondaryVertexHighPurBTag;
   vector<double>  *goodPatJetsCA8PF_TrackCountingHighEffBTag;
   vector<double>  *goodPatJetsCA8PF_TrackCountingHighPurBTag;
   vector<double>  *goodPatJets_Charge;
   vector<double>  *goodPatJets_CombinedSVBJetTag;
   vector<double>  *goodPatJets_CombinedSVMVABJetTag;
   vector<double>  *goodPatJets_EMF;
   vector<double>  *goodPatJets_Energy;
   vector<double>  *goodPatJets_EnergyRaw;
   vector<double>  *goodPatJets_Eta;
   vector<double>  *goodPatJets_HADF;
   vector<double>  *goodPatJets_JECUnc;
   vector<double>  *goodPatJets_JetBProbabilityBTag;
   vector<double>  *goodPatJets_JetProbabilityBTag;
   vector<double>  *goodPatJets_L1OffJEC;
   vector<double>  *goodPatJets_L2L3ResJEC;
   vector<double>  *goodPatJets_L2RelJEC;
   vector<double>  *goodPatJets_L3AbsJEC;
   vector<double>  *goodPatJets_Mass;
   vector<double>  *goodPatJets_Phi;
   vector<double>  *goodPatJets_Pt;
   vector<double>  *goodPatJets_PtRaw;
   vector<double>  *goodPatJets_Px;
   vector<double>  *goodPatJets_Py;
   vector<double>  *goodPatJets_Pz;
   vector<double>  *goodPatJets_SigmaEta;
   vector<double>  *goodPatJets_SigmaPhi;
   vector<double>  *goodPatJets_SimpleSecondaryVertexHighEffBTag;
   vector<double>  *goodPatJets_SimpleSecondaryVertexHighPurBTag;
   vector<double>  *goodPatJets_SoftElectronBJetTag;
   vector<double>  *goodPatJets_SoftMuonBJetTag;
   vector<double>  *goodPatJets_SoftMuonNoIPBJetTag;
   vector<double>  *goodPatJets_TrackCountingHighEffBTag;
   vector<double>  *goodPatJets_TrackCountingHighPurBTag;
   vector<double>  *goodPatJets_fHPD;
   vector<double>  *goodPatJets_fRBX;
   vector<double>  *goodPatJets_resEMF;
   vector<double>  *patMETs_ET;
   vector<double>  *patMETs_ETUncorr;
   vector<double>  *patMETs_Ex;
   vector<double>  *patMETs_Ey;
   vector<double>  *patMETs_Phi;
   vector<double>  *patMETs_PhiUncorr;
   vector<double>  *patMETs_Significance;
   vector<double>  *patMETs_SumET;
   vector<double>  *patMETs_SumETUncorr;
   vector<double>  *selectedPatElectrons_CaloEnergy;
   vector<double>  *selectedPatElectrons_DCotTheta;
   vector<double>  *selectedPatElectrons_DeltaEtaTrkSC;
   vector<double>  *selectedPatElectrons_DeltaPhiTrkSC;
   vector<double>  *selectedPatElectrons_Dist;
   vector<double>  *selectedPatElectrons_EcalIso;
   vector<double>  *selectedPatElectrons_EcalIso03;
   vector<double>  *selectedPatElectrons_EcalIsoHeep;
   vector<double>  *selectedPatElectrons_Energy;
   vector<double>  *selectedPatElectrons_EoverP;
   vector<double>  *selectedPatElectrons_Eta;
   vector<double>  *selectedPatElectrons_GSFTrack_Eta;
   vector<double>  *selectedPatElectrons_GSFTrack_Phi;
   vector<double>  *selectedPatElectrons_GSFTrack_Pt;
   vector<double>  *selectedPatElectrons_GSFTrack_Theta;
   vector<double>  *selectedPatElectrons_GSFTrack_d0;
   vector<double>  *selectedPatElectrons_HcalIso;
   vector<double>  *selectedPatElectrons_HcalIso03;
   vector<double>  *selectedPatElectrons_HcalIsoD1Heep;
   vector<double>  *selectedPatElectrons_HcalIsoD2Heep;
   vector<double>  *selectedPatElectrons_HoE;
   vector<double>  *selectedPatElectrons_Phi;
   vector<double>  *selectedPatElectrons_Pt;
   vector<double>  *selectedPatElectrons_Px;
   vector<double>  *selectedPatElectrons_Py;
   vector<double>  *selectedPatElectrons_Pz;
   vector<double>  *selectedPatElectrons_SCEta;
   vector<double>  *selectedPatElectrons_SCPhi;
   vector<double>  *selectedPatElectrons_SCPt;
   vector<double>  *selectedPatElectrons_SCRawEnergy;
   vector<double>  *selectedPatElectrons_SigmaEtaEta;
   vector<double>  *selectedPatElectrons_SigmaIEtaIEta;
   vector<double>  *selectedPatElectrons_TrkIso;
   vector<double>  *selectedPatElectrons_TrkIso03;
   vector<double>  *selectedPatElectrons_TrkIsoHeep;
   vector<double>  *selectedPatElectrons_Vertex_X;
   vector<double>  *selectedPatElectrons_Vertex_Y;
   vector<double>  *selectedPatElectrons_Vertex_Z;
   vector<double>  *selectedPatElectrons_VtxDistXY;
   vector<double>  *selectedPatElectrons_VtxDistZ;
   vector<double>  *selectedPatElectrons_dB;
   vector<double>  *selectedPatElectrons_eSeedClusterOverPout;
   vector<double>  *selectedPatElectrons_fbrem;
   vector<double>  *selectedPatElectrons_shFracInnerHits;
   vector<double>  *Event_PDFWeights;
   vector<double>  *GenJet_Charge;
   vector<double>  *GenJet_EMF;
   vector<double>  *GenJet_Energy;
   vector<double>  *GenJet_Eta;
   vector<double>  *GenJet_HADF;
   vector<double>  *GenJet_Mass;
   vector<double>  *GenJet_Phi;
   vector<double>  *GenJet_Pt;
   vector<double>  *GenJet_Px;
   vector<double>  *GenJet_Py;
   vector<double>  *GenJet_Pz;
   vector<double>  *GenMETExTrue;
   vector<double>  *GenMETEyTrue;
   vector<double>  *GenParticle_Energy;
   vector<double>  *GenParticle_Eta;
   vector<double>  *GenParticle_Phi;
   vector<double>  *GenParticle_Pt;
   vector<double>  *GenParticle_Px;
   vector<double>  *GenParticle_Py;
   vector<double>  *GenParticle_Pz;
   vector<double>  *GenParticle_VX;
   vector<double>  *GenParticle_VY;
   vector<double>  *GenParticle_VZ;
   vector<double>  *goodPatJetsPFlow_BestVertexTrackAssociationFactor;
   vector<double>  *goodPatJetsPFlow_Charge;
   vector<double>  *goodPatJetsPFlow_ChargedEmEnergyFraction;
   vector<double>  *goodPatJetsPFlow_ChargedEmEnergyFractionRAW;
   vector<double>  *goodPatJetsPFlow_ChargedHadronEnergyFraction;
   vector<double>  *goodPatJetsPFlow_ChargedHadronEnergyFractionRAW;
   vector<double>  *goodPatJetsPFlow_ChargedMuEnergyFraction;
   vector<double>  *goodPatJetsPFlow_ClosestVertexWeighted3DSeparation;
   vector<double>  *goodPatJetsPFlow_ClosestVertexWeightedXYSeparation;
   vector<double>  *goodPatJetsPFlow_ClosestVertexWeightedZSeparation;
   vector<double>  *goodPatJetsPFlow_ElectronEnergyFraction;
   vector<double>  *goodPatJetsPFlow_Energy;
   vector<double>  *goodPatJetsPFlow_EnergyRaw;
   vector<double>  *goodPatJetsPFlow_Eta;
   vector<double>  *goodPatJetsPFlow_JECUnc;
   vector<double>  *goodPatJetsPFlow_JetBProbabilityBTag;
   vector<double>  *goodPatJetsPFlow_JetProbabilityBTag;
   vector<double>  *goodPatJetsPFlow_L1OffJEC;
   vector<double>  *goodPatJetsPFlow_L2L3ResJEC;
   vector<double>  *goodPatJetsPFlow_L2RelJEC;
   vector<double>  *goodPatJetsPFlow_L3AbsJEC;
   vector<double>  *goodPatJetsPFlow_Mass;
   vector<double>  *goodPatJetsPFlow_MuonEnergyFraction;
   vector<double>  *goodPatJetsPFlow_NeutralEmEnergyFraction;
   vector<double>  *goodPatJetsPFlow_NeutralEmEnergyFractionRAW;
   vector<double>  *goodPatJetsPFlow_NeutralHadronEnergyFraction;
   vector<double>  *goodPatJetsPFlow_NeutralHadronEnergyFractionRAW;
   vector<double>  *goodPatJetsPFlow_Phi;
   vector<double>  *goodPatJetsPFlow_PhotonEnergyFraction;
   vector<double>  *goodPatJetsPFlow_Pt;
   vector<double>  *goodPatJetsPFlow_PtRaw;
   vector<double>  *goodPatJetsPFlow_Px;
   vector<double>  *goodPatJetsPFlow_Py;
   vector<double>  *goodPatJetsPFlow_Pz;
   vector<double>  *goodPatJetsPFlow_SimpleSecondaryVertexHighEffBTag;
   vector<double>  *goodPatJetsPFlow_SimpleSecondaryVertexHighPurBTag;
   vector<double>  *goodPatJetsPFlow_TrackCountingHighEffBTag;
   vector<double>  *goodPatJetsPFlow_TrackCountingHighPurBTag;
   vector<double>  *selectedPatElectronsLoosePFlow_CaloEnergy;
   vector<double>  *selectedPatElectronsLoosePFlow_DCotTheta;
   vector<double>  *selectedPatElectronsLoosePFlow_DeltaEtaTrkSC;
   vector<double>  *selectedPatElectronsLoosePFlow_DeltaPhiTrkSC;
   vector<double>  *selectedPatElectronsLoosePFlow_Dist;
   vector<double>  *selectedPatElectronsLoosePFlow_EcalIso;
   vector<double>  *selectedPatElectronsLoosePFlow_EcalIso03;
   vector<double>  *selectedPatElectronsLoosePFlow_EcalIsoHeep;
   vector<double>  *selectedPatElectronsLoosePFlow_Energy;
   vector<double>  *selectedPatElectronsLoosePFlow_EoverP;
   vector<double>  *selectedPatElectronsLoosePFlow_Eta;
   vector<double>  *selectedPatElectronsLoosePFlow_GSFTrack_Eta;
   vector<double>  *selectedPatElectronsLoosePFlow_GSFTrack_Phi;
   vector<double>  *selectedPatElectronsLoosePFlow_GSFTrack_Pt;
   vector<double>  *selectedPatElectronsLoosePFlow_GSFTrack_Theta;
   vector<double>  *selectedPatElectronsLoosePFlow_GSFTrack_d0;
   vector<double>  *selectedPatElectronsLoosePFlow_HcalIso;
   vector<double>  *selectedPatElectronsLoosePFlow_HcalIso03;
   vector<double>  *selectedPatElectronsLoosePFlow_HcalIsoD1Heep;
   vector<double>  *selectedPatElectronsLoosePFlow_HcalIsoD2Heep;
   vector<double>  *selectedPatElectronsLoosePFlow_HoE;
   vector<double>  *selectedPatElectronsLoosePFlow_PFGammaIso;
   vector<double>  *selectedPatElectronsLoosePFlow_PfChargedHadronIso;
   vector<double>  *selectedPatElectronsLoosePFlow_PfNeutralHadronIso;
   vector<double>  *selectedPatElectronsLoosePFlow_Phi;
   vector<double>  *selectedPatElectronsLoosePFlow_Pt;
   vector<double>  *selectedPatElectronsLoosePFlow_Px;
   vector<double>  *selectedPatElectronsLoosePFlow_Py;
   vector<double>  *selectedPatElectronsLoosePFlow_Pz;
   vector<double>  *selectedPatElectronsLoosePFlow_SCEta;
   vector<double>  *selectedPatElectronsLoosePFlow_SCPhi;
   vector<double>  *selectedPatElectronsLoosePFlow_SCPt;
   vector<double>  *selectedPatElectronsLoosePFlow_SCRawEnergy;
   vector<double>  *selectedPatElectronsLoosePFlow_SigmaEtaEta;
   vector<double>  *selectedPatElectronsLoosePFlow_SigmaIEtaIEta;
   vector<double>  *selectedPatElectronsLoosePFlow_TrkIso;
   vector<double>  *selectedPatElectronsLoosePFlow_TrkIso03;
   vector<double>  *selectedPatElectronsLoosePFlow_TrkIsoHeep;
   vector<double>  *selectedPatElectronsLoosePFlow_Vertex_X;
   vector<double>  *selectedPatElectronsLoosePFlow_Vertex_Y;
   vector<double>  *selectedPatElectronsLoosePFlow_Vertex_Z;
   vector<double>  *selectedPatElectronsLoosePFlow_VtxDistXY;
   vector<double>  *selectedPatElectronsLoosePFlow_VtxDistZ;
   vector<double>  *selectedPatElectronsLoosePFlow_dB;
   vector<double>  *selectedPatElectronsLoosePFlow_eSeedClusterOverPout;
   vector<double>  *selectedPatElectronsLoosePFlow_fbrem;
   vector<double>  *selectedPatElectronsLoosePFlow_shFracInnerHits;
   vector<double>  *patMETsPFlow_ET;
   vector<double>  *patMETsPFlow_ETUncorr;
   vector<double>  *patMETsPFlow_Ex;
   vector<double>  *patMETsPFlow_Ey;
   vector<double>  *patMETsPFlow_Phi;
   vector<double>  *patMETsPFlow_PhiUncorr;
   vector<double>  *patMETsPFlow_Significance;
   vector<double>  *patMETsPFlow_SumET;
   vector<double>  *patMETsPFlow_SumETUncorr;
   vector<double>  *goodOfflinePrimaryVertices_Chi2;
   vector<double>  *goodOfflinePrimaryVertices_NDF;
   vector<double>  *goodOfflinePrimaryVertices_Rho;
   vector<double>  *goodOfflinePrimaryVertices_X;
   vector<double>  *goodOfflinePrimaryVertices_XErr;
   vector<double>  *goodOfflinePrimaryVertices_Y;
   vector<double>  *goodOfflinePrimaryVertices_YErr;
   vector<double>  *goodOfflinePrimaryVertices_Z;
   vector<double>  *goodOfflinePrimaryVertices_ZErr;
   vector<int>     *selectedPatMuons_Charge;
   vector<int>     *selectedPatMuons_CocktailCharge;
   vector<int>     *selectedPatMuons_CocktailTrkHits;
   vector<int>     *selectedPatMuons_TrkHits;
   vector<int>     *selectedPatMuons_VtxIndex;
   vector<int>     *selectedPatMuons_isGoodGlobalMuon;
   vector<int>     *selectedPatMuonsLoosePFlow_Charge;
   vector<int>     *selectedPatMuonsLoosePFlow_CocktailCharge;
   vector<int>     *selectedPatMuonsLoosePFlow_CocktailTrkHits;
   vector<int>     *selectedPatMuonsLoosePFlow_TrkHits;
   vector<int>     *selectedPatMuonsLoosePFlow_VtxIndex;
   vector<int>     *selectedPatMuonsLoosePFlow_isGoodGlobalMuon;
   vector<int>     *goodPatJetsCA8PF_BestVertexTrackAssociationIndex;
   vector<int>     *goodPatJetsCA8PF_ChargedHadronMultiplicity;
   vector<int>     *goodPatJetsCA8PF_ChargedMultiplicity;
   vector<int>     *goodPatJetsCA8PF_ClosestVertex3DIndex;
   vector<int>     *goodPatJetsCA8PF_ClosestVertexXYIndex;
   vector<int>     *goodPatJetsCA8PF_ClosestVertexZIndex;
   vector<int>     *goodPatJetsCA8PF_ElectronMultiplicity;
   vector<int>     *goodPatJetsCA8PF_MuonMultiplicity;
   vector<int>     *goodPatJetsCA8PF_NConstituents;
   vector<int>     *goodPatJetsCA8PF_NeutralHadronMultiplicity;
   vector<int>     *goodPatJetsCA8PF_NeutralMultiplicity;
   vector<int>     *goodPatJetsCA8PF_PartonFlavour;
   vector<int>     *goodPatJetsCA8PF_PassLooseID;
   vector<int>     *goodPatJetsCA8PF_PassTightID;
   vector<int>     *goodPatJetsCA8PF_PhotonMultiplicity;
   vector<int>     *goodPatJets_PartonFlavour;
   vector<int>     *goodPatJets_PassLooseID;
   vector<int>     *goodPatJets_PassTightID;
   vector<int>     *goodPatJets_n90Hits;
   vector<int>     *selectedPatElectrons_Charge;
   vector<int>     *selectedPatElectrons_GSFTrack_Charge;
   vector<int>     *selectedPatElectrons_MissingHits;
   vector<int>     *selectedPatElectrons_PassID;
   vector<int>     *selectedPatElectrons_VtxIndex;
   vector<int>     *selectedPatElectrons_closestCtfTrackRef;
   vector<int>     *Event_PileUpInteractions;
   vector<int>     *Event_PileUpOriginBX;
   vector<int>     *GenParticle_MotherIndex;
   vector<int>     *GenParticle_NumDaught;
   vector<int>     *GenParticle_PdgId;
   vector<int>     *GenParticle_Status;
   vector<int>     *goodPatJetsPFlow_BestVertexTrackAssociationIndex;
   vector<int>     *goodPatJetsPFlow_ChargedHadronMultiplicity;
   vector<int>     *goodPatJetsPFlow_ChargedMultiplicity;
   vector<int>     *goodPatJetsPFlow_ClosestVertex3DIndex;
   vector<int>     *goodPatJetsPFlow_ClosestVertexXYIndex;
   vector<int>     *goodPatJetsPFlow_ClosestVertexZIndex;
   vector<int>     *goodPatJetsPFlow_ElectronMultiplicity;
   vector<int>     *goodPatJetsPFlow_MuonMultiplicity;
   vector<int>     *goodPatJetsPFlow_NConstituents;
   vector<int>     *goodPatJetsPFlow_NeutralHadronMultiplicity;
   vector<int>     *goodPatJetsPFlow_NeutralMultiplicity;
   vector<int>     *goodPatJetsPFlow_PartonFlavour;
   vector<int>     *goodPatJetsPFlow_PassLooseID;
   vector<int>     *goodPatJetsPFlow_PassTightID;
   vector<int>     *goodPatJetsPFlow_PhotonMultiplicity;
   vector<int>     *selectedPatElectronsLoosePFlow_Charge;
   vector<int>     *selectedPatElectronsLoosePFlow_GSFTrack_Charge;
   vector<int>     *selectedPatElectronsLoosePFlow_MissingHits;
   vector<int>     *selectedPatElectronsLoosePFlow_PassID;
   vector<int>     *selectedPatElectronsLoosePFlow_VtxIndex;
   vector<int>     *selectedPatElectronsLoosePFlow_closestCtfTrackRef;
   vector<int>     *Trigger_HLTBits;
   vector<int>     *Trigger_HLTPrescales;
   vector<int>     *Trigger_HLTPrescalesOther;
   vector<int>     *Trigger_HLTResults;
   vector<int>     *Trigger_HLTResultsOther;
   vector<int>     *Trigger_L1PhysBits;
   vector<int>     *Trigger_L1TechBits;
   vector<int>     *goodOfflinePrimaryVertices_IsFake;
   vector<int>     *goodOfflinePrimaryVertices_NTracks;
   vector<int>     *goodOfflinePrimaryVertices_NTracksW05;
   UInt_t          Event_Bunch;
   UInt_t          Event_LumiSection;
   UInt_t          Event_Number;
   UInt_t          Event_Orbit;
   UInt_t          Event_Run;
   UInt_t          Event_ProcessID;

   // List of branches
   TBranch        *b_Trigger_HLTNames;   //!
   TBranch        *b_Event_isData;   //!
   TBranch        *b_Event_MagneticField;   //!
   TBranch        *b_Event_Time;   //!
   TBranch        *b_Event_rho;   //!
   TBranch        *b_Event_PtHat;   //!
   TBranch        *b_selectedPatMuons_CocktailEta;   //!
   TBranch        *b_selectedPatMuons_CocktailGlobalChi2;   //!
   TBranch        *b_selectedPatMuons_CocktailP;   //!
   TBranch        *b_selectedPatMuons_CocktailPhi;   //!
   TBranch        *b_selectedPatMuons_CocktailPt;   //!
   TBranch        *b_selectedPatMuons_CocktailTrkD0;   //!
   TBranch        *b_selectedPatMuons_CocktailTrkD0Error;   //!
   TBranch        *b_selectedPatMuons_CocktailTrkDz;   //!
   TBranch        *b_selectedPatMuons_CocktailTrkDzError;   //!
   TBranch        *b_selectedPatMuons_EcalIso;   //!
   TBranch        *b_selectedPatMuons_EcalIso03;   //!
   TBranch        *b_selectedPatMuons_Energy;   //!
   TBranch        *b_selectedPatMuons_Eta;   //!
   TBranch        *b_selectedPatMuons_GlobalChi2;   //!
   TBranch        *b_selectedPatMuons_HOIso;   //!
   TBranch        *b_selectedPatMuons_HcalIso;   //!
   TBranch        *b_selectedPatMuons_HcalIso03;   //!
   TBranch        *b_selectedPatMuons_P;   //!
   TBranch        *b_selectedPatMuons_Phi;   //!
   TBranch        *b_selectedPatMuons_Pt;   //!
   TBranch        *b_selectedPatMuons_Px;   //!
   TBranch        *b_selectedPatMuons_Py;   //!
   TBranch        *b_selectedPatMuons_Pz;   //!
   TBranch        *b_selectedPatMuons_TrkD0;   //!
   TBranch        *b_selectedPatMuons_TrkD0Error;   //!
   TBranch        *b_selectedPatMuons_TrkDz;   //!
   TBranch        *b_selectedPatMuons_TrkDzError;   //!
   TBranch        *b_selectedPatMuons_TrkIso;   //!
   TBranch        *b_selectedPatMuons_TrkIso03;   //!
   TBranch        *b_selectedPatMuons_VtxDistXY;   //!
   TBranch        *b_selectedPatMuons_VtxDistZ;   //!
   TBranch        *b_selectedPatMuonsLoosePFlow_CocktailEta;   //!
   TBranch        *b_selectedPatMuonsLoosePFlow_CocktailGlobalChi2;   //!
   TBranch        *b_selectedPatMuonsLoosePFlow_CocktailP;   //!
   TBranch        *b_selectedPatMuonsLoosePFlow_CocktailPhi;   //!
   TBranch        *b_selectedPatMuonsLoosePFlow_CocktailPt;   //!
   TBranch        *b_selectedPatMuonsLoosePFlow_CocktailTrkD0;   //!
   TBranch        *b_selectedPatMuonsLoosePFlow_CocktailTrkD0Error;   //!
   TBranch        *b_selectedPatMuonsLoosePFlow_CocktailTrkDz;   //!
   TBranch        *b_selectedPatMuonsLoosePFlow_CocktailTrkDzError;   //!
   TBranch        *b_selectedPatMuonsLoosePFlow_EcalIso;   //!
   TBranch        *b_selectedPatMuonsLoosePFlow_EcalIso03;   //!
   TBranch        *b_selectedPatMuonsLoosePFlow_Energy;   //!
   TBranch        *b_selectedPatMuonsLoosePFlow_Eta;   //!
   TBranch        *b_selectedPatMuonsLoosePFlow_GlobalChi2;   //!
   TBranch        *b_selectedPatMuonsLoosePFlow_HOIso;   //!
   TBranch        *b_selectedPatMuonsLoosePFlow_HcalIso;   //!
   TBranch        *b_selectedPatMuonsLoosePFlow_HcalIso03;   //!
   TBranch        *b_selectedPatMuonsLoosePFlow_P;   //!
   TBranch        *b_selectedPatMuonsLoosePFlow_PFGammaIso;   //!
   TBranch        *b_selectedPatMuonsLoosePFlow_PfChargedHadronIso;   //!
   TBranch        *b_selectedPatMuonsLoosePFlow_PfNeutralHadronIso;   //!
   TBranch        *b_selectedPatMuonsLoosePFlow_Phi;   //!
   TBranch        *b_selectedPatMuonsLoosePFlow_Pt;   //!
   TBranch        *b_selectedPatMuonsLoosePFlow_Px;   //!
   TBranch        *b_selectedPatMuonsLoosePFlow_Py;   //!
   TBranch        *b_selectedPatMuonsLoosePFlow_Pz;   //!
   TBranch        *b_selectedPatMuonsLoosePFlow_TrkD0;   //!
   TBranch        *b_selectedPatMuonsLoosePFlow_TrkD0Error;   //!
   TBranch        *b_selectedPatMuonsLoosePFlow_TrkDz;   //!
   TBranch        *b_selectedPatMuonsLoosePFlow_TrkDzError;   //!
   TBranch        *b_selectedPatMuonsLoosePFlow_TrkIso;   //!
   TBranch        *b_selectedPatMuonsLoosePFlow_TrkIso03;   //!
   TBranch        *b_selectedPatMuonsLoosePFlow_VtxDistXY;   //!
   TBranch        *b_selectedPatMuonsLoosePFlow_VtxDistZ;   //!
   TBranch        *b_BeamSpot_WidthX;   //!
   TBranch        *b_BeamSpot_WidthXError;   //!
   TBranch        *b_BeamSpot_WidthY;   //!
   TBranch        *b_BeamSpot_WidthYError;   //!
   TBranch        *b_BeamSpot_X0;   //!
   TBranch        *b_BeamSpot_X0Error;   //!
   TBranch        *b_BeamSpot_Y0;   //!
   TBranch        *b_BeamSpot_Y0Error;   //!
   TBranch        *b_BeamSpot_Z0;   //!
   TBranch        *b_BeamSpot_Z0Error;   //!
   TBranch        *b_BeamSpot_dxdz;   //!
   TBranch        *b_BeamSpot_dxdzError;   //!
   TBranch        *b_BeamSpot_dydz;   //!
   TBranch        *b_BeamSpot_dydzError;   //!
   TBranch        *b_BeamSpot_sigmaZ;   //!
   TBranch        *b_BeamSpot_sigmaZError;   //!
   TBranch        *b_goodPatJetsCA8PF_BestVertexTrackAssociationFactor;   //!
   TBranch        *b_goodPatJetsCA8PF_Charge;   //!
   TBranch        *b_goodPatJetsCA8PF_ChargedEmEnergyFraction;   //!
   TBranch        *b_goodPatJetsCA8PF_ChargedEmEnergyFractionRAW;   //!
   TBranch        *b_goodPatJetsCA8PF_ChargedHadronEnergyFraction;   //!
   TBranch        *b_goodPatJetsCA8PF_ChargedHadronEnergyFractionRAW;   //!
   TBranch        *b_goodPatJetsCA8PF_ChargedMuEnergyFraction;   //!
   TBranch        *b_goodPatJetsCA8PF_ClosestVertexWeighted3DSeparation;   //!
   TBranch        *b_goodPatJetsCA8PF_ClosestVertexWeightedXYSeparation;   //!
   TBranch        *b_goodPatJetsCA8PF_ClosestVertexWeightedZSeparation;   //!
   TBranch        *b_goodPatJetsCA8PF_ElectronEnergyFraction;   //!
   TBranch        *b_goodPatJetsCA8PF_Energy;   //!
   TBranch        *b_goodPatJetsCA8PF_EnergyRaw;   //!
   TBranch        *b_goodPatJetsCA8PF_Eta;   //!
   TBranch        *b_goodPatJetsCA8PF_JECUnc;   //!
   TBranch        *b_goodPatJetsCA8PF_JetBProbabilityBTag;   //!
   TBranch        *b_goodPatJetsCA8PF_JetProbabilityBTag;   //!
   TBranch        *b_goodPatJetsCA8PF_L1OffJEC;   //!
   TBranch        *b_goodPatJetsCA8PF_L2L3ResJEC;   //!
   TBranch        *b_goodPatJetsCA8PF_L2RelJEC;   //!
   TBranch        *b_goodPatJetsCA8PF_L3AbsJEC;   //!
   TBranch        *b_goodPatJetsCA8PF_Mass;   //!
   TBranch        *b_goodPatJetsCA8PF_MuonEnergyFraction;   //!
   TBranch        *b_goodPatJetsCA8PF_NeutralEmEnergyFraction;   //!
   TBranch        *b_goodPatJetsCA8PF_NeutralEmEnergyFractionRAW;   //!
   TBranch        *b_goodPatJetsCA8PF_NeutralHadronEnergyFraction;   //!
   TBranch        *b_goodPatJetsCA8PF_NeutralHadronEnergyFractionRAW;   //!
   TBranch        *b_goodPatJetsCA8PF_Phi;   //!
   TBranch        *b_goodPatJetsCA8PF_PhotonEnergyFraction;   //!
   TBranch        *b_goodPatJetsCA8PF_Pt;   //!
   TBranch        *b_goodPatJetsCA8PF_PtRaw;   //!
   TBranch        *b_goodPatJetsCA8PF_Px;   //!
   TBranch        *b_goodPatJetsCA8PF_Py;   //!
   TBranch        *b_goodPatJetsCA8PF_Pz;   //!
   TBranch        *b_goodPatJetsCA8PF_SimpleSecondaryVertexHighEffBTag;   //!
   TBranch        *b_goodPatJetsCA8PF_SimpleSecondaryVertexHighPurBTag;   //!
   TBranch        *b_goodPatJetsCA8PF_TrackCountingHighEffBTag;   //!
   TBranch        *b_goodPatJetsCA8PF_TrackCountingHighPurBTag;   //!
   TBranch        *b_goodPatJets_Charge;   //!
   TBranch        *b_goodPatJets_CombinedSVBJetTag;   //!
   TBranch        *b_goodPatJets_CombinedSVMVABJetTag;   //!
   TBranch        *b_goodPatJets_EMF;   //!
   TBranch        *b_goodPatJets_Energy;   //!
   TBranch        *b_goodPatJets_EnergyRaw;   //!
   TBranch        *b_goodPatJets_Eta;   //!
   TBranch        *b_goodPatJets_HADF;   //!
   TBranch        *b_goodPatJets_JECUnc;   //!
   TBranch        *b_goodPatJets_JetBProbabilityBTag;   //!
   TBranch        *b_goodPatJets_JetProbabilityBTag;   //!
   TBranch        *b_goodPatJets_L1OffJEC;   //!
   TBranch        *b_goodPatJets_L2L3ResJEC;   //!
   TBranch        *b_goodPatJets_L2RelJEC;   //!
   TBranch        *b_goodPatJets_L3AbsJEC;   //!
   TBranch        *b_goodPatJets_Mass;   //!
   TBranch        *b_goodPatJets_Phi;   //!
   TBranch        *b_goodPatJets_Pt;   //!
   TBranch        *b_goodPatJets_PtRaw;   //!
   TBranch        *b_goodPatJets_Px;   //!
   TBranch        *b_goodPatJets_Py;   //!
   TBranch        *b_goodPatJets_Pz;   //!
   TBranch        *b_goodPatJets_SigmaEta;   //!
   TBranch        *b_goodPatJets_SigmaPhi;   //!
   TBranch        *b_goodPatJets_SimpleSecondaryVertexHighEffBTag;   //!
   TBranch        *b_goodPatJets_SimpleSecondaryVertexHighPurBTag;   //!
   TBranch        *b_goodPatJets_SoftElectronBJetTag;   //!
   TBranch        *b_goodPatJets_SoftMuonBJetTag;   //!
   TBranch        *b_goodPatJets_SoftMuonNoIPBJetTag;   //!
   TBranch        *b_goodPatJets_TrackCountingHighEffBTag;   //!
   TBranch        *b_goodPatJets_TrackCountingHighPurBTag;   //!
   TBranch        *b_goodPatJets_fHPD;   //!
   TBranch        *b_goodPatJets_fRBX;   //!
   TBranch        *b_goodPatJets_resEMF;   //!
   TBranch        *b_patMETs_ET;   //!
   TBranch        *b_patMETs_ETUncorr;   //!
   TBranch        *b_patMETs_Ex;   //!
   TBranch        *b_patMETs_Ey;   //!
   TBranch        *b_patMETs_Phi;   //!
   TBranch        *b_patMETs_PhiUncorr;   //!
   TBranch        *b_patMETs_Significance;   //!
   TBranch        *b_patMETs_SumET;   //!
   TBranch        *b_patMETs_SumETUncorr;   //!
   TBranch        *b_selectedPatElectrons_CaloEnergy;   //!
   TBranch        *b_selectedPatElectrons_DCotTheta;   //!
   TBranch        *b_selectedPatElectrons_DeltaEtaTrkSC;   //!
   TBranch        *b_selectedPatElectrons_DeltaPhiTrkSC;   //!
   TBranch        *b_selectedPatElectrons_Dist;   //!
   TBranch        *b_selectedPatElectrons_EcalIso;   //!
   TBranch        *b_selectedPatElectrons_EcalIso03;   //!
   TBranch        *b_selectedPatElectrons_EcalIsoHeep;   //!
   TBranch        *b_selectedPatElectrons_Energy;   //!
   TBranch        *b_selectedPatElectrons_EoverP;   //!
   TBranch        *b_selectedPatElectrons_Eta;   //!
   TBranch        *b_selectedPatElectrons_GSFTrack_Eta;   //!
   TBranch        *b_selectedPatElectrons_GSFTrack_Phi;   //!
   TBranch        *b_selectedPatElectrons_GSFTrack_Pt;   //!
   TBranch        *b_selectedPatElectrons_GSFTrack_Theta;   //!
   TBranch        *b_selectedPatElectrons_GSFTrack_d0;   //!
   TBranch        *b_selectedPatElectrons_HcalIso;   //!
   TBranch        *b_selectedPatElectrons_HcalIso03;   //!
   TBranch        *b_selectedPatElectrons_HcalIsoD1Heep;   //!
   TBranch        *b_selectedPatElectrons_HcalIsoD2Heep;   //!
   TBranch        *b_selectedPatElectrons_HoE;   //!
   TBranch        *b_selectedPatElectrons_Phi;   //!
   TBranch        *b_selectedPatElectrons_Pt;   //!
   TBranch        *b_selectedPatElectrons_Px;   //!
   TBranch        *b_selectedPatElectrons_Py;   //!
   TBranch        *b_selectedPatElectrons_Pz;   //!
   TBranch        *b_selectedPatElectrons_SCEta;   //!
   TBranch        *b_selectedPatElectrons_SCPhi;   //!
   TBranch        *b_selectedPatElectrons_SCPt;   //!
   TBranch        *b_selectedPatElectrons_SCRawEnergy;   //!
   TBranch        *b_selectedPatElectrons_SigmaEtaEta;   //!
   TBranch        *b_selectedPatElectrons_SigmaIEtaIEta;   //!
   TBranch        *b_selectedPatElectrons_TrkIso;   //!
   TBranch        *b_selectedPatElectrons_TrkIso03;   //!
   TBranch        *b_selectedPatElectrons_TrkIsoHeep;   //!
   TBranch        *b_selectedPatElectrons_Vertex_X;   //!
   TBranch        *b_selectedPatElectrons_Vertex_Y;   //!
   TBranch        *b_selectedPatElectrons_Vertex_Z;   //!
   TBranch        *b_selectedPatElectrons_VtxDistXY;   //!
   TBranch        *b_selectedPatElectrons_VtxDistZ;   //!
   TBranch        *b_selectedPatElectrons_dB;   //!
   TBranch        *b_selectedPatElectrons_eSeedClusterOverPout;   //!
   TBranch        *b_selectedPatElectrons_fbrem;   //!
   TBranch        *b_selectedPatElectrons_shFracInnerHits;   //!
   TBranch        *b_Event_PDFWeights;   //!
   TBranch        *b_GenJet_Charge;   //!
   TBranch        *b_GenJet_EMF;   //!
   TBranch        *b_GenJet_Energy;   //!
   TBranch        *b_GenJet_Eta;   //!
   TBranch        *b_GenJet_HADF;   //!
   TBranch        *b_GenJet_Mass;   //!
   TBranch        *b_GenJet_Phi;   //!
   TBranch        *b_GenJet_Pt;   //!
   TBranch        *b_GenJet_Px;   //!
   TBranch        *b_GenJet_Py;   //!
   TBranch        *b_GenJet_Pz;   //!
   TBranch        *b_GenMETExTrue;   //!
   TBranch        *b_GenMETEyTrue;   //!
   TBranch        *b_GenParticle_Energy;   //!
   TBranch        *b_GenParticle_Eta;   //!
   TBranch        *b_GenParticle_Phi;   //!
   TBranch        *b_GenParticle_Pt;   //!
   TBranch        *b_GenParticle_Px;   //!
   TBranch        *b_GenParticle_Py;   //!
   TBranch        *b_GenParticle_Pz;   //!
   TBranch        *b_GenParticle_VX;   //!
   TBranch        *b_GenParticle_VY;   //!
   TBranch        *b_GenParticle_VZ;   //!
   TBranch        *b_goodPatJetsPFlow_BestVertexTrackAssociationFactor;   //!
   TBranch        *b_goodPatJetsPFlow_Charge;   //!
   TBranch        *b_goodPatJetsPFlow_ChargedEmEnergyFraction;   //!
   TBranch        *b_goodPatJetsPFlow_ChargedEmEnergyFractionRAW;   //!
   TBranch        *b_goodPatJetsPFlow_ChargedHadronEnergyFraction;   //!
   TBranch        *b_goodPatJetsPFlow_ChargedHadronEnergyFractionRAW;   //!
   TBranch        *b_goodPatJetsPFlow_ChargedMuEnergyFraction;   //!
   TBranch        *b_goodPatJetsPFlow_ClosestVertexWeighted3DSeparation;   //!
   TBranch        *b_goodPatJetsPFlow_ClosestVertexWeightedXYSeparation;   //!
   TBranch        *b_goodPatJetsPFlow_ClosestVertexWeightedZSeparation;   //!
   TBranch        *b_goodPatJetsPFlow_ElectronEnergyFraction;   //!
   TBranch        *b_goodPatJetsPFlow_Energy;   //!
   TBranch        *b_goodPatJetsPFlow_EnergyRaw;   //!
   TBranch        *b_goodPatJetsPFlow_Eta;   //!
   TBranch        *b_goodPatJetsPFlow_JECUnc;   //!
   TBranch        *b_goodPatJetsPFlow_JetBProbabilityBTag;   //!
   TBranch        *b_goodPatJetsPFlow_JetProbabilityBTag;   //!
   TBranch        *b_goodPatJetsPFlow_L1OffJEC;   //!
   TBranch        *b_goodPatJetsPFlow_L2L3ResJEC;   //!
   TBranch        *b_goodPatJetsPFlow_L2RelJEC;   //!
   TBranch        *b_goodPatJetsPFlow_L3AbsJEC;   //!
   TBranch        *b_goodPatJetsPFlow_Mass;   //!
   TBranch        *b_goodPatJetsPFlow_MuonEnergyFraction;   //!
   TBranch        *b_goodPatJetsPFlow_NeutralEmEnergyFraction;   //!
   TBranch        *b_goodPatJetsPFlow_NeutralEmEnergyFractionRAW;   //!
   TBranch        *b_goodPatJetsPFlow_NeutralHadronEnergyFraction;   //!
   TBranch        *b_goodPatJetsPFlow_NeutralHadronEnergyFractionRAW;   //!
   TBranch        *b_goodPatJetsPFlow_Phi;   //!
   TBranch        *b_goodPatJetsPFlow_PhotonEnergyFraction;   //!
   TBranch        *b_goodPatJetsPFlow_Pt;   //!
   TBranch        *b_goodPatJetsPFlow_PtRaw;   //!
   TBranch        *b_goodPatJetsPFlow_Px;   //!
   TBranch        *b_goodPatJetsPFlow_Py;   //!
   TBranch        *b_goodPatJetsPFlow_Pz;   //!
   TBranch        *b_goodPatJetsPFlow_SimpleSecondaryVertexHighEffBTag;   //!
   TBranch        *b_goodPatJetsPFlow_SimpleSecondaryVertexHighPurBTag;   //!
   TBranch        *b_goodPatJetsPFlow_TrackCountingHighEffBTag;   //!
   TBranch        *b_goodPatJetsPFlow_TrackCountingHighPurBTag;   //!
   TBranch        *b_selectedPatElectronsLoosePFlow_CaloEnergy;   //!
   TBranch        *b_selectedPatElectronsLoosePFlow_DCotTheta;   //!
   TBranch        *b_selectedPatElectronsLoosePFlow_DeltaEtaTrkSC;   //!
   TBranch        *b_selectedPatElectronsLoosePFlow_DeltaPhiTrkSC;   //!
   TBranch        *b_selectedPatElectronsLoosePFlow_Dist;   //!
   TBranch        *b_selectedPatElectronsLoosePFlow_EcalIso;   //!
   TBranch        *b_selectedPatElectronsLoosePFlow_EcalIso03;   //!
   TBranch        *b_selectedPatElectronsLoosePFlow_EcalIsoHeep;   //!
   TBranch        *b_selectedPatElectronsLoosePFlow_Energy;   //!
   TBranch        *b_selectedPatElectronsLoosePFlow_EoverP;   //!
   TBranch        *b_selectedPatElectronsLoosePFlow_Eta;   //!
   TBranch        *b_selectedPatElectronsLoosePFlow_GSFTrack_Eta;   //!
   TBranch        *b_selectedPatElectronsLoosePFlow_GSFTrack_Phi;   //!
   TBranch        *b_selectedPatElectronsLoosePFlow_GSFTrack_Pt;   //!
   TBranch        *b_selectedPatElectronsLoosePFlow_GSFTrack_Theta;   //!
   TBranch        *b_selectedPatElectronsLoosePFlow_GSFTrack_d0;   //!
   TBranch        *b_selectedPatElectronsLoosePFlow_HcalIso;   //!
   TBranch        *b_selectedPatElectronsLoosePFlow_HcalIso03;   //!
   TBranch        *b_selectedPatElectronsLoosePFlow_HcalIsoD1Heep;   //!
   TBranch        *b_selectedPatElectronsLoosePFlow_HcalIsoD2Heep;   //!
   TBranch        *b_selectedPatElectronsLoosePFlow_HoE;   //!
   TBranch        *b_selectedPatElectronsLoosePFlow_PFGammaIso;   //!
   TBranch        *b_selectedPatElectronsLoosePFlow_PfChargedHadronIso;   //!
   TBranch        *b_selectedPatElectronsLoosePFlow_PfNeutralHadronIso;   //!
   TBranch        *b_selectedPatElectronsLoosePFlow_Phi;   //!
   TBranch        *b_selectedPatElectronsLoosePFlow_Pt;   //!
   TBranch        *b_selectedPatElectronsLoosePFlow_Px;   //!
   TBranch        *b_selectedPatElectronsLoosePFlow_Py;   //!
   TBranch        *b_selectedPatElectronsLoosePFlow_Pz;   //!
   TBranch        *b_selectedPatElectronsLoosePFlow_SCEta;   //!
   TBranch        *b_selectedPatElectronsLoosePFlow_SCPhi;   //!
   TBranch        *b_selectedPatElectronsLoosePFlow_SCPt;   //!
   TBranch        *b_selectedPatElectronsLoosePFlow_SCRawEnergy;   //!
   TBranch        *b_selectedPatElectronsLoosePFlow_SigmaEtaEta;   //!
   TBranch        *b_selectedPatElectronsLoosePFlow_SigmaIEtaIEta;   //!
   TBranch        *b_selectedPatElectronsLoosePFlow_TrkIso;   //!
   TBranch        *b_selectedPatElectronsLoosePFlow_TrkIso03;   //!
   TBranch        *b_selectedPatElectronsLoosePFlow_TrkIsoHeep;   //!
   TBranch        *b_selectedPatElectronsLoosePFlow_Vertex_X;   //!
   TBranch        *b_selectedPatElectronsLoosePFlow_Vertex_Y;   //!
   TBranch        *b_selectedPatElectronsLoosePFlow_Vertex_Z;   //!
   TBranch        *b_selectedPatElectronsLoosePFlow_VtxDistXY;   //!
   TBranch        *b_selectedPatElectronsLoosePFlow_VtxDistZ;   //!
   TBranch        *b_selectedPatElectronsLoosePFlow_dB;   //!
   TBranch        *b_selectedPatElectronsLoosePFlow_eSeedClusterOverPout;   //!
   TBranch        *b_selectedPatElectronsLoosePFlow_fbrem;   //!
   TBranch        *b_selectedPatElectronsLoosePFlow_shFracInnerHits;   //!
   TBranch        *b_patMETsPFlow_ET;   //!
   TBranch        *b_patMETsPFlow_ETUncorr;   //!
   TBranch        *b_patMETsPFlow_Ex;   //!
   TBranch        *b_patMETsPFlow_Ey;   //!
   TBranch        *b_patMETsPFlow_Phi;   //!
   TBranch        *b_patMETsPFlow_PhiUncorr;   //!
   TBranch        *b_patMETsPFlow_Significance;   //!
   TBranch        *b_patMETsPFlow_SumET;   //!
   TBranch        *b_patMETsPFlow_SumETUncorr;   //!
   TBranch        *b_goodOfflinePrimaryVertices_Chi2;   //!
   TBranch        *b_goodOfflinePrimaryVertices_NDF;   //!
   TBranch        *b_goodOfflinePrimaryVertices_Rho;   //!
   TBranch        *b_goodOfflinePrimaryVertices_X;   //!
   TBranch        *b_goodOfflinePrimaryVertices_XErr;   //!
   TBranch        *b_goodOfflinePrimaryVertices_Y;   //!
   TBranch        *b_goodOfflinePrimaryVertices_YErr;   //!
   TBranch        *b_goodOfflinePrimaryVertices_Z;   //!
   TBranch        *b_goodOfflinePrimaryVertices_ZErr;   //!
   TBranch        *b_selectedPatMuons_Charge;   //!
   TBranch        *b_selectedPatMuons_CocktailCharge;   //!
   TBranch        *b_selectedPatMuons_CocktailTrkHits;   //!
   TBranch        *b_selectedPatMuons_TrkHits;   //!
   TBranch        *b_selectedPatMuons_VtxIndex;   //!
   TBranch        *b_selectedPatMuons_isGoodGlobalMuon;   //!
   TBranch        *b_selectedPatMuonsLoosePFlow_Charge;   //!
   TBranch        *b_selectedPatMuonsLoosePFlow_CocktailCharge;   //!
   TBranch        *b_selectedPatMuonsLoosePFlow_CocktailTrkHits;   //!
   TBranch        *b_selectedPatMuonsLoosePFlow_TrkHits;   //!
   TBranch        *b_selectedPatMuonsLoosePFlow_VtxIndex;   //!
   TBranch        *b_selectedPatMuonsLoosePFlow_isGoodGlobalMuon;   //!
   TBranch        *b_goodPatJetsCA8PF_BestVertexTrackAssociationIndex;   //!
   TBranch        *b_goodPatJetsCA8PF_ChargedHadronMultiplicity;   //!
   TBranch        *b_goodPatJetsCA8PF_ChargedMultiplicity;   //!
   TBranch        *b_goodPatJetsCA8PF_ClosestVertex3DIndex;   //!
   TBranch        *b_goodPatJetsCA8PF_ClosestVertexXYIndex;   //!
   TBranch        *b_goodPatJetsCA8PF_ClosestVertexZIndex;   //!
   TBranch        *b_goodPatJetsCA8PF_ElectronMultiplicity;   //!
   TBranch        *b_goodPatJetsCA8PF_MuonMultiplicity;   //!
   TBranch        *b_goodPatJetsCA8PF_NConstituents;   //!
   TBranch        *b_goodPatJetsCA8PF_NeutralHadronMultiplicity;   //!
   TBranch        *b_goodPatJetsCA8PF_NeutralMultiplicity;   //!
   TBranch        *b_goodPatJetsCA8PF_PartonFlavour;   //!
   TBranch        *b_goodPatJetsCA8PF_PassLooseID;   //!
   TBranch        *b_goodPatJetsCA8PF_PassTightID;   //!
   TBranch        *b_goodPatJetsCA8PF_PhotonMultiplicity;   //!
   TBranch        *b_goodPatJets_PartonFlavour;   //!
   TBranch        *b_goodPatJets_PassLooseID;   //!
   TBranch        *b_goodPatJets_PassTightID;   //!
   TBranch        *b_goodPatJets_n90Hits;   //!
   TBranch        *b_selectedPatElectrons_Charge;   //!
   TBranch        *b_selectedPatElectrons_GSFTrack_Charge;   //!
   TBranch        *b_selectedPatElectrons_MissingHits;   //!
   TBranch        *b_selectedPatElectrons_PassID;   //!
   TBranch        *b_selectedPatElectrons_VtxIndex;   //!
   TBranch        *b_selectedPatElectrons_closestCtfTrackRef;   //!
   TBranch        *b_Event_PileUpInteractions;   //!
   TBranch        *b_Event_PileUpOriginBX;   //!
   TBranch        *b_GenParticle_MotherIndex;   //!
   TBranch        *b_GenParticle_NumDaught;   //!
   TBranch        *b_GenParticle_PdgId;   //!
   TBranch        *b_GenParticle_Status;   //!
   TBranch        *b_goodPatJetsPFlow_BestVertexTrackAssociationIndex;   //!
   TBranch        *b_goodPatJetsPFlow_ChargedHadronMultiplicity;   //!
   TBranch        *b_goodPatJetsPFlow_ChargedMultiplicity;   //!
   TBranch        *b_goodPatJetsPFlow_ClosestVertex3DIndex;   //!
   TBranch        *b_goodPatJetsPFlow_ClosestVertexXYIndex;   //!
   TBranch        *b_goodPatJetsPFlow_ClosestVertexZIndex;   //!
   TBranch        *b_goodPatJetsPFlow_ElectronMultiplicity;   //!
   TBranch        *b_goodPatJetsPFlow_MuonMultiplicity;   //!
   TBranch        *b_goodPatJetsPFlow_NConstituents;   //!
   TBranch        *b_goodPatJetsPFlow_NeutralHadronMultiplicity;   //!
   TBranch        *b_goodPatJetsPFlow_NeutralMultiplicity;   //!
   TBranch        *b_goodPatJetsPFlow_PartonFlavour;   //!
   TBranch        *b_goodPatJetsPFlow_PassLooseID;   //!
   TBranch        *b_goodPatJetsPFlow_PassTightID;   //!
   TBranch        *b_goodPatJetsPFlow_PhotonMultiplicity;   //!
   TBranch        *b_selectedPatElectronsLoosePFlow_Charge;   //!
   TBranch        *b_selectedPatElectronsLoosePFlow_GSFTrack_Charge;   //!
   TBranch        *b_selectedPatElectronsLoosePFlow_MissingHits;   //!
   TBranch        *b_selectedPatElectronsLoosePFlow_PassID;   //!
   TBranch        *b_selectedPatElectronsLoosePFlow_VtxIndex;   //!
   TBranch        *b_selectedPatElectronsLoosePFlow_closestCtfTrackRef;   //!
   TBranch        *b_Trigger_HLTBits;   //!
   TBranch        *b_Trigger_HLTPrescales;   //!
   TBranch        *b_Trigger_HLTPrescalesOther;   //!
   TBranch        *b_Trigger_HLTResults;   //!
   TBranch        *b_Trigger_HLTResultsOther;   //!
   TBranch        *b_Trigger_L1PhysBits;   //!
   TBranch        *b_Trigger_L1TechBits;   //!
   TBranch        *b_goodOfflinePrimaryVertices_IsFake;   //!
   TBranch        *b_goodOfflinePrimaryVertices_NTracks;   //!
   TBranch        *b_goodOfflinePrimaryVertices_NTracksW05;   //!
   TBranch        *b_Event_Bunch;   //!
   TBranch        *b_Event_LumiSection;   //!
   TBranch        *b_Event_Number;   //!
   TBranch        *b_Event_Orbit;   //!
   TBranch        *b_Event_Run;   //!
   TBranch        *b_Event_ProcessID;   //!

   Variables(TTree * /*tree*/ =0) { }
   virtual ~Variables() { }
   virtual void    Init(TTree *tree);
   virtual Int_t   GetEntry(Long64_t entry, Int_t getall = 0) { return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }

//   ClassDef(Variables,0);
};

#endif
