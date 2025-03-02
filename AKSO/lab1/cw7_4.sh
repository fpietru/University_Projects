#!/bin/bash

# Napisz skrypt, który wyświetla nazwy wszystkich niepustych plików
# zwykłych z katalogów przekazanych jako parametry lub z katalogu
# bieżącego,jeżeli nie dostanie parametrów.
# Skrypt powinien sprawdzać poprawność przekazanych parametrów. 

dirs=( "$@" )

if (($# == 0)); then
    dirs+=('.')
fi

for dir in "${dirs[@]}"; do
    # echo "${dir}"
    if [ -d ${dir} ]; then
        echo "Listing all regular, nonempty files from directory: ${dir}"
        echo "$(find ${dir} -type f -not -empty)"
    else
        echo "${dir} is not a directory"
    fi
done
