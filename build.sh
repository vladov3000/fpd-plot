#!/bin/sh

g++ -std=c++11 -I/usr/local/Cellar/root/6.20.02/include/root/ -L `root-config --incdir --libs` -o plotter.cpp.out ./plotter.cpp