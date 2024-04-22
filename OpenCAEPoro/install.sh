#!/bin/sh

sudo apt -y install p7zip-full

rm -rf examples
7za x examples.7z -o/$PWD/examples

mkdir build
cd build
cmake .. -DFASP_DIR=$PWD/../../../NLA/faspsolver_install/ -DCMAKE_INSTALL_PREFIX=$PWD/../../opencaeporo_install
make -j4
make install

