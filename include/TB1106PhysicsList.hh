#ifndef TB1106PhysicsList_HH
#define TB1106PhysicsList_HH

#include "G4VModularPhysicsList.hh"
#include "G4EmStandardPhysics.hh"
#include "G4OpticalPhysics.hh"

class TB1106PhysicsList : public G4VModularPhysicsList
{
public:
	TB1106PhysicsList();
	~TB1106PhysicsList();
};

#endif
