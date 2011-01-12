from __future__ import division

from HistGetter import *
from tdrStyle import *
from ROOT import *
from math import pow, exp

class QCDEstimator:
    luminosity = 36.145#pb-1
    mc_luminosity = 36.145#pb-1
    luminosity_unit = 'pb-1'
    scale = luminosity / mc_luminosity
    jetBins = ['0jet', 'allJets', '1jet', '1orMoreJets', '2jets', '2orMoreJets', '3jets', '3orMoreJets', '4orMoreJets']
    jetBinsLatex = {'0jet':'0 jet', 'allJets':'#geq 0 jets', '1jet':'1 jet', '1orMoreJets':'#geq 1 jet',
                    '2jets':'2 jets', '#geq 2 jets':'', '3jets':'3 jets', '3orMoreJets':'#geq 3 jets',
                    '4orMoreJets':'#geq 4 jets'}
    binWidth = 0.01
    rebin = 10
    fitRanges = [ ( 0.1, 1.0 ), ( 0.1, 1.2 ), ( 0.1, 1.4 ),
                  ( 0.2, 1.1 ), ( 0.2, 1.3 ), ( 0.2, 1.5 ),
                  ( 0.3, 1.2 ), ( 0.3, 1.4 ), ( 0.3, 1.6 )]

    signalRegion = ( 0, 0.1 )
    pfIsoHistogramPrefix = 'QCDest_PFIsolation_'
    relIsoHistogramPrefix = 'QCDest_CombRelIso_'
    pfIsoResults = {}
    relIsoResults = {}

    useEntryAsData = 'data'
    constrainFit = False
    numberOfFreeParameters = 0

    def __init__( self, files ):
        self.files = files
        HistGetter.samplefiles = files
        self.histograms = {}
        self.histGetter = HistGetter()
        self.histGetter.setStyle()
        self.getHistograms()
        self.applyStyleAndCreateStack()

        for bin in self.jetBins:
            self.pfIsoResults[bin] = {'actualNumberOfQCDEvents': 0, 'estimatedNumberOfQCDEvents':0,
                                      'fitFunction': None, 'fitParameters': {}}
            self.relIsoResults[bin] = {'actualNumberOfQCDEvents': 0, 'estimatedNumberOfQCDEvents':0,
                                       'fitFunction': None, 'fitParameters': {}}

    def getHistograms( self ):
        relIsoHists = ['QCDest_CombRelIso_' + jetbin for jetbin in self.jetBins]
        pfIsoHists = ['QCDest_PFIsolation_' + jetbin for jetbin in self.jetBins]
        allHists = relIsoHists
        allHists.extend( pfIsoHists )
        HistGetter.hists = allHists

        self.histograms = self.histGetter.getHistsFromFiles()
        self.histograms = self.histGetter.addSampleSum( self.histograms )

    def applyStyleAndCreateStack( self ):
        samplesOfInterest = ['data', 'qcd', 'zjets', 'wjets', 'singleTop', 'ttbar']
        colors = {'ttbar' :  kRed + 1,
                  'wjets' :  kGreen - 3,
                  'zjets' :  kAzure - 2,
                  'qcd' :  kYellow,
                  'singleTop' :  kMagenta}

        mcStack = {}

        for sample in samplesOfInterest:#sample
            for histname in self.histograms[sample].keys():
                self.histograms[sample][histname].Rebin( self.rebin )
                if not sample == 'data':
                    self.histograms[sample][histname].Scale( self.scale )
                    self.histograms[sample][histname].SetFillStyle( 1001 )
                    self.histograms[sample][histname].SetFillColor( colors[sample] )
                    if not mcStack.has_key( histname ):
                        mcStack[histname] = THStack( "MC_" + histname, "MC_" + histname );
                    mcStack[histname].Add( self.histograms[sample][histname] )
                else:
                    self.histograms[sample][histname].SetMarkerStyle( 8 );


        self.histograms['MCStack'] = mcStack
        self.setStyle()
        print "=" * 40
        print "data integrated luminosity:", self.luminosity, self.luminosity_unit
        print "MC integrated luminosity:", self.mc_luminosity, self.luminosity_unit
        print "MC scale factor: ", self.scale
        print "=" * 40


    def setStyle( self ):
        tdrstyle = setTDRStyle();
        tdrstyle.SetPadRightMargin( 0.05 )#originally was 0.02, too narrow!
        tdrStyle.SetStatH( 0.2 );
        tdrStyle.SetOptStat( 0 );#off title
        tdrStyle.SetOptFit( 0 );#off title
        tdrStyle.cd();
        gROOT.ForceStyle();
        gStyle.SetTitleH( 0.1 );
        gStyle.SetStatH( 0.22 ); #0.24);
        gStyle.SetStatW( 0.22 ); #0.26);
        gStyle.SetOptStat( 1 ); #on stat
        gStyle.SetLineScalePS( 2 ); #D=3
        gStyle.SetOptFit( 112 );


    def doClosureTests( self ):
        self.useEntryAsData = 'allMC'
        pass

    def doEstimate( self, function = 'gaus', limits = ( 0.1, 1.6 ) ):
        self.useEntryAsData = 'data'

        for bin in self.jetBins:
            self.EstimateJetBin( bin, function, limits )


    def EstimateJetBin( self, jetbin, function = 'gaus', limits = ( 0.1, 1.6 ) ):
        QCD = self.histograms['qcd']
        pfIsoHist = self.pfIsoHistogramPrefix + jetbin
        relIsoHist = self.relIsoHistogramPrefix + jetbin

        self.pfIsoResults[jetbin]['actualNumberOfQCDEvents'] = QCD[pfIsoHist].GetBinContent( 1 )
        pfIsoFit = self.doFit( self.histograms[self.useEntryAsData][pfIsoHist], function, limits )
        self.pfIsoResults[jetbin]['fitFunction'] = pfIsoFit
        self.pfIsoResults[jetbin]['fitParameters'] = self.getFitParameters( pfIsoFit )
        estimate = pfIsoFit.Integral( self.signalRegion[0], self.signalRegion[1] ) / ( self.binWidth * self.rebin )
        self.pfIsoResults[jetbin]['estimatedNumberOfQCDEvents'] = estimate

        self.relIsoResults[jetbin]['actualNumberOfQCDEvents'] = QCD[relIsoHist].GetBinContent( 1 )
        relIsoFit = self.doFit( self.histograms[self.useEntryAsData][relIsoHist], function, limits )
        self.relIsoResults[jetbin]['fitFunction'] = relIsoFit
        self.relIsoResults[jetbin]['fitParameters'] = self.getFitParameters( relIsoFit )

        estimate = relIsoFit.Integral( self.signalRegion[0], self.signalRegion[1] ) / ( self.binWidth * self.rebin )
        self.relIsoResults[jetbin]['estimatedNumberOfQCDEvents'] = estimate


    def doFit( self, histogram, function = 'gaus', limits = ( 0.1, 1.6 ) ):
        histogram.Fit( function, "Q0", "ah", limits[0], limits[1] )

        if self.constrainFit:
             ff = TF1( function, function, 0, 1 );
             self.numberOfFreeParameters = ff.GetNumberFreeParameters();

        return histogram.GetFunction( function )

    def getFitParameters( self, fitFunction ):
        fitParameters = {'chi2':-1, 'numberOfdegreesOfFreedom': 0, 'constrain1': 0, 'constrain2': 0, 'constrain3': 0,
                         'constrain4': 0}
        fitParameters['chi2'] = fitFunction.GetChisquare()
        fitParameters['numberOfdegreesOfFreedom'] = fitFunction.GetNDF()
        return fitParameters

    def doConstrainedFit( self, histogram, function = 'gaus', limits = ( 0.1, 1.6 ) ):
        fitFunction = None
        if function == 'gaus':
            fitFunction = TF1( "gaus", "gaus", 0, 2 );
        elif function == 'pol3':
            fitFunction = TF1( "pol3", "[0] * ( 1 + [1]*x + [2]*x^2 + [3]*x^3 )", 0, 2 );
        elif function == 'landau':
            fitFunction = TF1( "landau", "landau", 0, 2 )


        myFitResult = data.Fit( function, "Q0", "ah", limits[0], limits[1] );

    def add_cms_label( self, njet = "" ):

        mytext = TPaveText( 0.3, 0.8, 0.6, 0.93, "NDC" );
        mytext.AddText( "CMS Preliminary" );
        mytext.AddText( "%.1f pb^{-1} at  #sqrt{s} = 7 TeV" % self.luminosity );
        if njet != "":
            mytext.AddText( "e+jets, %s" % self.jetBinsLatex[njet] )
        mytext.SetFillStyle( 0 );
        mytext.SetBorderSize( 0 );
        mytext.SetTextFont( 42 );
        mytext.SetTextAlign( 13 );
        return mytext

    def producedZoomedHistogram( self, zoom ):
        pass

