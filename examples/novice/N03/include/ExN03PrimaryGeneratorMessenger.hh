// This code implementation is the intellectual property of
// the RD44 GEANT4 collaboration.
//
// By copying, distributing or modifying the Program (or any work
// based on the Program) you indicate your acceptance of this statement,
// and all its terms.
//
// $Id: ExN03PrimaryGeneratorMessenger.hh,v 2.3 1998/10/09 15:48:01 japost Exp $
// GEANT4 tag $Name: geant4-00 $
//
// 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#ifndef ExN03PrimaryGeneratorMessenger_h
#define ExN03PrimaryGeneratorMessenger_h 1

#include "G4UImessenger.hh"
#include "globals.hh"

class ExN03PrimaryGeneratorAction;
class G4UIcmdWithAString;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

class ExN03PrimaryGeneratorMessenger: public G4UImessenger
{
  public:
    ExN03PrimaryGeneratorMessenger(ExN03PrimaryGeneratorAction*);
   ~ExN03PrimaryGeneratorMessenger();
    
    void SetNewValue(G4UIcommand*, G4String);
    
  private:
    ExN03PrimaryGeneratorAction* ExN03Action; 
    G4UIcmdWithAString*          RndmCmd;
};

#endif
