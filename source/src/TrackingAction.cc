//This TrackinAction is to record the incident particle energy, location, directions
//Created by Inchun chondrite  2018.12.21.

#include "TrackingAction.hh"

#include "G4Track.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
#include "Analysis.hh"

#include <math.h>
#define PI 3.14159265

TrackingAction::TrackingAction()
:G4UserTrackingAction()
{ }

void TrackingAction::PreUserTrackingAction(const G4Track* track)
{
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
 
  G4int ID                = track->GetTrackID();
  // G4int particle          = track->GetDynamicParticle()->GetPDGcode();
  G4double edep           = track->GetKineticEnergy();
  G4ThreeVector vertex    = track->GetPosition();
  G4ThreeVector direction = track->GetMomentumDirection();
   
  G4double x = vertex.x(), y = vertex.y(), z = vertex.z();
  G4double theta = direction.theta()*180/PI, phi = direction.phi()*180/PI+180;
  if(ID==1)
  {
    analysisManager->FillNtupleDColumn(0,0,edep);
    analysisManager->FillNtupleDColumn(0,1,x);
    analysisManager->FillNtupleDColumn(0,2,y);
    analysisManager->FillNtupleDColumn(0,3,z);
    analysisManager->FillNtupleDColumn(0,4,phi);
    analysisManager->FillNtupleDColumn(0,5,theta);
   }  

}







