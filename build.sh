#!/bin/bash

cmake -Bbuild -S . -DCMAKE_EXPORT_COMPILE_COMMANDS=TRUE &&
cmake --build build/
