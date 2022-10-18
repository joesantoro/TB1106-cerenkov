
#include "TB1106SensitiveDetector.hh"
#include "G4RunManager.hh"
#include "G4RunManagerFactory.hh"


TB1106SensitiveDetector::TB1106SensitiveDetector(G4String name) : 
	G4VSensitiveDetector(name)
{}

TB1106SensitiveDetector::~TB1106SensitiveDetector()
{}

G4bool TB1106SensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *R0hist)
{
	G4Track* track = aStep->GetTrack();

	track->SetTrackStatus(fStopAndKill);

	G4StepPoint*  preStepPoint = aStep->GetPreStepPoint();
	G4StepPoint* postStepPoint = aStep->GetPostStepPoint();

	G4ThreeVector posParticle = preStepPoint->GetPosition();

	const G4VTouchable* touchable = aStep->GetPreStepPoint()->GetTouchable();

	G4int copyNO = touchable->GetCopyNumber();
	G4VPhysicalVolume* physVol = touchable->GetVolume();
	G4ThreeVector pos = physVol->GetTranslation();

	G4int evt;
	evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();

	G4ThreeVector vertex = track->GetVertexPosition();
	const G4DynamicParticle* particle = track->GetDynamicParticle();
	G4ParticleDefinition* parDef = particle->GetDefinition();

	G4int PDGcode = particle->GetPDGcode();
	const G4String Partname = parDef->GetParticleName();

	//Fill the NTuple with good stuff
	G4AnalysisManager* man = G4AnalysisManager::Instance();
	man->FillNtupleIColumn(0,PDGcode);
	man->FillNtupleDColumn(1,posParticle[0]);
	man->FillNtupleDColumn(2,posParticle[1]);
	man->FillNtupleDColumn(3,posParticle[2]);
	man->FillNtupleDColumn(4, vertex[0]);
	man->FillNtupleDColumn(5, vertex[1]);
	man->FillNtupleDColumn(6, vertex[2]);
	man->AddNtupleRow(0);
    
	return true;
}