// This code implementation is the intellectual property of
// the RD44 GEANT4 collaboration.
//
// By copying, distributing or modifying the Program (or any work
// based on the Program) you indicate your acceptance of this statement,
// and all its terms.
//
// $Id: G4DAWNFILE.hh,v 2.1 1998/11/06 13:41:37 allison Exp $
// GEANT4 tag $Name: geant4-00 $
//
// Satoshi TANAKA
// DAWNFILE driver factory.

//=================//
#if defined (G4VIS_BUILD_DAWNFILE_DRIVER) || defined (G4VIS_USE_DAWNFILE)
//=================//

#ifndef G4DAWNFILE_HH
#define G4DAWNFILE_HH

#include "G4VGraphicsSystem.hh"

	//----- prototype
class G4VScene   ;

	//----------------------------//
	//----- class G4DAWNFILE -----// 
	//----------------------------//
class G4DAWNFILE: public G4VGraphicsSystem {

public:
  G4DAWNFILE ();
  ~G4DAWNFILE ();
  G4VScene* CreateScene (const G4String& name = "");
  G4VView*  CreateView  (G4VScene&, const G4String& name = "");

private:


};

#endif
#endif 