#include "SteppingAction.hh"
#include "EventAction.hh"
#include "Geometry.hh"

#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
#include "Analysis.hh"

#include <math.h>
#define PI 3.14159265

using namespace std;

SteppingAction::SteppingAction(EventAction* eventAction)
: G4UserSteppingAction(),
  fEventAction(eventAction),
  fScoringVol(0) 
{}

SteppingAction::~SteppingAction()
{}

void SteppingAction::UserSteppingAction(const G4Step* step)
{
  if(step->GetTrack()->GetNextVolume()==0) return;//If the next volume is outofworld, halt.

  // G4AnalysisManager* analysisManager = G4AnalysisManager::Instance(); 
	G4TouchableHandle theTouchable = step->GetPreStepPoint()->GetTouchableHandle();
  G4TouchableHandle NextTouchable = step->GetPostStepPoint()->GetTouchableHandle();

  G4String volumeName = theTouchable->GetVolume()-> GetName();
  // G4String NextVolume = NextTouchable->GetVolume()->GetName();


  //G4int motherCopyNo = theTouchable->GetCopyNumber(1);
G4int copyNo = theTouchable->GetCopyNumber();
		//G4int chID=copyNo+motherCopyNo;	
		G4double edepStep = step->GetTotalEnergyDeposit();
		// G4cout<<chID<<G4endl;

		fEventAction->AddeDep(copyNo, edepStep);//fill energy deposit each layer

		// if(motherCopyNo==2000)
		// {
		// 	G4int stepNo = step->GetTrack()->GetCurrentStepNumber();
		// 	G4int trackID= step->GetTrack()->GetTrackID();
		// 	fEventAction->SET_TrigCh( trackID, stepNo, copyNo);
		// 	// G4cout<<trackID<<" "<< stepNo <<" "<<chID<<G4endl;
		// }




	// if(volumeName=="HEP_PV")
	// {
	// 	G4int copyNo = theTouchable->GetCopyNumber();
	// 	G4double edepStep = step->GetTotalEnergyDeposit();
	// 	fEventAction->AddeDep(copyNo, edepStep);
	// }

}



