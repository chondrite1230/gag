{
  gROOT->Reset();
  char rootfile[50];
  double_t eDep_Si_sum;

  TH2D *h1 = new TH2D("h1", "h1", 3000, 0, 3, 3000, 0, 3000);

  //  int n=1;
  for (int ene=10;ene<=10;ene++)
  {
    sprintf(rootfile, "../beam_incline_12degree_%d.root", ene);
    TFile *file = new TFile(rootfile);
    TTree *eventtree = (TTree *)file->Get("Events");
    eventtree->Print();
    eventtree->SetBranchAddress("eDep_Si_sum",&eDep_Si_sum);
    
    Int_t event = eventtree->GetEntries();
    
    for (int i = 0; i < event; i++)
    {
      eventtree->GetEntry(i);
      h1->Fill(eDep_Si_sum, ene);
    }
    //n++;
    //index++;
    cout<<ene<<" "<<rootfile<<endl;

    file->Close();
  }
  
  //gStyle->SetOptStat(kFALSE);
  //    h1->GetYaxis()->SetRangeUser();
  
  h1->Draw("colz");
  gPad->SetLogz();

  TFile *newfile=new TFile("Event_L_ch0.root","new");
  h1->Write();

}
