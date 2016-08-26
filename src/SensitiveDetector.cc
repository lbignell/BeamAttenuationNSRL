#include "SensitiveDetector.hh"
#include "G4Step.hh"

#include "G4HCofThisEvent.hh"
#include "G4TouchableHistory.hh"
#include "G4SystemOfUnits.hh"

#include "RunAction.hh"
#include "G4RunManager.hh"
#include "G4Run.hh"
#include "G4SteppingManager.hh"
#include <iterator>
#include "G4TrackVector.hh"
#include "G4StepPoint.hh"
#include "G4Track.hh"

SensitiveDetector::SensitiveDetector(G4String name) : G4VSensitiveDetector(name){
  //runnum = 0;
  name = "abs_log";
}

SensitiveDetector::~SensitiveDetector(){;}

/*This method is invoked at the beginning of each event. The argument of this method is an object of the G4HCofThisEvent class. Hits collections, where hits produced in this particular event are stored, can be associated to the G4HCofThisEvent object in this method. The hits collections associated with the G4HCofThisEvent  object during this method can be used for ``during the event processing'' digitization.*/
void SensitiveDetector::Initialize(G4HCofThisEvent* HCE){

  Edep = 0;

}

/*This method is invoked by G4SteppingManager when a step is composed in the G4LogicalVolume which has the pointer to this sensitive detector. The first argument of this method is a G4Step  object of the current step. The second argument is a G4TouchableHistory object for the ``Readout geometry'' described in the next section. The second argument is NULL for the case ``Readout geometry'' is not assigned to this sensitive detector. In this method, one or more G4VHit objects should be constructed if the current step is meaningful for your detector.*/
G4bool SensitiveDetector::ProcessHits(G4Step* theStep, G4TouchableHistory*){

  
  //Need to add in alternate Edep collection, simple Edep per step.
  Edep += theStep->GetTotalEnergyDeposit()*MeV;

  return true;  
}


/*This method is invoked at the end of each event. The argument of this method is the same object as the previous method. Hits collections occasionally created in your sensitive detector can be associated to the G4HCofThisEvent object.*/
void SensitiveDetector::EndOfEvent(G4HCofThisEvent*)
{
  //only need to do anything if there were some interactions.
  if(Edep!=0){
    //get run action pointer
    RunAction* myRunAction =
      (RunAction*)(G4RunManager::GetRunManager()->GetUserRunAction());
    
    if(myRunAction){
      //Tally unquenched Edeps.
      //G4cout << "Calling RunAction->TallyEdepNoQuench" << G4endl;
      myRunAction->TallyEdep(Edep);

    }
  }
}
