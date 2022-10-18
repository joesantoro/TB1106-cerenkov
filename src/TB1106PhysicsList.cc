#include "TB1106PhysicsList.hh"
#include "QBBC.hh"

TB1106PhysicsList::TB1106PhysicsList()
{  
	RegisterPhysics(new G4EmStandardPhysics());
	RegisterPhysics(new G4OpticalPhysics());
	//RegisterPhysics(new QBBC);
}

TB1106PhysicsList::~TB1106PhysicsList()
{}
