#!/bin/bash
cmake -H. -Bbuild && cmake --build ./build -- -j40 && cd Release-Tests && ./Vic2ToHoi4ConverterTests && cd ..
