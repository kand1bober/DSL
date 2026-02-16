#!/bin/bash

g++ -std=c++17 \
-I./result -I./3rdparty/ELFIO \
result/tests/execute_test.cpp result/static/op.cpp result/generated/execute.cpp result/generated/decode.cpp \
-o exec_test
