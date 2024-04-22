#!/bin/sh

sudo apt -y install p7zip-full
sudo apt -y install libblas-dev
sudo apt -y install liblapack-dev

rm -rf examples
7za x examples.7z -o/$PWD/examples

mkdir build
cd build
cmake .. -DFASP_DIR=$PWD/../../../NLA/faspsolver_install/ -DCMAKE_INSTALL_PREFIX=$PWD/../../opencaeporo_install
make -j4
make install

