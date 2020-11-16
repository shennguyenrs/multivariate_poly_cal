#! /bin/bash

# Generate output file
g++ $1.cpp $2.cpp -o $1
ctags --recurse=yes --exclude=$1 --exclude=README.md
./$1
