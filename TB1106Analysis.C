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

    cout << "The file contains the following NTuples:" << "\n";
    cout << "----------------------------------------" << "\n";

    TNtuple* tr  = (TNtuple*)f->Get("Hits");
    tr->ls();
    TNtuple* tr2 = (TNtuple*)f->Get("Production");
    tr2->ls();

    double vertexX, vertexY, vertexZ;
    double dirX, dirY, dirZ;
    int PID, EventID1,EventID2,numEvents;

    double CerHitX, CerHitY, CerHitZ;

    tr->SetBranchAddress("CerHitX", &CerHitX);
    tr->SetBranchAddress("CerHitY", &CerHitY);
    tr->SetBranchAddress("CerHitZ", &CerHitZ);
    tr->SetBranchAddress("EventID", &EventID1);

    tr2->SetBranchAddress("vertexX", &vertexX);
    tr2->SetBranchAddress("vertexY", &vertexY);
    tr2->SetBranchAddress("vertexZ", &vertexZ);
    tr2->SetBranchAddress("dirX", &dirX);
    tr2->SetBranchAddress("dirY", &dirY);
    tr2->SetBranchAddress("dirZ", &dirZ);
    tr2->SetBranchAddress("fEvent", &PID);
    tr2->SetBranchAddress("EventID", &EventID2);

    numEvents = (Int_t)tr2->GetMaximum("EventID");
    cout << " THE NUMBER OF EVENTS GENERATED IN THIS RUN IS: " << numEvents << "\n";


 //THE HISTOGRAMS

    //HISTO OF PARTICLE PIDS IN DETECTOR VOLUME
    gStyle->SetHistFillColor(8);
    gStyle->SetHistFillStyle(3002);
    TH1D* hPID    = new TH1D("hPID", "PID", 50, -50.0, 100.0);

    TH1D* hVx  = new TH1D("hVx", "Vertex position X(mm)", 100, -1000.0, 1000.0);
    TH1D* hDx  = new TH1D("hDx", "Dir Cosine X", 100, -1.0, 1.0);
    TH1D* hHx  = new TH1D("hHx", "Hit position X(mm)", 100, -300.0, 300.0);

    gStyle->SetHistFillColor(4);
    gStyle->SetHistFillStyle(3002);
    TH1D* hVy  = new TH1D("hVy", "Vertex position Y(mm)", 100, -1000.0, 1000.0);
    TH1D* hDy  = new TH1D("hDy", "Dir Cosine Y", 100, -1.0, 1.0);
    TH1D* hHy  = new TH1D("hHy", "Hit position Y(mm)", 100, -300.0, 300.0);

    gStyle->SetHistFillColor(2);
    gStyle->SetHistFillStyle(3002);
    
    TH1D* hVz  = new TH1D("hVz", "Vertex position Z(mm)", 100, -1000.0, 1000.0);
    TH1D* hDz  = new TH1D("hDz", "Dir Cosine Z", 100, -1.0, 1.0);
    TH1D* hHz  = new TH1D("hHz", "Hit position Z(mm)", 100, -300.0, 300.0);

    //2D plot(s)
    TH2* hHxHy   = new TH2F("hHxHy"  , "X-Y distribution of Detector hits", 100, -300.0, 300.0, 100, -300.0, 300.0);

    //3D plot(s)
    TH3* hVxVyVz = new TH3F("hVxVyVz", "3D distribution of Cerenkov Vertex Positions", 100, -250.0, 250.0, 100, -250.0, 250.0, 100, -250.0, 250.0);
    

    //EVENT LOOP TO FILL THE PRODUCTION HISTOGRAMS
    Int_t nentries2 = (Int_t)tr2->GetEntries();
    cout << "PRODUCTION LOOP" << "\n";
    cout << "===============" << "\n";
    cout << "PROCESSING " << nentries2 << " CERENKOV TRACKS" << "\n\n";

    for (Int_t i = 0; i < nentries2; i++)
    {
        tr2->GetEntry(i);
        hVx->Fill(vertexX);
        hVy->Fill(vertexY);
        hVz->Fill(vertexZ);
        hDx->Fill(dirX);
        hDy->Fill(dirY);
        hDz->Fill(dirZ);
        hVxVyVz->Fill(vertexX, vertexZ, vertexY);
        hPID->Fill(PID);
    }

    //EVENT LOOP TO FILL THE HIT HISTOGRAMS
    TH1D* hEvents = new TH1D("hEvents", "Event ID", 100, 0, numEvents);
    Int_t nentries = (Int_t)tr->GetEntries();

    cout << "HIT LOOP" << "\n";
    cout << "========" << "\n";
    cout << "PROCESSING " << nentries << " HITS IN THE DETECTOR ARRAY" << "\n\n";

    for (Int_t i = 0; i<nentries; i++)
    {
            tr->GetEntry(i);
            hHx->Fill(CerHitX);
            hHy->Fill(CerHitY);
            hHz->Fill(CerHitZ);
            hHxHy->Fill(CerHitX, CerHitY);
            hEvents->Fill(EventID1);
            //cout << "Event Number: "<< EventID1 << "\n";

             
    }
    
    cout << "RENDERING HISTOGRAMS AND PLOTS..." << "\n";
    cout << "==============================" << "\n";

  //The 1st canvas
      TCanvas* Can = new TCanvas("c1","1D Analysis");
      Can->Divide(3,3);
      Can->cd(1);hVx->Draw();
      Can->cd(2);hVy->Draw();
      Can->cd(3);hVz->Draw();
      Can->cd(4);hDx->Draw();
      Can->cd(5);hDy->Draw();
      Can->cd(6);hDz->Draw();
      Can->cd(7);hHx->Draw();
      Can->cd(8);hHy->Draw();
      Can->cd(9);hHz->Draw();
    

 //The 2nd Canvas
      TCanvas* Can2 = new TCanvas("c2", "2D Analysis");
      hHxHy->Draw("Colz");

 //The 3rd Canvas
      TCanvas* Can3 = new TCanvas("c3", "3D Analysis");
      hVxVyVz->Draw("BOX2Z");

//The 4th canvas
      TCanvas* Can4 = new TCanvas("c4", "PID");
      hPID->Draw();

      //The 4th canvas
      TCanvas* Can5 = new TCanvas("c5", "EventID");
      hEvents->Draw();


}

