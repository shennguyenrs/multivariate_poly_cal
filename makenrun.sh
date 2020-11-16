#! /bin/bash

# Generate output file
g++ $1.cpp $2.cpp -o $1

# Update tags file
# If ctags-exuberant is installed
check=$(dpkg -S `which ctags-exuberant` 2> /dev/null | grep "ctags-exuberant" | wc -l)

if [ "$check" -ge 1 ]; then
    ctags --recurse=yes --exclude=$1 --exclude=README.md
fi

# Open file
if [ -f "./$1" ]; then
    ./$1
fi
