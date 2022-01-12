#!/bin/bash
# install denseflow
set -e

ROOTDIR=${ZZROOT:-$HOME/app}
NAME="denseflow"
echo $NAME will be installed in "$ROOTDIR"
echo Dependency: boost, opencv

mkdir -p build
cd build
cmake -DCMAKE_INSTALL_PREFIX="$ROOTDIR" ..
make -j"$(nproc)" && make install

echo $NAME installed on "$ROOTDIR"
