#!/bin/bash
rm -rf build/
cmake -H. -Bbuild -DCOVERAGE=TRUE && cmake --build ./build --target Vic2ToHoi4Converter Vic2ToHoi4ConverterTests -- -j40
cd build || exit
cd Release-LinuxTests || exit
./Vic2ToHoi4ConverterTests
cd .. || exit
make gcov
make lcov