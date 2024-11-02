#!/bin/bash

gcc -I ./src -o pong ping_pong.c ../raylib/raylib-5.0/src/libraylib.a -lm -lGL -lpthread -ldl


