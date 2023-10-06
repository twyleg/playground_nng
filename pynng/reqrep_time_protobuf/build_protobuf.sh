#!/bin/bash
SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

protoc -I=${SCRIPT_DIR}/idl --python_out=${SCRIPT_DIR} ${SCRIPT_DIR}/idl/time.proto