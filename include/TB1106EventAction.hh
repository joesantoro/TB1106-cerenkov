
/// \file TB1106EventAction.hh
/// \brief Definition of the TB1106EventAction class

#ifndef TB1106EventAction_h
#define TB1106EventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

class TB1106RunAction;

/// Event action class
///

class TB1106EventAction : public G4UserEventAction
{
  public:
    TB1106EventAction(TB1106RunAction* runAction);
    virtual ~TB1106EventAction();

    virtual void BeginOfEventAction(const G4Event* event);
    virtual void EndOfEventAction(const G4Event* event);

    void AddEdep(G4double edep) { fEdep += edep; }

  private:
    TB1106RunAction* fRunAction;
    G4double     fEdep;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

    
