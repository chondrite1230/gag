#include "EventAction.hh"

#include "G4RunManager.hh"
#include "G4Event.hh"

#include "G4UnitsTable.hh"
#include "Analysis.hh"
#include "Randomize.hh"
#include <iomanip> 

#include "G4Track.hh"

EventAction::EventAction()
 : G4UserEventAction() 
{}

EventAction::~EventAction()
{}

void EventAction::BeginOfEventAction(const G4Event* /*event*/)
{
  memset(sum_eDep,0,sizeof(sum_eDep));//reset array function
}

void EventAction::EndOfEventAction(const G4Event* /*event*/)
{
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
 
  G4double sum_energy = 0.;
  G4double sum_Si[10];
  // G4int Trigger=999;
  
  for(G4int motherID=0;motherID<5;motherID++)
  {
    sum_Si[motherID]=0.;

    if(GetSum(motherID)==0) continue;

    sum_energy += GetSum(motherID);
    sum_Si[motherID] += GetSum(motherID);
    
  }

  analysisManager->FillNtupleDColumn(0,6, sum_energy);
  analysisManager->FillNtupleDColumn(0,7, sum_Si[0]);//Alwindow
  analysisManager->FillNtupleDColumn(0,8, sum_Si[1]);
  analysisManager->FillNtupleDColumn(0,9, sum_Si[2]);
  analysisManager->FillNtupleDColumn(0,10, sum_Si[3]);
  analysisManager->FillNtupleDColumn(0,11, sum_Si[4]);
/*  analysisManager->FillNtupleDColumn(0,12, sum_Si[5]);
  analysisManager->FillNtupleDColumn(0,13, sum_Si[6]);
  analysisManager->FillNtupleDColumn(0,14, sum_Si[7]);
  analysisManager->FillNtupleDColumn(0,15, sum_Si[8]);
*/
  // analysisManager->FillNtupleIColumn(0,12,Trigger);
  // G4cout << "Trig channel:" << GET_TrigCh() <<G4endl;

 analysisManager-> AddNtupleRow(0);

} 
