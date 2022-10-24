
#include "TB1106SensitiveDetector.hh"
#include "G4RunManager.hh"
#include "G4RunManagerFactory.hh"
#include "G4Cerenkov.hh"


TB1106SensitiveDetector::TB1106SensitiveDetector(G4String name) : 
	G4VSensitiveDetector(name)
{}

TB1106SensitiveDetector::~TB1106SensitiveDetector()
{}

G4bool TB1106SensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *R0hist)
{
	G4int evt;
	G4int photons=0;

	G4Track* track = aStep->GetTrack();
	track->SetTrackStatus(fStopAndKill);

	G4StepPoint*  preStepPoint = aStep->GetPreStepPoint();
	G4StepPoint* postStepPoint = aStep->GetPostStepPoint();

	G4ThreeVector posParticle = preStepPoint->GetPosition();
	G4ThreeVector vertex      = track->GetVertexPosition();
	G4ThreeVector dir         = track->GetMomentumDirection();

	const G4VTouchable* touchable = aStep->GetPreStepPoint()->GetTouchable();

	G4int copyNO  = touchable->GetCopyNumber();
	G4int trackID = track->GetTrackID();

	G4VPhysicalVolume* physVol = touchable->GetVolume();
	G4ThreeVector pos = physVol->GetTranslation();

	evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();

	const G4DynamicParticle* particle = track->GetDynamicParticle();
	G4int PDGcode                     = particle->GetPDGcode();

	G4ParticleDefinition* parDef = particle->GetDefinition();	
	const G4String Partname      = parDef->GetParticleName();

	const G4String process_name = postStepPoint->GetProcessDefinedStep()->GetProcessName();

	//Fill the NTuple with Cerenkov hit information
	  G4AnalysisManager* man = G4AnalysisManager::Instance();
	 
	if (process_name == "Cerenkov") {  
      G4Cerenkov* proc = (G4Cerenkov*) postStepPoint->GetProcessDefinedStep();
	  photons = proc->GetNumPhotons();

	  G4cout << "------ CERENKOV DETECTED LOOP -------------" << G4endl;
	  G4cout << "IN EVENT       : " << evt                    << G4endl;
	  G4cout << "THE TRACK ID IS: " << trackID                << G4endl;
      G4cout << "THE PROCESS IS : " << process_name           << G4endl;
	  G4cout << "THE VOLUME IS  : " << physVol->GetName()     << G4endl;
	  G4cout << "Hit Position   : " << posParticle            << G4endl;
	  G4cout << "Direction      : " << dir                    << G4endl;
	  G4cout << "---------------------------------------\n\n" << G4endl;

	  man->FillNtupleDColumn(1,0, posParticle[0]);
	  man->FillNtupleDColumn(1,1, posParticle[1]);
	  man->FillNtupleDColumn(1,2, posParticle[2]);
	  man->FillNtupleIColumn(1,3, evt);
	  man->AddNtupleRow(1);
	  }

	
    
	return true;
}