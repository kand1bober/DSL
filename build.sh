#!/bin/bash

g++ result/static/main.cpp result/static/op.cpp result/generated/decode.cpp result/generated/execute.cpp \
-I./3rdparty/ELFIO -o sim
