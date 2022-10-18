#ifndef TB1106SensitiveDetector_HH
#define TB1106SensitiveDetector_HH

#include "G4VSensitiveDetector.hh"
#include "g4root.hh"
#include "G4RunManager.hh"


class TB1106SensitiveDetector : public G4VSensitiveDetector
{
public:
	TB1106SensitiveDetector(G4String);
   ~TB1106SensitiveDetector();
	
private:
	virtual G4bool ProcessHits(G4Step*, G4TouchableHistory*);
};

#endif

