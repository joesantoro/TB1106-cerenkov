// A ROOT macro to analyze the results of the TB1106 Cerenkov

#include <stdio.h>
#include <string.h>
#include "TROOT.h"
#include "TCanvas.h"
#include "TTree.h"
#include "TFile.h"
#include "TStyle.h"
#include "TGFileBrowser.h"
#include "TGFileDialog.h"
#include "TF1.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TString.h"

void TB1106Analysis() {
    
    char* fname = 0;
    TGFileInfo file;

    TGFileDialog* B = new TGFileDialog(gClient->GetDefaultRoot(), gClient->GetDefaultRoot(), kFDOpen, &file);
    
    fname = file.fFilename;
    cout << "Opening ROOT file: " << fname << endl;
    
    TFile* f = new TFile(fname);

    TNtuple* tr = (TNtuple*)f->Get("Hits");
    tr->ls();
   
    double vertexX, vertexY, vertexZ;
    double hitsX, hitsY, hitsZ;

    tr->SetBranchAddress("vertexX", &vertexX);
    tr->SetBranchAddress("vertexY", &vertexY);
    tr->SetBranchAddress("vertexZ", &vertexZ);
    tr->SetBranchAddress("hitsX", &hitsX);
    tr->SetBranchAddress("hitsY", &hitsY);
    tr->SetBranchAddress("hitsZ", &hitsZ);

 //THE HISTOGRAMS
    gStyle->SetHistFillColor(8);
    gStyle->SetHistFillStyle(3002);
    TH1D* hVx = new TH1D("hVx", "Vertex position X(mm)", 100, -1000.0, 1000.0);
    TH1D* hHx = new TH1D("hHx", "Hit position X(mm)", 100, -300.0, 300.0);
    
    gStyle->SetHistFillColor(4);
    gStyle->SetHistFillStyle(3002);
    TH1D* hVy = new TH1D("hVy", "Vertex position Y(mm)", 100, -1000.0, 1000.0);
    TH1D* hHy = new TH1D("hHy", "Hit position Y(mm)", 100, -300.0, 300.0);

    gStyle->SetHistFillColor(2);
    gStyle->SetHistFillStyle(3002);
    TH1D* hVz = new TH1D("hVz", "Vertex position Z(mm)", 100, -1000.0, 1000.0);
    TH1D* hHz = new TH1D("hHz", "Hit position Z(mm)", 100, -300.0, 300.0);

    //2D plot(s)
    TH2* hHxHy = new TH2F("hHxHy", "X-Y distribution of detector hits", 100, -300.0, 300.0, 100, -300.0, 300.0);
   
    //3D plot(s)
    TH3* hVxVyVz = new TH3F("hVxVyVz", "3D distribution of Vertex Positions", 100, -500.0, 500.0, 100, -500.0, 500.0, 100, -500.0, 500.0);

    //EVENT LOOP TO FILL THE HISTOGRAMS
    Int_t nentries = (Int_t)tr->GetEntries();
    cout << "PROCESSING " << nentries << " EVENTS" << "\n";

    for (Int_t i = 0; i<nentries; i++)
    {
        tr->GetEntry(i);
        hVx->Fill(vertexX);
        hVy->Fill(vertexY);
        hVz->Fill(vertexZ);
        hHx->Fill(hitsX);
        hHy->Fill(hitsY);
        hHz->Fill(hitsZ);
        hHxHy->Fill(hitsX, hitsY);
        hVxVyVz->Fill(vertexX, vertexZ,vertexY);
    }
    
  //The 1st canvas
      TCanvas* Can = new TCanvas("c1","1D Analysis");
      Can->Divide(3,2);
      Can->cd(1);hVx->Draw();
      Can->cd(2);hVy->Draw();
      Can->cd(3);hVz->Draw();
      Can->cd(4);hHx->Draw();
      Can->cd(5);hHy->Draw();
      Can->cd(6);hHz->Draw();

 //The 2nd Canvas
      TCanvas* Can2 = new TCanvas("c2", "2D/3D Analysis");
      Can2->Divide(2, 1);
      Can2->cd(1); hHxHy->Draw("Colz");
      Can2->cd(2); hVxVyVz->Draw("Colz");
  


}

