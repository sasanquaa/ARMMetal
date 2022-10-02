#!/bin/bash

cmake -BBuild -S . -DCMAKE_EXPORT_COMPILE_COMMANDS=TRUE &&
cmake --build Build/
