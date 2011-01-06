from HistGetter import *

def fit_njet(function = "pol1", Fit_From = 0.1, hists):
    allMCSamples = ['ttbar', 'wjets', 'zjets','tW', 'tchan', 'qcd']
    mcStack = THStack("MC", "MC");
    [mcStack.Add(hists[sample]['QCDest_CombRelIso_4orMoreJets']) for sample in allMCSamples if hists.has_key(sample)]
    print "\nSwitched from chi2 fit to likelihood fit (better with low stats)\n"

    # Try: 0.1, 0.2
    print "-----------------------"
    print " FIT:  ",function,"   range ",Fit_From,"--1.6"
    print "-----------------------"

    lw = 2; #line width (function)


    c1 = TCanvas("c1", "RelIso fit", 600, 400);#,"",500,500);


    #  gStyle.SetOptStat(1110);#off title


    data.GetXaxis().SetRangeUser(0, 1.6 - 0.01);

    data.Draw();
#    if (firstTime):
#        YMAX_all = 2 * data.GetMaximum();
#        firstTime = False;

#    data.GetYaxis().SetRangeUser(0, YMAX_all);


    # draw mc
    mcStack.Draw("ahist same");
    data.Draw("ae same");
    data.Draw("axis same");

    print "Fit Range: ",Fit_From,"-1.6"

    #  TFitResultPtr myFitResult = data.Fit("pol1","0S","ah",Fit_From,1.6); # <----Fit Range
    #    const char *func = Form("%s", function);

    # Fit options used:
    #  L : likelihood method
    #  S : store fit results
    #  0 : do not draw
    myFitResult = data.Fit(function, "0SL", "ah", Fit_From, 1.6); # <----Fit Range
    print "func ",function
    # Fit line in red
    #  myf = data.GetFunction("pol1");
    myf = data.GetFunction(function);
    myf.SetLineColor(kRed);
    myf.SetLineWidth(lw);

    # Extrapolation in dashed blue
    myf2 =  myf.Clone(); #range 0-0.1
    myf2.SetLineColor(kBlue);
    myf2.SetLineStyle(kDashed);
    myf2.SetLineWidth(lw);
    myf2.SetRange(0, Fit_From);

    myf.Draw("same");
    myf2.Draw("same");

    # Get estimate from extrapolation
    n_extrap = myf2.Integral(0, 0.1) / 0.1; #note divided by bin width=0.1

    p0 = myf.GetParameter(0);
    p1 = myf.GetParameter(1);
    e0 = myf.GetParError(0);
    e1 = myf.GetParError(1);

    chi2 = myFitResult.Chi2();
    ndf = myFitResult.Ndf();

    print "------------"
    print "Fit results"
    print "------------"
    print "n extrap = ",n_extrap
    print "p0 = ",p0," +/- ",e0
    print "p1 = ",p1," +/- ",e1
    print "chi2/ndf =  ",chi2," / ",ndf

    # Constructfunctions to see how estimate varies within fit parameter
    # uncertainties, ie error of p0 and p1

    # vary p0 (normalization)
    newF1_up =TF1(function, function, 0, 1.6);
    newF1_up.SetParameters(p0 + e0, p1);
    newF1_up.SetLineColor(kGreen);
    newF1_up.SetLineWidth(lw);

    newF1_down =TF1(function, function, 0, 1.6);
    newF1_down.SetParameters(p0 - e0, p1);
    newF1_down.SetLineColor(kGreen);
    newF1_down.SetLineWidth(lw);


    # Get theestimates
    est_1 = newF1_up.Integral(0, 0.1) / 0.1;
    est_2 = newF1_down.Integral(0, 0.1) / 0.1;
    print "n extrap (p0 + e0,   p1     ) = ",est_1
    print "n extrap (p0 - e0,   p1     ) = ",est_2

    # take the maximum deviation as the uncertainty
    est_unc = 0;
    if (fabs(est_1 - n_extrap) > est_unc):
        est_unc = fabs(est_1 - n_extrap);
    if (fabs(est_2 - n_extrap) > est_unc):
        est_unc = fabs(est_2 - n_extrap);
    #if( fabs(est_3 - n_extrap) > est_unc ) est_unc = fabs(est_3 - n_extrap);
    #if( fabs(est_4 - n_extrap) > est_unc ) est_unc = fabs(est_4 - n_extrap);

    print "Take the maximum deviation as the uncertainty of the QCD estimate."
    print "--------------------------------------------"
    print "  RESULT: ",function," ",Fit_From,"-1.6"
    print "--------------------------------------------"
    # prout MC prediction for QCD + photon+jets
    if (normMode == 1):
        print "\n  QCD predicted =  ",QCD.Integral(0, 1)," (Lumi)"
        TheEstimates,"\n  QCD predicted =  ",QCD.Integral(0, 1)," (Lumi)"
    print "\n  QCD estimate  =  ",n_extrap,"  +/-  ",est_unc," (vary p0)"
    TheEstimates,"  QCD estimate  =  ",n_extrap,"  +/-  ",est_unc," (vary p0)"

    #----------------------
    # error propagation
    #----------------------
    N = 0;
    sigmaN = 0;

    if (function == "pol1"):
        c = p0;
        m = p1;

        eC = e0;
        eM = e1;

        N = 0.05 * m + c;
        sigmaN = TMath.Hypot(0.05 * eM, eC);

    elif (function == "expo"):
        a = p0;
        b = p1;
        eA = e0;
        eB = e1;

        x2 = 0.1;

        exp_ab = exp(a + 0.1 * b);
        exp_a = exp(a);

        N = 10 / b * (exp_ab - exp_a);

        # del(N)/del(a/b)
        dNda = 1 / (b * x2) * (exp_ab - exp_a);
        dNdb = -1 / (b * b * x2) * (exp_ab - exp_a) + 1 / b * exp_ab;

        # Note: sigma(N) = sqrt( dNda^2*eA^2 + dBdb^2*eB^2  )
        sigmaN = TMath.Hypot(dNda * eA, dNdb * eB);
    elif (function == "gaus"):
        p2 = myf.GetParameter(2);
        e2 = myf.GetParError(2);
        # Not finished. Calculated estimate is wrong.
        print "\n-. Error propagation for Gaussian not yet implemented!"
        #calculate_gaus_unc(p0,p1,p2);

    print "\n  QCD estimate  =  ",N;
    print "  +/-  ",sigmaN," (error propagation)\n\n";
    print "--------------------------------------------"

    # Add "CMS Preliminary", integrated luminosity and sqrt(s), and legend
#    add_cms_label(intlumi, nj);
    #  add_fit_res( Fit_From, chi2, ndf );
#    add_legend(function);

    # save as eps, then convert to pdf
    print "Fit_From=",Fit_From
    out = ''
    if (function == "pol1"):
        out ="ele_reliso_fit_%s_linear_from_0%.0f" %(nj, Fit_From * 10.0);
    else:
        out = "ele_reliso_fit_%s_%s_from_0%.0f" % (function, nj, Fit_From * 10.0);

    if (normMode == 1):
        out += "_normToLumi";
    else:
        out += "_normToData";

    print "out: ",out
    c1.SaveAs(Form("%s.C", out)); #save as C++ root macro
    c1.SaveAs(Form("%s.eps", out));
    gROOT.ProcessLine(Form(".!ps2pdf -dEPSCrop %s.eps", out));
    gROOT.ProcessLine(Form(".!rm -f %s.eps", out));

    c1.Close(); #crucial!