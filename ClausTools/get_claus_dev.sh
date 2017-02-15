#!/bin/bash

if [[ ${1} = "-a" ]]
then
    klog.krb5 -principal ghellwig -cell desy.de -k DESY.DE
    kinit ghellwig@CERN.CH
fi

ref_traj_path=${CMSSW_BASE}/src/Alignment/ReferenceTrajectories/
claus_dev_path=/afs/desy.de/user/k/kleinwrt/cms/gbleigen/trunk/

items=(BorderedBandMatrix GblData GblPoint GblTrajectory MilleBinary VMatrix)

for item in "${items[@]}"
do
    cp ${claus_dev_path}/${item}.h ${ref_traj_path}/interface/${item}.h
    cp ${claus_dev_path}/${item}.cpp ${ref_traj_path}/src/${item}.cc
    for incl in "${items[@]}"
    do
	sed -i "s|#include \"${incl}.h\"|#include \"Alignment/ReferenceTrajectories/interface/${incl}.h\"|" ${ref_traj_path}/interface/${item}.h
	sed -i "s|#include \"${incl}.h\"|#include \"Alignment/ReferenceTrajectories/interface/${incl}.h\"|" ${ref_traj_path}/src/${item}.cc
    done
done
