#ifndef Alignment_CommonAlignmentAlgorithm_AlignmentParameterBuilder_h
#define Alignment_CommonAlignmentAlgorithm_AlignmentParameterBuilder_h

/** \class AlignmentParameterBuilder
 *
 *  Build Alignment Parameter Structure 
 *
 *  $Date: 2010/10/26 20:01:51 $
 *  $Revision: 1.11 $
 *  (last update by $Author: flucke $)
 */

#include <memory>

#include "Alignment/CommonAlignment/interface/Utilities.h"
#include "Alignment/CommonAlignmentParametrization/interface/AlignmentParametersFactory.h"
#include "Alignment/CommonAlignment/interface/AlignableExtras.h"
#include "Alignment/TrackerAlignment/interface/AlignableTracker.h"
#include "Alignment/MuonAlignment/interface/AlignableMuon.h"

namespace edm {
  class ParameterSet;
}
class AlignmentParameters;
class TrackerTopology;

class AlignmentParameterBuilder 
{
public:
  /// Constructor from tracker only
  explicit AlignmentParameterBuilder(const std::shared_ptr<AlignableTracker>& alignableTracker,
                                     const std::shared_ptr<AlignableExtras>& alignableExtras);

  /// Constructor from tracker and muon
  AlignmentParameterBuilder(const std::shared_ptr<AlignableTracker>& alignableTracker,
                            const std::shared_ptr<AlignableMuon>& alignableMuon,
                            const std::shared_ptr<AlignableExtras>& alignableExtras);

  /// Constructor adding selections by passing the ParameterSet named 'AlignmentParameterSelector'
  /// (expected in pSet) to addSelections(..)
  AlignmentParameterBuilder(const std::shared_ptr<AlignableTracker>& alignableTracker,
                            const std::shared_ptr<AlignableExtras>& alignableExtras,
                            const edm::ParameterSet &pSet );

  /// Constructor from tracker and muon, plus selection
  AlignmentParameterBuilder(const std::shared_ptr<AlignableTracker>& alignableTracker,
                            const std::shared_ptr<AlignableMuon>& alignableMuon,
                            const std::shared_ptr<AlignableExtras>& alignableExtras,
                            const edm::ParameterSet &pSet);


  /// destructor 
  virtual ~AlignmentParameterBuilder() {};
  /// master initialisation method, PSet must have form as constructor wants it 
  void addAllSelections(const edm::ParameterSet &pSet);

  /// Add selections of Alignables, using AlignmenParameterSelector::addSelections.
  /// For each Alignable, AlignmentParameters of type parType will be attached
  /// using the selection of active parameters done in AlignmenParameterSelector,
  /// e.g. for RigidBody a selection string '11100' selects the degrees of freedom in
  /// (x,y,z), but not (alpha,beta,gamma).
  /// Returns number of added selections 
  unsigned int addSelections(const edm::ParameterSet &pset,
			     AlignmentParametersFactory::ParametersType parType);

  /// Add arbitrary selection of Alignables, return number of higher level Alignables
  unsigned int add(const align::Alignables &alignables,
		   AlignmentParametersFactory::ParametersType parType,
		   const std::vector<bool> &sel);
  /// Add a single Alignable, true if it is higher level, false if it is an AlignableDet 
  bool add(Alignable *alignable, AlignmentParametersFactory::ParametersType parType,
	   const std::vector<bool> &sel);

  /// Get list of alignables for which AlignmentParameters are built 
  const align::Alignables& alignables() const { return theAlignables; };

  /// Remove n Alignables from list 
  void fixAlignables( int n );

  /// Alignable tracker   
  std::shared_ptr<const AlignableTracker> alignableTracker() const;

private:
  /// First remove all spaces (' ') from char selection 'paramSelChar' (coming
  /// from ParameterSelector) and then convert the selection to bool (for AlignmentParameters).
  /// True if (after removal of spaces) anything else than 0 and 1 is found in vector<char>.
  bool decodeParamSel(std::vector<char> &paramSelChar, std::vector<bool> &result) const;
  /// add SelectionUserVariables corresponding to fullSel 
  bool addFullParamSel(AlignmentParameters *aliPar, const std::vector<char> &fullSel) const;

  // data members

  /// Vector of alignables 
  align::Alignables theAlignables;

  /// Alignable tracker   
  std::shared_ptr<AlignableTracker> theAlignableTracker;

  /// Alignable muon
  std::shared_ptr<AlignableMuon> theAlignableMuon;
  
  /// extra Alignables
  std::shared_ptr<AlignableExtras> theAlignableExtras;
};

#endif
