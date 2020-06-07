#!/bin/bash
echo "Version Number?"
read version
rm -rf "Vic2ToHoI4-$version"
rm -rf "Vic2ToHoI4-$version.tar.bz2"

rm -rf build
rm -rf Release-Linux
rm -rf Release-Tests
cmake -H. -Bbuild
cmake --build ./build -- -j3
cp -rf "Release-Linux" "Vic2ToHoI4-$version"

tar -cjf "Vic2ToHoI4-$version.tar.bz2" "Vic2ToHoI4-$version"