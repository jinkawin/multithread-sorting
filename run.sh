#!/bin/bash
g++ -std=c++17 ./src/index.cpp -pthread -o ./.src/index && ./.src/index
exit 0