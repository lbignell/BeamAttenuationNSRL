//
#include "RunAction.hh"
#include "G4Run.hh"
#include "G4SDManager.hh"
//
#include "DetectorConstruction.hh"
#include "G4VSensitiveDetector.hh"
#include <math.h>
#include "TH1D.h"
#include "TFile.h"
#include <sstream>

RunAction::RunAction(DetectorConstruction* DC){
  //
  
  //take the DetectorConstruction pointer given when this object is created (in main) and copy to local member
  myDC = DC;
  //
  
}

RunAction::~RunAction(){

}

void RunAction::BeginOfRunAction(const G4Run* aRun){
  
  //Arguments:Name of file,type of rewrite option(UPDATE means append),comments
  RootOP = new TFile("EdepNoQuench.root","RECREATE","LS Sim Output");

  //arguments: Name, Title, number of bins, lower level range, upper
  //level range.
  //
  //All Energies are passed in MeV.
  //
  EdepInAbs =
    new TH1D("Edep in Absorbing material",
	     "Energy Deposition in the absorber (MeV)",
	     2000000,0.,2000.);

}



void RunAction::TallyEdep(const G4double thisEdep){

  //Fill ROOT histogram
  EdepInAbs->Fill(thisEdep);

}


//task to be carried out at the end of the run
void RunAction::EndOfRunAction(const G4Run* aRun){
  //get the number of primary particles being simulated for this run
  //G4double NumberOfEvents = aRun->GetNumberOfEventToBeProcessed();
 
  // Name the histograms
  EdepInAbs->SetName("Edep");
  //EdepInAbs->Scale(1/NumberOfEvents);
  EdepInAbs->Write();

  RootOP->Write();
  RootOP->Close();
  

}