if __name__ == '__main__':
    path = '/storage/workspace/BristolAnalysisTools/outputfiles/Fall10_NovRereco_PfIso/'
    files = {'data': path + "data_36.145pb_PFElectron_PF2PATJets_PFMET.root",
    'ttbar' :  path + "ttjet_36.145pb_PFElectron_PF2PATJets_PFMET.root",
    'wjets' :  path + "wj_36.145pb_PFElectron_PF2PATJets_PFMET.root",
    'zjets' :  path + "zj_36.145pb_PFElectron_PF2PATJets_PFMET.root",
    'bce1' :  path + "bce1_36.145pb_PFElectron_PF2PATJets_PFMET.root",
    'bce2' :  path + "bce2_36.145pb_PFElectron_PF2PATJets_PFMET.root",
    'bce3' :  path + "bce3_36.145pb_PFElectron_PF2PATJets_PFMET.root",
    'enri1' : path + "enri1_36.145pb_PFElectron_PF2PATJets_PFMET.root",
    'enri2' :  path + "enri2_36.145pb_PFElectron_PF2PATJets_PFMET.root",
    'enri3' :  path + "enri3_36.145pb_PFElectron_PF2PATJets_PFMET.root",
    'pj1' :  path + "pj1_36.145pb_PFElectron_PF2PATJets_PFMET.root",
    'pj2' :  path + "pj2_36.145pb_PFElectron_PF2PATJets_PFMET.root",
    'pj3' :  path + "pj3_36.145pb_PFElectron_PF2PATJets_PFMET.root",
    'tW' :  path + "tW_36.145pb_PFElectron_PF2PATJets_PFMET.root",
    'tchan' :  path + "tchan_36.145pb_PFElectron_PF2PATJets_PFMET.root"}
    q = QCDEstimator( files )
    q.doEstimate()
    print q.pfIsoResults['4orMoreJets']['actualNumberOfQCDEvents']
    print q.pfIsoResults['4orMoreJets']['estimatedNumberOfQCDEvents']
    print
    print q.relIsoResults['4orMoreJets']['actualNumberOfQCDEvents']
    print q.relIsoResults['4orMoreJets']['estimatedNumberOfQCDEvents']
