#!/bin/bash

c_files=$(find . -maxdepth 1 -type f -name "*.c")


for file in $c_files
do
    gcc -c "$file"
done

ar rc liball.a *.o
ranlib liball.a
rm -f *.o

