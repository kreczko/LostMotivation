//
// 15 Jul 2010
//
// * Perform fit to RelIso distribution to estimate QCD in various jet bins.
// * Different fitting procedures are employed:
//   (a) free functional fits in all jet bins
//   (b) free fit in 1,2j, but constrained fits in 3,4mj, using 
//       fitted results from 1,2j.
//   (c) plot RelIso without fitting.
//
// * Configurable options:
//   (a) fit function: pol3, gaus
//   (b) fit range
//   (c) whether to zoom in on y-axis or not
//
// * Each fit produces one such multi-pad plot:
//    ----------------
//    |  allj |  0j  |
//    ----------------
//    |   1j  |  2j  |
//    ----------------
//    |   3j  |  4mj |
//    ----------------
//
// Tips/reminder:
//   - To use only MC, use run_mc.sh
//   - To fit data, use run_data.sh
//   - Every time new data is used, the integrated luminosity needs to be updated (intlumi).
//
// Things to look out for:
//  - Because data is plotted first, sometimes the MC histograms are
//    cut off in the y-scale. To cure this, set explicitly the upper limit on y
//    using the YMAX_nj (n=all,1,2 etc) global variables.
// 
// If code crashes, turn on the (global) 'debug' flag and re-run, but hopefully you won't need this!
//
//----------------------------------------------------
//-------------

bool limit_gaus_mean_12j = false;
double gaus_mean_min = 0.3;
const double gaus_mean_max = 0.6;

const int nj = 6;


//--------------------------------
// to customize y-axis max range
// if set to -1, it means do not set
//--------------------------------
double YMAX_allj = -1;
double YMAX_0j = -1;
double YMAX_1j = -1;
double YMAX_2j = -1; //20;
double YMAX_3j = -1;
double YMAX_4mj = -1;

//--------------------------------

const double sig_from = 0; //new reliso
const double sig_upto = 0.1;
const double control_max = 1.6;
double fit_from;
double fit_upto;

double this_bw;

double nqcd_actual_sig[nj];
double n_extrap[nj];
double fit_chi2[nj];
int fit_ndf[nj];

string do_fit;

int nFreePara;
double fit_par0[nj];
double fit_par1[nj];
double fit_par2[nj];
double fit_par3[nj];

// get integral of nEntries from 0-1.6
const double control_max = 1.6;
double n_cand_data_observed[nj];
double n_cand_mc_predicted[nj];


