#!/bin/bash

ruby main.rb

g++ -I./3rdparty/ELFIO \
result/static/main.cpp result/static/op.cpp result/generated/decode.cpp result/generated/execute.cpp \
-o sim
