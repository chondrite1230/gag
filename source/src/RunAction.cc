#include "RunAction.hh"
#include "Analysis.hh"

#include "G4Run.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

using namespace std;
char Name[10];

RunAction::RunAction()
 : G4UserRunAction()
{
G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

  G4cout << "Using " << analysisManager->GetType() << G4endl;

  analysisManager->SetFileName("BeamTest");

  analysisManager->SetVerboseLevel(1);
  analysisManager->SetActivation(true);

  ///create Ntuple///
  analysisManager->CreateNtuple("Events","Event");
  analysisManager->CreateNtupleDColumn("source_E");//Column 0
  analysisManager->CreateNtupleDColumn("source_Loc_x");//Column 1
  analysisManager->CreateNtupleDColumn("source_Loc_y");//Column 2
  analysisManager->CreateNtupleDColumn("source_Loc_z");//Column 3
  analysisManager->CreateNtupleDColumn("source_dir_phi");//Column 4
	analysisManager->CreateNtupleDColumn("source_dir_theta");//Column 5
 
  analysisManager->CreateNtupleDColumn("eDep_Si_sum");//Column 6
  analysisManager->CreateNtupleDColumn("eDep_0");//Column 7
  analysisManager->CreateNtupleDColumn("eDep_1");//Column 8
  analysisManager->CreateNtupleDColumn("eDep_2");//Column 9
  analysisManager->CreateNtupleDColumn("eDep_3");//Column 10
  analysisManager->CreateNtupleDColumn("eDep_4");//Column 11
  /* analysisManager->CreateNtupleDColumn("eDep_5");
  analysisManager->CreateNtupleDColumn("eDep_Si6");
  analysisManager->CreateNtupleDColumn("eDep_Si7");
  analysisManager->CreateNtupleDColumn("eDep_Si8");
  */
  analysisManager->FinishNtuple();
  // analysisManager->SetNtupleActivation(false);
}



RunAction::~RunAction()
{
  delete G4AnalysisManager::Instance();
}

void RunAction::BeginOfRunAction(const G4Run* /*run*/)
{
G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

  G4cout<<"*******Run start*******"<<G4endl;
  
  analysisManager->OpenFile();
}

void RunAction::EndOfRunAction(const G4Run* /*run*/)
{
G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  
  analysisManager->Write();
  analysisManager->CloseFile();
  
  G4cout<<"********End Run********"<<G4endl;
}

