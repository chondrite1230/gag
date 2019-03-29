//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Geant4 Application: Tutorial course for Hep/Space Users: 2015.08.24 @Hiroshima
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "Geometry.hh"
#include "UserActionInitialization.hh"

#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
//#include "QGSP_BIC.hh"
#include "FTFP_BERT.hh"

#include "G4UIsession.hh"
#include "G4UIterminal.hh"
#include "G4MTRunManager.hh"
#include "G4RunManager.hh"

//-------------------------------------------------------------------------------
  int main( int argc, char** argv )
//-------------------------------------------------------------------------------
{
   // ============= [ Setting up the application environment ] ================
   typedef  FTFP_BERT PhysicsList;                   // Physics List
   G4String nameMainMacro = "GlobalSetup.mac";      // Initialization  macros
   // =========================================================================

// Construct the default run manager
  //  if(argc!=1)//VIS mode
  //  {
    // G4RunManager * runManager = new G4RunManager;
  //  }
  //  else//Batch mode
  //  {
    G4MTRunManager * runManager = new G4MTRunManager;
    G4int nThreads = G4Threading::G4GetNumberOfCores();
    G4cout<<"Number of Threads="<<nThreads<<G4endl;
    
    if (argc>=2) nThreads = G4UIcommand::ConvertToInt(argv[1]);
    else nThreads=1;
    G4cout<<"Threads="<<nThreads<<G4endl;
    
    runManager->SetNumberOfThreads(nThreads);
  //  }


// Set up mandatory user initialization: Geometry
   runManager->SetUserInitialization( new Geometry() );

// Set up mandatory user initialization: Physics-List
   runManager->SetUserInitialization( new PhysicsList );

// Set up user initialization: User Actions
   runManager->SetUserInitialization( new UserActionInitialization() );

// Initialize G4 kernel
   runManager->Initialize();
   
   
// Start interactive session
   if(nThreads==1)//VIS mode
   {
    // Create visualization environment
    G4VisManager* visManager = new G4VisExecutive;
    visManager->Initialize();

    G4UImanager*   uiManager = G4UImanager::GetUIpointer(); 
    G4UIExecutive* ui = new G4UIExecutive(argc, argv);
    uiManager->ApplyCommand("/control/execute " + nameMainMacro);
    ui->SessionStart();
    delete ui;
    delete visManager;
   }
   else//BATCH mode
   {
    // Create terminal ui environment 
    G4UIsession * session = new G4UIterminal;
    G4UImanager* uiManager = G4UImanager::GetUIpointer();
    uiManager->ApplyCommand("/control/execute " + nameMainMacro);
    session->SessionStart();
    delete session;
   }

// Job termination
   delete runManager;
   return 0;
}
