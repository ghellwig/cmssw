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
    echo ${item}.h
    diff ${ref_traj_path}/interface/${item}.h ${claus_dev_path}/${item}.h
    echo ${item}.cpp
    diff ${ref_traj_path}/src/${item}.cc ${claus_dev_path}/${item}.cpp
done
