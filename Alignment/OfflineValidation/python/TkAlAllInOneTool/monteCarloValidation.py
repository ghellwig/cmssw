import os
import configTemplates
import globalDictionaries
from dataset import Dataset
from genericValidation import GenericValidationData
from helperFunctions import replaceByMap
from TkAlExceptions import AllInOneError


class MonteCarloValidation(GenericValidationData):
    def __init__(self, valName, alignment, config):
        GenericValidationData.__init__(self, valName, alignment, config,
                                       "mcValidate")

    def createConfiguration(self, path ):
        cfgName = "TkAlMcValidate.%s.%s_cfg.py"%(self.name,
                                                 self.alignmentToValidate.name)
        repMap = self.getRepMap()
        cfgs = {cfgName: configTemplates.mcValidateTemplate}
        self.filesToCompare[GenericValidationData.defaultReferenceName] = \
            repMap["resultFile"]
        GenericValidationData.createConfiguration(self, cfgs, path, repMap = repMap)

    def createScript(self, path):
        scriptName = "TkAlMcValidate.%s.%s.sh"%(self.name,
                                                self.alignmentToValidate.name)
        repMap = self.getRepMap()
        repMap["CommandLine"]=""
        for cfg in self.configFiles:
            repMap["CommandLine"] += \
                repMap["CommandLineTemplate"]%{"cfgFile":cfg, "postProcess":"" }

        scripts = {scriptName: configTemplates.scriptTemplate}
        return GenericValidationData.createScript(self, scripts, path, repMap = repMap)

    def createCrabCfg(self, path, crabCfgBaseName = "TkAlMcValidate"):
        return GenericValidationData.createCrabCfg(self, path,
                                                   crabCfgBaseName)

    def getRepMap( self, alignment = None ):
        repMap = GenericValidationData.getRepMap(self, alignment)
        repMap.update({
            "resultFile": replaceByMap(("/store/caf/user/$USER/.oO[eosdir]Oo."
                                        "/McValidation_"
                                        + self.name +
                                        "_.oO[name]Oo..root"), repMap ),
            "outputFile": replaceByMap(("McValidation_"
                                        + self.name +
                                        "_.oO[name]Oo..root"), repMap ),
            "nEvents": self.general["maxevents"]
            })
        repMap["outputFile"] = os.path.expandvars( repMap["outputFile"] )
        repMap["resultFile"] = os.path.expandvars( repMap["resultFile"] )
        return repMap

