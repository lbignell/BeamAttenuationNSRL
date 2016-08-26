#ifndef RunAction_hh
#define RunAction_hh 1
//
#include "G4UserRunAction.hh"
#include "G4UnitsTable.hh"
#include "DetectorConstruction.hh"

#include "TH1D.h"
#include <fstream>
#include "TTree.h"

//declare the DetectorConstruction class as we will define a pointer later
class DetectorConstruction;
class TFile;

//needed for using standard libraries
using namespace std;

//run action class, carries out tasks at the begin and end of each run
//the concept of a run incorporates a fixed geometry, fixed beam conditions, simulation of number of primaries
//begins with /run/beamOn command and finishes with tracking of last secondary to zero energy 

class RunAction : public G4UserRunAction {
//
public:
//run action class needs pointer ot the detector construction class in order to get details of the readout geometry
//accepts pointer to detector construction class

  RunAction(DetectorConstruction*);
  ~RunAction();

    //

private:
//an ofstream to access the output file
  ofstream outfile;

  TH1D *EdepInAbs;
  TFile* RootOP;

//local pointer for detector construction class
  DetectorConstruction* myDC;

public:

//note argument of these methods is a pointer to a G4Run object
  void BeginOfRunAction(const G4Run*);
  void EndOfRunAction(const G4Run*);

  void TallyEdep(const G4double);

};

#endif