int fit(string do_fit_user = "fix", string func_user = "gaus", double fit_from_user = 0.2, double fit_upto_user = 1.4,
        bool zoom_in = true) {

    double bw = 0.1;
    int rb = bw / 0.01;

    string func = func_user;

    do_fit = do_fit_user;

    fit_from = fit_from_user; //0.3;  // <------
    fit_upto = fit_upto_user; //1.0;  // <------

    if (do_fit == "none")
        gStyle->SetOptStat(0);//off stat


    if (do_fit == "fix") {
        TF1 ff(func.c_str(), func.c_str(), 0, 1);
        nFreePara = ff.GetNumberFreeParameters();
    }

    TCanvas *c1 = new TCanvas("c1", "c1", 980, 1050);//980,700

    c1->Divide(2, 2);

    char *njet[6] = { "allj", "0j", "1j", "2j", "3j", "4mj" };
    char *njlabel[6] = { "#geq0 jets", "0 jet", "1 jet", "2 jets", "3 jets", "#geq4 jets" };

    int npad = 1;

    for (int j = 2; j < 6; j++) {

        const double binw = 0.01; //original binw = 0.01 = 1.1/110 (old) = 10/1000 (new)

        const int sig_bin_low = (int) (sig_from / binw + 1);
        const int sig_bin_up = (int) (sig_upto / binw);
        const int control_bin_max = (int) (control_max / binw);

        nqcd_actual_sig[j] = -1;
        if (draw_mc) {
            nqcd_actual_sig[j] = qcd->Integral(sig_bin_low, sig_bin_up); //actual number of _QCD_ event in signal region

        }

        // get number of candidates
        cout << "control_bin_max: " << control_bin_max << endl;
        if (draw_mc)
            n_cand_mc_predicted[j] = mc_all->Integral(1, control_bin_max);
        n_cand_data_observed[j] = all->Integral(1, control_bin_max);

        this_bw = binw * rebin[j];


        all->GetXaxis()->SetRangeUser(0, 1.6 - 0.01);
        if (draw_mc) {
            qcd->GetXaxis()->SetRangeUser(0, 1.6 - 0.01);
            qcd->SetLineColor(kAzure + 2);
            qcd->SetFillColor(kAzure - 9);
        }

        all->SetMarkerStyle(20);
        all->SetMarkerSize(0.6); //if run in batch mode

        all->SetLineColor(kRed);
        all->SetTitle(Form("%s", njlabel[j]));
        all->SetXTitle("RelIso");

        all->SetName(Form("%s (%.1f-%.1f)", func.c_str(), fit_from, fit_upto));

        all->SetLineColor(kBlack);

        c1->cd(npad);
        npad++;

        gStyle->SetOptFit(112);

        // To zoom in on y-axis
        if (zoom_in) {

            // find tallest bin from 3rd to 9th (0.2-1.0)
            double highest = 0;
            unsigned int scanfrom = all->FindBin(0.2);
            unsigned int scanto = all->FindBin(1.0) - 1;//do not count bin 1.0
            for (short i = scanfrom; i < scanto; i++) {
                double bin_height = all->GetBinContent(i);
                if (bin_height > highest)
                    highest = bin_height;
            }
            all->GetYaxis()->SetRangeUser(0, highest * 2.3);

        } else {

            // customize unzoom plot
            if (njet[j] == "allj" && YMAX_allj > 0)
                all->GetYaxis()->SetRangeUser(0, YMAX_allj);
            if (njet[j] == "0j" && YMAX_0j > 0)
                all->GetYaxis()->SetRangeUser(0, YMAX_0j);
            if (njet[j] == "1j" && YMAX_1j > 0)
                all->GetYaxis()->SetRangeUser(0, YMAX_1j);
            if (njet[j] == "2j" && YMAX_2j > 0)
                all->GetYaxis()->SetRangeUser(0, YMAX_2j);
            if (njet[j] == "3j" && YMAX_3j > 0)
                all->GetYaxis()->SetRangeUser(0, YMAX_3j);
            if (njet[j] == "4mj" && YMAX_4mj > 0)
                all->GetYaxis()->SetRangeUser(0, YMAX_4mj);
        }


        gPad->SetBottomMargin(0.14); //TEST


        all->GetXaxis()->SetTitleOffset(0.8); //on stat


        all->GetXaxis()->SetTitleSize(0.07);

        all->Draw("ae");
        if (draw_mc) {
            qcdcomp->Draw("ahist same"); //add
        }
        all->Draw("ae same");
        all->Draw("axis same");


        gPad->Update();


        TPaveStats *s1 = (TPaveStats*) all->GetListOfFunctions()->FindObject("stats");
        if (s1 > 0) {
            double sp[4] = { 0.35, 0.55, 0.7, 0.99 };
            s1->SetX1NDC(sp[0]);
            s1->SetY1NDC(sp[1]);
            s1->SetX2NDC(sp[2]);
            s1->SetY2NDC(sp[3]);
        }

        if (do_fit == "none") {
            continue;
        }

        //--------------------
        //  Perform the Fit
        //--------------------


        if (do_fit == "free") {

            //----------
            // Free Fit
            //----------

            //1st opt: "V": verbose, "Q": Quiet, "0": do not draw
            all->Fit(func.c_str(), "Q0", "ah", fit_from, fit_upto);



            getFitRes(j, gPad, func, all);

        } else if (do_fit == "fix") {

            //-------------------
            //  Constrained Fit
            //-------------------
            if (debug)
                cout << "constrained fit" << endl;

            TF1 *fitf;
            if (func == "gaus") {
                fitf = new TF1("gaus", "gaus", 0, 2);
            } else if (func == "pol3") {
                // pol3 = A + Bx + Cx^2+ Dx^3 = a(1 + b x + c x2 + d x3)
                //
                fitf = new TF1("pol3", "[0] * ( 1 + [1]*x + [2]*x^2 + [3]*x^3 )", 0, 2);
            } else if (func == "landau") {
                fitf = new TF1("landau", "landau", 0, 2);
            }

            // (a) free-fit in 1,2 jet bins
            //
            // For gaussian, require mean to be whithin 0.2-0.6, the flat or peak region.
            //
            //if( j<2 ) { //1,2j - Free Fit OR gaus-mean-constrained //this doesn't work now that 0mj and 0j were added
            if (j < 4) { //1,2j - Free Fit OR gaus-mean-constrained

                if (func == "gaus" && limit_gaus_mean_12j && j > 1 && j < 4) {//j=2,3 being 1jet or 2jets

                    cout << "constraining gaus mean in12j to " << gaus_mean_min << "-" << gaus_mean_max << endl;
                    fitf->SetParLimits(1, gaus_mean_min, gaus_mean_max); //mean of gaus (1j)

                }

                // 1st opt: "V"=verbose; "Q"=quite
                all->Fit(fitf, "Q0", "ah", fit_from, fit_upto); //Free Fit (Q)

            } else { //3,4mj - Constrained Fit

                string fopt;
                if (func == "gaus") {
                    fitf->FixParameter(1, (fit_par1[0] + fit_par1[1]) / 2); //mean or p1
                    fitf->FixParameter(2, (fit_par2[0] + fit_par2[1]) / 2); //sigma or p2
                    fopt = "BQ0";
                } else if (func == "pol3") {
                    // fix b,c,d
                    double avg_b = (fit_par1[0] + fit_par1[1]) / 2;
                    double avg_c = (fit_par2[0] + fit_par2[1]) / 2;
                    double avg_d = (fit_par3[0] + fit_par3[1]) / 2;

                    fitf->FixParameter(1, avg_b);
                    fitf->FixParameter(2, avg_c);
                    fitf->FixParameter(3, avg_d);
                    fopt = "BQ0";
                } else if (func == "landau") {
                    double mpv_min = min(fit_par1[0], fit_par1[1]);//mpv or p1
                    double mpv_max = max(fit_par1[0], fit_par1[1]);
                    cout << "mpv_min " << mpv_min << endl;
                    cout << "mpv_max " << mpv_max << endl;
                    fitf->SetParLimits(1, mpv_min, mpv_max);
                    fopt = "Q0"; //"B" gives wrong answer
                }

                // "B"=use fixed parameter value
                all->Fit(fitf, fopt.c_str(), "ah", fit_from, fit_upto);
            }
            delete fitf;

            if (debug)
                cout << "getFitRes 1" << endl;
            getFitRes(j, gPad, func, all);

        }

        if (debug)
            cout << "amtb go to next nj" << endl;

    }// njet loop

    if (debug)
        cout << "amtb: after nj loop" << endl;

    // Print
    printf("\nNumber of electron candidates with RelIso 0-1.6.\n");
    printf("              mc         data\n");
    printf(" allj   %10.2f   %10.2f\n", n_cand_mc_predicted[0], n_cand_data_observed[0]);
    printf("   0j   %10.2f   %10.2f\n", n_cand_mc_predicted[1], n_cand_data_observed[1]);
    printf("   1j   %10.2f   %10.2f\n", n_cand_mc_predicted[2], n_cand_data_observed[2]);
    printf("   2j   %10.2f   %10.2f\n", n_cand_mc_predicted[3], n_cand_data_observed[3]);
    printf("   3j   %10.2f   %10.2f\n", n_cand_mc_predicted[4], n_cand_data_observed[4]);
    printf(" >=4j   %10.2f   %10.2f\n", n_cand_mc_predicted[5], n_cand_data_observed[5]);

    cout << endl;

    // Legend
    //--------
    if (debug)
        cout << "amtb: creating legend" << endl;

    double coord[4] = { 0.7, 0.4, 0.9, 0.9 };

    TLegend *leg = new TLegend(coord[0], coord[1], coord[2], coord[3]);

    TF1 *blue = new TF1("blue", "pol0", 0, 1);
    TF1 *red = new TF1("red", "pol0", 0, 1);
    blue->SetLineColor(kBlue);
    red->SetLineColor(kRed);

    leg->SetFillColor(0);
    leg->SetBorderSize(0);

    if (!draw_data)
        leg->AddEntry(all, "All MC events", "LP"); //Line+Marker, E(error)
    else
        leg->AddEntry(all, "Data", "LP");
    if (draw_mc) {
        leg->AddEntry(tt, "t#bar{t}", "f");
        leg->AddEntry(stop, "Single-Top", "f");
        leg->AddEntry(wj, "W#rightarrowl#nu", "f");
        leg->AddEntry(zj, "Z#rightarrowl^{+}l^{-}", "f");
        leg->AddEntry(pj, "#gamma+jets", "f");
        leg->AddEntry(enri1, "EME pt 20-30", "f");
        leg->AddEntry(enri2, "EME pt 30-80", "f");
        leg->AddEntry(enri3, "EME pt 80-170", "f");
        //leg->AddEntry(bce1, "BCE pt 20-30", "f");
        leg->AddEntry(bce2, "BCE pt 30-80", "f");
        leg->AddEntry(bce3, "BCE pt 80-170", "f");
    }
    if (do_fit != "none") {
        leg->AddEntry(red, "Fit", "l");
        leg->AddEntry(blue, "Extrapolation", "l");
    }

    gStyle->SetOptStat(0);
    gStyle->SetOptFit(0);

    if (debug)
        cout << "amtb: draw legend" << endl;
    c1->cd(1);
    leg->Draw();
    add_cms_label();
    add_njet_label(1);
    c1->cd(2);
    leg->Draw();
    add_cms_label();
    add_njet_label(2);
    c1->cd(3);
    leg->Draw();
    add_cms_label();
    add_njet_label(3);
    c1->cd(4);
    leg->Draw();
    add_cms_label();
    add_njet_label(4);

    if (do_fit == "none") {

        if (debug)
            cout << "amtb: save plot" << endl;
        if (!zoom_in) {
            c1->SaveAs("QCD_reliso.gif");
            c1->SaveAs("QCD_reliso.eps");
            gROOT->ProcessLine(".!ps2pdf -dEPSCrop QCD_reliso.eps");
        } else {
            c1->SaveAs("QCD_reliso_zoom.gif");
            c1->SaveAs("QCD_reliso_zoom.eps");
            gROOT->ProcessLine(".!ps2pdf -dEPSCrop QCD_reliso_zoom.eps");
        }
        c1->Close();

        return 0;
    }

    if (debug)
        cout << "amtb: print fit results" << endl;

    //TDatime now;
    //now.Print();
    cout << "\n-----------------------------------------------" << endl;
    cout << "Fit " << func << " (range: " << fit_from << "-" << fit_upto << ")" << endl;
    cout << "-----------------------------------------------" << endl;
    cout << "  " << intlumi << "/pb     rb      True    Estimate     Diff" << endl;
    printf("allj jet:   %2d %10.1f  %10.1f  %6.1f %%\n", rebin[0], nqcd_actual_sig[0], n_extrap[0], (n_extrap[0]
            / nqcd_actual_sig[0] - 1) * 100);
    printf("   0 jet:   %2d %10.1f  %10.1f  %6.1f %%\n", rebin[1], nqcd_actual_sig[1], n_extrap[1], (n_extrap[1]
            / nqcd_actual_sig[1] - 1) * 100);
    printf("   1 jet:   %2d %10.1f  %10.1f  %6.1f %%\n", rebin[2], nqcd_actual_sig[2], n_extrap[2], (n_extrap[2]
            / nqcd_actual_sig[2] - 1) * 100);
    printf("   2 jet:   %2d %10.1f  %10.1f  %6.1f %%\n", rebin[3], nqcd_actual_sig[3], n_extrap[3], (n_extrap[3]
            / nqcd_actual_sig[3] - 1) * 100);
    printf("   3 jet:   %2d %10.1f  %10.1f  %6.1f %%\n", rebin[4], nqcd_actual_sig[4], n_extrap[4], (n_extrap[4]
            / nqcd_actual_sig[4] - 1) * 100);
    printf(" >=4 jet:   %2d %10.1f  %10.1f  %6.1f %%\n", rebin[5], nqcd_actual_sig[5], n_extrap[5], (n_extrap[5]
            / nqcd_actual_sig[5] - 1) * 100);
    cout << "-----------------------------------------------\n" << endl;

    if (debug)
        cout << "amtb: print constrained-fit results" << endl;

    if (do_fit == "fix") {

        cout << " Fitted parameter values" << endl;
        cout << "-----------------------------------------------" << endl;
        if (func == "gaus")
            cout << " Gaus         const        mean       sigma" << endl;
        else if (func == "landau")
            cout << " Landau       const        mpv        sigma" << endl;
        else
            cout << "           p0           p1          p2         p3" << endl;
        cout << "-----------------------------------------------" << endl;
        char *jjlabel[5] = { "0", "1", "2", "3", ">=4" };

        for (short i = 0; i < 5; ++i) {
            if (nFreePara == 3)
                printf(" %3s jet: %10.1f %10.2f %10.2f\n", jjlabel[i], fit_par0[i], fit_par1[i], fit_par2[i]);
            else if (nFreePara == 4)
                printf(" %3s jet: %10.1f %10.2f %10.2f %10.2f\n", jjlabel[i], fit_par0[i], fit_par1[i], fit_par2[i],
                        fit_par3[i]);
        }
        cout << "-----------------------------------------------" << endl;

    }

    if (debug)
        cout << "amtb: save picture" << endl;

    string out = Form("%s_r%.1fto%.1f", func.c_str(), fit_from, fit_upto);
    if (do_fit == "fix")
        out = Form("fixPara_%s_r%.1fto%.1f", func.c_str(), fit_from, fit_upto);

    if (!zoom_in) {
        c1->SaveAs(Form("fit_%s.gif", out));
        c1->SaveAs(Form("fit_%s.pdf", out));

    } else {
        c1->SaveAs(Form("fit_zoom_%s.gif", out));
        c1->SaveAs(Form("fit_zoom_%s.pdf", out));
    }
    c1->Close();


    if (debug)
        cout << "amtb: write result to text file" << endl;

    ofstream myfile;

    string outText;
    outText = "est_";
    if (zoom_in)
        outText += "zoom_";
    outText = outText + do_fit + "_" + func; //place where "est_free_gaus.txt" is made

    if (debug)
        cout << "amtb: " << outText << endl;

    myfile.open(Form("%s.txt", outText.c_str()), ios::app);

    myfile.setf(ios::fixed, ios::floatfield);
    myfile << endl;
    for (int k = 2; k < 6; ++k) {
        myfile << n_extrap[k] / nqcd_actual_sig[k] - 1 << endl;
    }

    if (debug)
        cout << "amtb: close text file" << endl;
    myfile.close();

    if (debug)
        cout << "amtb: complete" << endl;

    return 0;
}

