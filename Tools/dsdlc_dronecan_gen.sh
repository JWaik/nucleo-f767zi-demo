#!/bin/bash

if [ "$1" == "Debug" ] || [ "$1" == "Release" ]; then
    echo "Generate DSDL for '"$1"' build type"
else
    echo "Invalid argument: $1"
    echo "Usage: ./dsdlc_dronecan_gen.sh <Debug|Release>"
    exit 1
fi

# Get the workspace directory and script path
WORKSPACE_DIR=$(cd $(dirname "$(readlink -f "$0")")/.. && pwd)
SCRIPT_PATH=${WORKSPACE_DIR}/modules/DroneCAN/dronecan_dsdlc/dronecan_dsdlc.py
# echo $WORKSPACE_DIR
# echo $SCRIPT_PATH

# Generate DSDL type in C
# python script usage: python dronecan_dsdlc.py -O <output directory> <list of namespace dirs>
python ${SCRIPT_PATH} -O "${WORKSPACE_DIR}"/App/DroneCAN/dsdlc_generated \
                         "${WORKSPACE_DIR}"/modules/DroneCAN/DSDL/uavcan \
                         "${WORKSPACE_DIR}"/modules/DroneCAN/DSDL/dronecan \
                         "${WORKSPACE_DIR}"/modules/DroneCAN/DSDL/com \
                         "${WORKSPACE_DIR}"/modules/DroneCAN/DSDL/ardupilot

