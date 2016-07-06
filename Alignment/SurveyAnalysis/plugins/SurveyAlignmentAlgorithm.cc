#include "Alignment/CommonAlignment/interface/AlignableObjectId.h"
#include "Alignment/SurveyAnalysis/interface/SurveyAlignmentSensor.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "SurveyAlignmentAlgorithm.h"

SurveyAlignmentAlgorithm::SurveyAlignmentAlgorithm(const edm::ParameterSet& cfg):
  AlignmentAlgorithmBase(cfg),
  theOutfile(cfg.getParameter<std::string>("outfile")),
  theIterations(cfg.getParameter<unsigned int>("nIteration")),
  theLevels(cfg.getParameter< std::vector<std::string> >("levels"))
{
}

void SurveyAlignmentAlgorithm::initialize(const edm::EventSetup&,
                                          const std::shared_ptr<AlignableTracker>&,
                                          const std::shared_ptr<AlignableMuon>&,
                                          const std::shared_ptr<AlignableExtras>&,
                                          const std::shared_ptr<AlignmentParameterStore>& store)
{
  std::vector<align::StructureType> levels;

  for (unsigned int l = 0; l < theLevels.size(); ++l)
  {
    levels.push_back(AlignableObjectId::stringToId(theLevels[l].c_str()));
  }

  SurveyAlignmentSensor align(store->alignables(), levels);

  align.iterate(theIterations, theOutfile, true);
}

// Plug in to framework

#include "Alignment/CommonAlignmentAlgorithm/interface/AlignmentAlgorithmPluginFactory.h"

DEFINE_EDM_PLUGIN(AlignmentAlgorithmPluginFactory, SurveyAlignmentAlgorithm, "SurveyAlignmentAlgorithm");