//-------------------------------------------------------------------------------
// just plot without fitting
void fit_none(bool zoom_in = true) {
    fit("none", "", 0, 1, zoom_in);
}

//-------------------------------------------------------------------------------
// free fit
void fit(string func_user = "gaus", double fit_from_user = 0.2, double fit_upto_user = 1.6, bool zoom_in = true) {
    fit("free", func_user, fit_from_user, fit_upto_user, zoom_in);
}

//-------------------------------------------------------------------------------
// constrained fit in 3,4j (Free in 1,2j)
void fit_fixPara(string func_user = "gaus", double fit_from_user = 0.2, double fit_upto_user = 1.6, bool zoom_in = true) {
    fit("fix", func_user, fit_from_user, fit_upto_user, zoom_in);
}
//-------------------------------------------------------------------------------
// constrained fit in 3,4j (gaus-mean-constrained in 1,2j > 0.3)
void fit_fixPara_mean12j_geq03(string func_user = "gaus", double fit_from_user = 0.2, double fit_upto_user = 1.6,
        bool zoom_in = true) {
    limit_gaus_mean_12j = true;
    gaus_mean_min = 0.3;
    fit("fix", func_user, fit_from_user, fit_upto_user, zoom_in);
}
//-------------------------------------------------------------------------------
// constrained fit in 3,4j (gaus-mean-constrained in 1,2j > 0.4)
void fit_fixPara_mean12j_geq04(string func_user = "gaus", double fit_from_user = 0.2, double fit_upto_user = 1.6,
        bool zoom_in = true) {
    limit_gaus_mean_12j = true;
    gaus_mean_min = 0.4;
    fit("fix", func_user, fit_from_user, fit_upto_user, zoom_in);
}

