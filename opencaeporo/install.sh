#!/bin/sh

sudo apt update
sudo apt -y install p7zip-full
sudo apt -y install libblas-dev
sudo apt -y install liblapack-dev
sudo apt -y install cmake
sudo apt -y install make
sudo apt -y install gcc g++

rm -rf examples
7za x examples.7z -o/$PWD/examples

mkdir build
cd build
cmake .. -DFASP_DIR=$PWD/../../../NLA/install/faspsolver_install/ -DCMAKE_INSTALL_PREFIX=$PWD/../../install/opencaeporo_install
make -j4
make install

