
/// \file TB1106RunAction.cc
/// \brief Implementation of the TB1106RunAction class

#include "TB1106RunAction.hh"
#include "TB1106PrimaryGeneratorAction.hh"
#include "TB1106DetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4Run.hh"
#include "G4AccumulableManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

#include "g4root.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TB1106RunAction::TB1106RunAction()
: G4UserRunAction(),
  fEdep(0.),
  fEdep2(0.)
{ 
  // add new units for dose
  // 
  const G4double milligray = 1.e-3*gray;
  const G4double microgray = 1.e-6*gray;
  const G4double nanogray  = 1.e-9*gray;  
  const G4double picogray  = 1.e-12*gray;
   
  new G4UnitDefinition("milligray", "milliGy" , "Dose", milligray);
  new G4UnitDefinition("microgray", "microGy" , "Dose", microgray);
  new G4UnitDefinition("nanogray" , "nanoGy"  , "Dose", nanogray);
  new G4UnitDefinition("picogray" , "picoGy"  , "Dose", picogray); 

  // Register accumulable Variables to the accumulable manager
  G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
  accumulableManager->RegisterAccumulable(fEdep);
  accumulableManager->RegisterAccumulable(fEdep2); 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TB1106RunAction::~TB1106RunAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TB1106RunAction::BeginOfRunAction(const G4Run*)
{ 
  // inform the runManager to save random number seed
  G4RunManager::GetRunManager()->SetRandomNumberStore(false);

  // reset accumulables to their initial values
  G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
  accumulableManager->Reset();

  //MY ADDITIONS FOR THE CREATION OF A ROOT DATA FILE 
  //FOR MORE SOPHISTICATED ANALYSIS AND OUTPUT THAN THE ACCUMULABLE VARIABLES
  G4AnalysisManager* man  = G4AnalysisManager::Instance();
  
  man->OpenFile("output.root");

    man->CreateNtuple("Production", "Production");

    man->CreateNtupleIColumn(0,"fEvent"); //PID
    man->CreateNtupleDColumn(0,"vertexX");//VERTEX POSITIONS
    man->CreateNtupleDColumn(0,"vertexY");
    man->CreateNtupleDColumn(0,"vertexZ");
    man->CreateNtupleDColumn(0,"dirX");   //DIRECTION COSINES
    man->CreateNtupleDColumn(0,"dirY");
    man->CreateNtupleDColumn(0,"dirZ");
    man->CreateNtupleIColumn(0,"EventID"); //Event ID
    man->FinishNtuple(0);

 //Cerenkov detector-specific histograms
    man->CreateNtuple("Hits", "Hits");

    man->CreateNtupleDColumn(1,"CerHitX");//DETECTOR HIT POSITION
    man->CreateNtupleDColumn(1,"CerHitY");
    man->CreateNtupleDColumn(1,"CerHitZ");
    man->CreateNtupleIColumn(1,"EventID"); //Event ID
    man->FinishNtuple(1);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TB1106RunAction::EndOfRunAction(const G4Run* run)
{
  G4int nofEvents = run->GetNumberOfEvent();
  if (nofEvents == 0) return;

  // Merge accumulables 
  G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
  accumulableManager->Merge();

  // Compute dose = total energy deposit in a run and its variance
  G4double edep  = fEdep.GetValue();
  G4double edep2 = fEdep2.GetValue();
  
  G4double rms = edep2 - edep*edep/nofEvents;
  if (rms > 0.) rms = std::sqrt(rms); else rms = 0.;  

  //GET MASS OF THE SCORING VOLUME (WATER CUBE) TO CALCULATE DOSE (Gy)
  const TB1106DetectorConstruction* detectorConstruction
   = static_cast<const TB1106DetectorConstruction*>
     (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
  G4double mass = detectorConstruction->GetScoringVolume()->GetMass();
  G4double dose = edep/mass;
  G4double rmsDose = rms/mass;

  // Run conditions
  //  note: There is no primary generator action object for "master"
  //        run manager for multi-threaded mode.
  const TB1106PrimaryGeneratorAction* generatorAction
   = static_cast<const TB1106PrimaryGeneratorAction*>
     (G4RunManager::GetRunManager()->GetUserPrimaryGeneratorAction());
  G4String runCondition;
  if (generatorAction)
  {
    const G4ParticleGun* particleGun = generatorAction->GetParticleGun();
    runCondition += particleGun->GetParticleDefinition()->GetParticleName();
    runCondition += " of ";
    G4double particleEnergy = particleGun->GetParticleEnergy();
    runCondition += G4BestUnit(particleEnergy,"Energy");
  }
        
  // Print 
  if (IsMaster()) {
    G4cout
     << G4endl
     << "--------------------End of Global Run-----------------------";
  }
  else {
    G4cout
     << G4endl
     << "--------------------End of Local Run------------------------";
  }
  
  /*G4cout
     << G4endl
     << " The run consists of " << nofEvents << " "<< runCondition
     << G4endl
     << " Cumulated dose per run, in scoring volume : " 
     << G4BestUnit(dose,"Dose") << " rms = " << G4BestUnit(rmsDose,"Dose")
     << G4endl
     << "------------------------------------------------------------"
     << G4endl
     << G4endl;*/

  //MY ADDITIONS FOR THE CREATION OF A ROOT DATA FILE
  G4AnalysisManager* man = G4AnalysisManager::Instance();
  man->Write();
  man->CloseFile();
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TB1106RunAction::AddEdep(G4double edep)
{
  fEdep  += edep;
  fEdep2 += edep*edep;
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

