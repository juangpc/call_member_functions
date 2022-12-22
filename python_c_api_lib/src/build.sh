#!/bin/bash

SCRIPT_PATH="$0"
ROOT_FOLDER=""
ROOT_FOLDER="$(cd -- "$(dirname $SCRIPT_PATH)"/.. && pwd)"

echo $SCRIPT_PATH
echo $ROOT_FOLDER

BUILD_FOLDER=$ROOT_FOLDER/build
SRC_FOLDER=$ROOT_FOLDER/src

#while
#  sleep 1;
#do
  rm -fr $BUILD_FOLDER
  cmake -S $SRC_FOLDER -B $BUILD_FOLDER
  # cmake --build $BUILD_FOLDER
  cp $BUILD_FOLDER/compile_commands.json $SRC_FOLDER
#done

#call application
# build/app/hellos

# python src/python/callbacks.py

