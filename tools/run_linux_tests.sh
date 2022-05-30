#!/bin/bash
rm Release-Tests/Vic2ToHoi4ConverterTests
cmake -H. -Bbuild/linux-intermediate && cmake --build ./build/linux-intermediate -- -j40
(
cd Release-Tests
./Vic2ToHoi4ConverterTests
)