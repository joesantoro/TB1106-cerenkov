
/// \file TB1106SteppingAction.cc
/// \brief Implementation of the TB1106SteppingAction class

#include "TB1106SteppingAction.hh"
#include "TB1106EventAction.hh"
#include "TB1106DetectorConstruction.hh"

#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
#include "G4Cerenkov.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TB1106SteppingAction::TB1106SteppingAction(TB1106EventAction* eventAction)
: G4UserSteppingAction(),
  fEventAction(eventAction),
  fScoringVolume()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TB1106SteppingAction::~TB1106SteppingAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TB1106SteppingAction::UserSteppingAction(const G4Step* step)
{
  if (!fScoringVolume) { 
    const TB1106DetectorConstruction* detectorConstruction
      = static_cast<const TB1106DetectorConstruction*>
        (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
    fScoringVolume = detectorConstruction->GetScoringVolume();   
  }

  // get volume of the current step
  G4LogicalVolume* volume 
    = step->GetPreStepPoint()->GetTouchableHandle()
      ->GetVolume()->GetLogicalVolume();
      
  // check if we are in scoring volume
  if (volume != fScoringVolume) return;

  // collect energy deposited in this step
  G4double edepStep = step->GetTotalEnergyDeposit();
  fEventAction->AddEdep(edepStep);  

  //--------------------------------------------------------------
  //-----------------SOME EXPERIMENTAL OUTPUT---------------------
  //--------------------------------------------------------------
    G4int evt;
    G4int photons = 0;

    G4Track* theTrack = step->GetTrack();
    G4StepPoint* preStepPoint  = step->GetPreStepPoint();
    G4StepPoint* postStepPoint = step->GetPostStepPoint();

    G4ThreeVector vertex      = theTrack->GetVertexPosition();
    G4ThreeVector posParticle = theTrack->GetPosition();
    G4ThreeVector dir         = theTrack->GetMomentumDirection();

    G4double kEnergy = theTrack->GetKineticEnergy();

    const G4String process_name = postStepPoint->GetProcessDefinedStep()->GetProcessName();

    G4int trackID = theTrack->GetTrackID();
    evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();

    const G4DynamicParticle* particle = theTrack->GetDynamicParticle();
    G4int PDGcode = particle->GetPDGcode();

    G4ParticleDefinition* parDef = particle->GetDefinition();
    const G4String Partname = parDef->GetParticleName();

    //----------- Fill Production NTuple ---------------- 
    G4AnalysisManager* man = G4AnalysisManager::Instance();

    if (process_name == "Cerenkov") {
        G4Cerenkov* proc = (G4Cerenkov*)postStepPoint->GetProcessDefinedStep();
        photons = proc->GetNumPhotons();

        /*G4cout << "------ CERENKOV PRODUCTION LOOP -------------" << G4endl;
        G4cout << "IN EVENT       : " << evt << G4endl;
        G4cout << "THE PID IS     : " << PDGcode << G4endl;
        G4cout << "THE TRACK ID IS: " << trackID << G4endl;
        G4cout << "THE PROCESS IS : " << process_name << G4endl;
        G4cout << "IT PRODUCED    : " << photons << " PHOTONS" << G4endl;
        G4cout << "THE VOLUME IS  : " << volume->GetName() << G4endl;
        G4cout << "Vertex Position: " << vertex << G4endl;
        G4cout << "Hit Position   : " << posParticle << G4endl;
        G4cout << "Direction      : " << dir << G4endl;
        G4cout << "Kinetic Energy : " << kEnergy << G4endl;
        G4cout << "---------------------------------------\n\n" << G4endl;*/

        man->FillNtupleIColumn(0,0, PDGcode);
        man->FillNtupleDColumn(0,1, vertex[0]);
        man->FillNtupleDColumn(0,2, vertex[1]);
        man->FillNtupleDColumn(0,3, vertex[2]); 
        man->FillNtupleDColumn(0,4, dir[0]);
        man->FillNtupleDColumn(0,5, dir[1]);
        man->FillNtupleDColumn(0,6, dir[2]);
        man->FillNtupleIColumn(0,7, evt);
        man->AddNtupleRow(0);
    }
     

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