//-------------------------------------------------------------------------------
void getFitRes(int j, TPad *gpad, string func, TH1D *all) {

    // Get fitted function
    //---------------------

    TF1 *myf = all->GetFunction(func.c_str());
    myf->SetLineColor(kRed);

    TF1 *myf2 = (TF1*) myf->Clone(); //range 0-0.1
    myf2->SetLineColor(kBlue);
    myf2->SetRange(0, 0.1);

    TF1 *myf3 = (TF1*) myf->Clone(); //range 0.1 to 0.2
    myf3->SetLineColor(kBlue);
    myf3->SetLineStyle(kDashed);
    myf3->SetRange(0.1, fit_from);

    gpad->cd();

    myf->Draw("same");
    myf2->Draw("same");
    myf3->Draw("same");

    // Get fit results
    //----------------
    fit_chi2[j] = myf->GetChisquare();
    fit_ndf[j] = myf->GetNDF();
    n_extrap[j] = myf->Integral(sig_from, sig_upto) / this_bw;

    if (do_fit == "fix")
        getParametersForConstrainedFit(j, myf);
}

//-------------------------------------------------------------------------------
void getParametersForConstrainedFit(int j, TF1 *myf) {

    // fixPara: Get fit results
    //--------------------------
    fit_par0[j] = myf->GetParameter(0);//1st para p0
    fit_par1[j] = myf->GetParameter(1);//2nd para p1
    if (nFreePara >= 3) {
        fit_par2[j] = myf->GetParameter(2);//3rd para p2
        if (nFreePara >= 4) {
            fit_par3[j] = myf->GetParameter(3);//4th para p3
        }
    }
}


