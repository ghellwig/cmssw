#ifndef Alignment_TrackerAlignment_TrackerSystematicMisalignments_h
#define Alignment_TrackerAlignment_TrackerSystematicMisalignments_h

/** \class TrackerSystematicMisalignments
 *
 *  Class to misaligned tracker from DB.
 *
 *  $Date: 2012/06/13 09:24:50 $
 *  $Revision: 1.5 $
 *  \author Chung Khim Lae
 */

#include <unordered_map>
#include <unordered_set>

// user include files

#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"


class AlignableSurface;
class Alignments;

namespace edm {
  class ParameterSet;
}

class TrackerSystematicMisalignments: public edm::EDAnalyzer
{
public:

  TrackerSystematicMisalignments(const edm::ParameterSet&);

  /// Read ideal tracker geometry from DB
  virtual void beginJob();

  virtual void analyze(const edm::Event&, const edm::EventSetup&);

private:

  void applySystematicMisalignment( Alignable* );
  //align::GlobalVector findSystematicMis( align::PositionType );
  align::GlobalVector findSystematicMis( const align::PositionType&, const bool blindToZ, const bool blindToR );

  std::unordered_map<int, std::unordered_set<unsigned int> > convertToSubDetIds(const std::vector<std::string>& detIdStrings);
  bool startsWith(const std::string& haystack, const std::string& needle);
  bool selectedForMisalignment(const Alignable*);

  AlignableTracker* theAlignableTracker;



  // configurables needed for the systematic misalignment
  bool m_fromDBGeom;

  double m_radialEpsilon;
  double m_telescopeEpsilon;
  double m_layerRotEpsilon;
  double m_bowingEpsilon;
  double m_zExpEpsilon;
  double m_twistEpsilon;
  double m_ellipticalEpsilon;
  double m_skewEpsilon;
  double m_sagittaEpsilon;
  double m_xShift;
  double m_yShift;
  double m_zShift;

  //misalignment phases
  double m_ellipticalDelta;
  double m_skewDelta;
  double m_sagittaDelta;

  // flag to steer suppression of blind movements
  bool suppressBlindMvmts;

  // flag for old z behaviour, version <= 1.5
  bool oldMinusZconvention;

  // subdetectors to which the alignment is applied
  const std::unordered_map<int, std::unordered_set<unsigned int> > applyToSubdetectors_;
};

#endif
