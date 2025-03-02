#!/bin/bash

# Napisz skrypt, który wypisze swój największy parametr.
# Zakładamy, że parametry są liczbami całkowitymi (mogą być ujemne).

dirs=("$@")
mx=$1

for dir in "${dirs[@]}"; do
    echo ${dir}
    [ ${mx} -le ${dir} ] && mx=${dir} 
done

echo "Biggest parameter provided is ${mx}"