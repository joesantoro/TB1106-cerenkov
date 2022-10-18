/// \file TB1106.cc
// MAIN ROUTINE FOR THE TB1106 CERENKOV SIMULATION

#include "TB1106DetectorConstruction.hh"
#include "TB1106ActionInitialization.hh"

#include "G4RunManagerFactory.hh"
#include "G4RunManager.hh"
#include "G4UImanager.hh"

#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "G4TScoreNtupleWriter.hh"

#include "Randomize.hh"
#include "TB1106PhysicsList.hh"
#include "TB1106Analysis.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int main(int argc,char** argv)
{
  // Detect interactive mode (if no arguments) and define UI session
  //
  G4UIExecutive* ui = 0;
  if ( argc == 1 ) {
    ui = new G4UIExecutive(argc, argv);
  }

  // Construct the default run manager
  //----------------------------------
  //G4RunManager* runManager = new G4RunManager();
  auto* runManager = G4RunManagerFactory::CreateRunManager(G4RunManagerType::Default, 4);

  // Set mandatory initialization classes
  //-------------------------------------
  // Detector construction
  runManager->SetUserInitialization(new TB1106DetectorConstruction());

  // Physics lists
  runManager->SetUserInitialization(new TB1106PhysicsList());

  // User action initialization
  runManager->SetUserInitialization(new TB1106ActionInitialization());
  
  // Initialize visualization
  //
  G4VisManager* visManager = new G4VisExecutive;
  // G4VisExecutive can take a verbosity argument - see /vis/verbose guidance.
  // G4VisManager* visManager = new G4VisExecutive("Quiet");
  visManager->Initialize();

  // Get the pointer to the User Interface manager
  G4UImanager* UImanager = G4UImanager::GetUIpointer();

  // Activate score ntuple writer
  // The Root output type (Root) is selected in TB1106Analysis.hh.
  // The verbose level can be also set via UI commands
  // /score/ntuple/writerVerbose level
  // 
  //G4TScoreNtupleWriter<G4AnalysisManager> scoreNtupleWriter;
  //scoreNtupleWriter.SetVerboseLevel(1);

  // Process macro or start UI session
  //
  if ( ! ui ) { 
    // batch mode
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager->ApplyCommand(command+fileName);
  }
  else { 
    // interactive mode
    UImanager->ApplyCommand("/control/execute init_vis.mac");
    ui->SessionStart();
    delete ui;
  }

  // Job termination
  // Free the store: user actions, physics_list and detector_description are
  // owned and deleted by the run manager, so they should not be deleted 
  // in the main() program !
  
  delete visManager;
  delete runManager;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....
