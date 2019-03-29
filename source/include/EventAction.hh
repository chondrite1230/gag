
#ifndef EventAction_h
#define EventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

/// Event action class
///

enum{noSi = 10000};   // no of Sichannels

class EventAction : public G4UserEventAction
{
public:
  EventAction();
  virtual ~EventAction();

  virtual void    BeginOfEventAction(const G4Event* event);
  virtual void    EndOfEventAction(const G4Event* event);
    inline void AddeDep(G4int i, G4double de) {
        sum_eDep[i] +=de;
    }
    inline G4double GetSum(G4int i){
        return sum_eDep[i];
    }


    void SET_TrigCh(G4int a, G4int b, G4int c){
        if(TrackID == 0) TrackID=a, StepID=b, TrigCh=c;  
        else if (TrackID <= a ){
            if(StepID > b) TrackID=a, StepID=b, TrigCh=c;//find lowest TrackID&StepID
        } 
    }
    G4int GET_TrigCh(){
        return  TrigCh;
    }



private:
  G4double  sum_eDep[noSi];

  G4int TrigCh;
  G4int TrackID;
  G4int StepID;
  
};

#endif

    
