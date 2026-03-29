#!/bin/bash
cmake -H. -B ./build/Release-Win -DCMAKE_TOOLCHAIN_FILE=cmake/mingw-toolchain.cmake -DBUILD_FRONTEND=OFF
cmake --build ./build/Release-Win --target Vic2ToHoi4Converter