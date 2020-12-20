#include "headers/Meteorite.h"

void plot1()
{
    // Input file directory
    string inDir = "../rootfiles/";
    // Input file
    string inFile = "meteorite_data.root";


    ///////////////// Load Data From Tree ///////////////////////
    TFile *input = new TFile((inDir + inFile).c_str(), "read");
    TTree *data_tree = (TTree*)input->Get("meteorite_data");

    Meteorite *temp = new Meteorite();
    data_tree->SetBranchAddress("id", &temp->id);
    data_tree->SetBranchAddress("type", &temp->type);
    data_tree->SetBranchAddress("year", &temp->year);
    data_tree->SetBranchAddress("mass", &temp->mass);
    data_tree->SetBranchAddress("fallen", &temp->fallen);
    data_tree->SetBranchAddress("latitude", &temp->latitude);
    data_tree->SetBranchAddress("longitude", &temp->longitude);

    vector<Meteorite> meteorites;
    for (int i = 0; i < data_tree->GetEntries(); i++) {
        data_tree->GetEntry(i);
        meteorites.push_back(new Meteorite(temp));
        // cout << meteorites[i].id << "\t" << meteorites[i].type << "\t" << meteorites[i].mass << "\t" << meteorites[i].fallen << "\t" << meteorites[i].year << "\t" << meteorites[i].latitude << "\t" << meteorites[i].longitude << endl;
    }



    //////////////////// Preparing Canvas ///////////////////////


    TCanvas *c1 = new TCanvas("c1", "", 800, 500);
    c1->SetTickx();
    c1->SetTicky();
    c1->SetGridx();
    c1->SetGridy();

    TCanvas *c2 = new TCanvas("c2", "", 800, 500);
    c2->SetTickx();
    c2->SetTicky();
    c2->SetGridx();
    c2->SetGridy();

    c1->cd();
    TH1D *hist = new TH1D("hist", "Meteorite Landings (1560 - 1960)", 30, 1560, 1960);
    hist->GetXaxis()->SetTitle("Year");
    hist->GetYaxis()->SetTitle("Landings");
    for (Meteorite &m : meteorites)
        hist->Fill(m.year);
    hist->SetStats(0);
    hist->Draw();
    TF1 *gaus = new TF1("f1", "gaus", 1950, 2050);
    gaus->SetLineWidth(3);
    hist->SetFillColorAlpha(kBlue, 0.5);
    gaus->SetLineColor(kRed);
    hist->Fit(gaus);

    TLegend *leg = new TLegend(0.175,0.64,0.43,0.79);
    leg->SetBorderSize(0);
    leg->AddEntry(hist, "Measured Data", "f");
    leg->AddEntry(gaus, "Gaussian Fit", "l");
    leg->Draw();

    c2->cd();
    TH1D *hist1 = new TH1D("hist1", "Meteorite Landings (1950 - 2050)", 50, 1850, 2050);
    hist1->GetXaxis()->SetTitle("Year");
    hist1->GetYaxis()->SetTitle("Landings");
    for (Meteorite &m : meteorites)
        hist1->Fill(m.year);
    hist1->SetStats(0);
    hist1->Draw();
    TF1 *gaus1 = new TF1("f1", "gaus", 1950, 2050);
    gaus1->SetLineWidth(3);
    hist1->SetFillColorAlpha(kRed, 0.5);
    gaus1->SetLineColor(kBlue);
    hist1->Fit(gaus1);

    TLegend *leg1 = new TLegend(0.175,0.64,0.43,0.79);
    leg1->SetBorderSize(0);
    leg1->AddEntry(hist1, "Measured Data", "f");
    leg1->AddEntry(gaus1, "Gaussian Fit", "l");
    leg1->Draw();
}
