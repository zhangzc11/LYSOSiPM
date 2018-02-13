
#ifndef LYSOSiPMRunAction_h
#define LYSOSiPMRunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"

class LYSOSiPMEventAction;
class G4Run;

/// Run action class
///
/// It accumulates statistic and computes dispersion of the energy deposit 
/// and track lengths of charged particles with use of analysis tools:
/// H1D histograms are created in BeginOfRunAction() for the following 
/// physics quantities:
/// - Edep in absorber
/// - Edep in gap
/// - Track length in absorber
/// - Track length in gap
/// The same values are also saved in the ntuple.
/// The histograms and ntuple are saved in the output file in a format
/// accoring to a selected technology in LYSOSiPMAnalysis.hh.
///
/// In EndOfRunAction(), the accumulated statistic and computed 
/// dispersion is printed.
///

class LYSOSiPMRunAction : public G4UserRunAction
{
  public:
    LYSOSiPMRunAction(LYSOSiPMEventAction* eventAction);
    virtual ~LYSOSiPMRunAction();

    virtual void BeginOfRunAction(const G4Run*);
    virtual void   EndOfRunAction(const G4Run*);
  private:
	LYSOSiPMEventAction* fEventAction;	
};



#endif

