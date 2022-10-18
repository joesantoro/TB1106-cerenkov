
/// \file TB1106ActionInitialization.cc
/// \brief Implementation of the TB1106ActionInitialization class

#include "TB1106ActionInitialization.hh"
#include "TB1106PrimaryGeneratorAction.hh"
#include "TB1106RunAction.hh"
#include "TB1106EventAction.hh"
#include "TB1106SteppingAction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TB1106ActionInitialization::TB1106ActionInitialization()
 : G4VUserActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TB1106ActionInitialization::~TB1106ActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TB1106ActionInitialization::BuildForMaster() const
{
  TB1106RunAction* runAction = new TB1106RunAction;
  SetUserAction(runAction);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TB1106ActionInitialization::Build() const
{
  SetUserAction(new TB1106PrimaryGeneratorAction);

  TB1106RunAction* runAction = new TB1106RunAction;
  SetUserAction(runAction);
  
  TB1106EventAction* eventAction = new TB1106EventAction(runAction);
  SetUserAction(eventAction);
  
  SetUserAction(new TB1106SteppingAction(eventAction));
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
