#ifndef PCLMetadataWriter_H
#define PCLMetadataWriter_H

/** \class PCLMetadataWriter
 *  No description available.
 *
 *  \author G. Cerminara - CERN
 */

#include "FWCore/Framework/interface/one/EDAnalyzer.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include <vector>
#include <string>


class PCLMetadataWriter :
  public edm::one::EDAnalyzer<edm::one::WatchRuns>
{
public:
  /// Constructor
  PCLMetadataWriter(const edm::ParameterSet&);

  /// Destructor
  virtual ~PCLMetadataWriter();

  // Operations
  virtual void analyze  (const edm::Event&, const edm::EventSetup&);
  virtual void beginRun (const edm::Run&,   const edm::EventSetup&);
  virtual void endRun   (const edm::Run&,   const edm::EventSetup&);

private:
  const bool readFromDB_;
  std::map<std::string, std::map<std::string, std::string> > recordMap_;
};
#endif

