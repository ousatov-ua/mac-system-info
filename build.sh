#!/bin/sh

brew tap nlohmann/json

brew install nlohmann-json@3.9

brew install ncurses@6.2

cmake .
make all
