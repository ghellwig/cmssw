/** \class SurveyAlignmentAlgorithm
 *
 *  Alignment of Silicon Pixel Detector with survey constraint.
 *
 *  $Date: 2010/09/10 11:53:18 $
 *  $Revision: 1.4 $
 *  \author Chung Khim Lae
 */

#ifndef Alignment_SurveyAnalysis_SurveyAlignmentAlgorithm_h
#define Alignment_SurveyAnalysis_SurveyAlignmentAlgorithm_h

#include "Alignment/CommonAlignmentAlgorithm/interface/AlignmentAlgorithmBase.h"
#include "Alignment/CommonAlignmentAlgorithm/interface/AlignmentParameterStore.h"

namespace edm { class ParameterSet; class EventSetup; }

class AlignableMuon;
class AlignableTracker;
class AlignableExtras;

class SurveyAlignmentAlgorithm : public AlignmentAlgorithmBase
{
  public:

  SurveyAlignmentAlgorithm(const edm::ParameterSet&);

  /// call at start of job
  virtual void initialize(const edm::EventSetup&,
                          AlignableTracker*,
                          AlignableMuon*,
                          AlignableExtras*,
                          std::shared_ptr<AlignmentParameterStore>) override;

  /// call at end of job
  virtual void terminate(const edm::EventSetup& iSetup) override {}

  /// run for every event
  virtual void run(const edm::EventSetup&,
		   const AlignmentAlgorithmBase::EventInfo&) override {}


  private:

  const std::string theOutfile;
  const unsigned int theIterations;
  const std::vector<std::string> theLevels;
};

#endif
