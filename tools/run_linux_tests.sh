#!/bin/bash
rm build/Release-LinuxTests/Vic2ToHoi4ConverterTests
cmake -H. -Bbuild/linux-intermediate && cmake --build ./build/linux-intermediate --target Vic2ToHoi4Converter Vic2ToHoi4ConverterTests -- -j40
(
cd build/Release-LinuxTests
./Vic2ToHoi4ConverterTests
)