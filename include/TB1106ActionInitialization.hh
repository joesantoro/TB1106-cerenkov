
/// \file TB1106ActionInitialization.hh
/// \brief Definition of the TB1106ActionInitialization class

#ifndef TB1106ActionInitialization_h
#define TB1106ActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

/// Action initialization class.

class TB1106ActionInitialization : public G4VUserActionInitialization
{
  public:
    TB1106ActionInitialization();
    virtual ~TB1106ActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

    
