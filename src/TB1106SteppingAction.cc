
/// \file TB1106SteppingAction.cc
/// \brief Implementation of the TB1106SteppingAction class

#include "TB1106SteppingAction.hh"
#include "TB1106EventAction.hh"
#include "TB1106DetectorConstruction.hh"

#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"

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

  //SOME EXPERIMENTAL OUTPUT
  G4Track* theTrack = step->GetTrack();
  G4ThreeVector vertex = theTrack->GetVertexPosition();
  G4ThreeVector pos = theTrack->GetPosition();
  G4int trackID = theTrack->GetTrackID();
  const G4DynamicParticle* particle = theTrack->GetDynamicParticle();
  G4ParticleDefinition* parDef = particle->GetDefinition();

  G4int PDGcode = particle->GetPDGcode();
  const G4String Partname = parDef->GetParticleName();

  G4double enDep = step->GetTotalEnergyDeposit();
  G4double particleCharge = particle->GetCharge();
  G4double kineticEnergy = theTrack->GetKineticEnergy();

  //G4cout
      /*<< "Particle-->"   << " " << Partname << " "
      << "Vertex Pos-->" << " " << vertex   << " "
      << "Pos-->"        << " " << pos      << " "
      << "Track ID-->"   << " " << trackID  << " "*/
      //<< "Energy Deposited-->" << " " << enDep << " "
      //<< "Charge-->" << " " << particleCharge << " "
      //<< "Kinetic Energy-->" << " " << kineticEnergy << " " 
      //<< G4endl;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

