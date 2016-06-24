
/*
 *  See header file for a description of this class.
 *
 *  \author G. Cerminara - CERN
 */

#include "Calibration/TkAlCaRecoProducers/plugins/PCLMetadataWriter.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CondCore/DBOutputService/interface/PoolDBOutputService.h"
#include "FWCore/MessageLogger/interface/JobReport.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "CondFormats/DataRecord/interface/DropBoxMetadataRcd.h"
#include "CondFormats/Common/interface/DropBoxMetadata.h"


PCLMetadataWriter::PCLMetadataWriter(const edm::ParameterSet& pSet) :
  readFromDB_(pSet.getParameter<bool>("readFromDB"))
{
  auto recordsToMap =
    pSet.getParameter<std::vector<edm::ParameterSet> >("recordsToMap");
  for(const auto& recordPset: recordsToMap) {
    auto record = recordPset.getUntrackedParameter<std::string>("record");
    std::map<std::string, std::string> jrInfo;
    if(!readFromDB_) {
      auto paramKeys = recordPset.getParameterNames();
      for(const auto& key: paramKeys) {
        jrInfo["Source"] = "AlcaHarvesting";
        jrInfo["FileClass"] = "ALCA";
        if(key != "record") {
          jrInfo[key] = recordPset.getUntrackedParameter<std::string>(key);
        }
      }
    }
    recordMap_[record] = jrInfo;
  }
}


PCLMetadataWriter::~PCLMetadataWriter()
{
}


void PCLMetadataWriter::analyze(const edm::Event&, const edm::EventSetup&)
{
}


void PCLMetadataWriter::beginRun(const edm::Run&, const edm::EventSetup&)
{
}


void PCLMetadataWriter::endRun(const edm::Run&, const edm::EventSetup& iSetup)
{
  const DropBoxMetadata* metadata{nullptr};

  if(readFromDB_) {
    // Read the objects
    edm::ESHandle<DropBoxMetadata> mdPayload;
    iSetup.get<DropBoxMetadataRcd>().get(mdPayload);

    metadata = mdPayload.product();
  }

  // get the PoolDBOutputService
  edm::Service<cond::service::PoolDBOutputService> poolDbService;
  if(poolDbService.isAvailable() ) {
    edm::Service<edm::JobReport> jr;
    if (jr.isAvailable()) {
      // the filename is unique for all records
      auto filename = poolDbService->session().connectionString();

      // loop over all records
      for(const auto& recordAndMap: recordMap_) {
        auto record = recordAndMap.first;
        // this is the map of metadata that we write in the JR
        auto jrInfo = recordAndMap.second;
        if(readFromDB_) {
          if(metadata->knowsRecord(record)) {
            jrInfo = metadata->getRecordParameters(record).getParameterMap();
          }
        }
        jrInfo["inputtag"] = poolDbService->tag(record);

        // actually write in the job report
        jr->reportAnalysisFile(filename, jrInfo);
      }
    }
  }
}


#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE(PCLMetadataWriter);
