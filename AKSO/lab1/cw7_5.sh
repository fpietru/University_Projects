#!/bin/bash

# Zmodyfikuj skrypt z poprzedniego ćwiczenia,
# aby wypisywał nazwy wszystkich programów (plików wykonywalnych),
# które użytkownik może uruchomić.

dirs=( "$@" )

if (($# == 0)); then
    dirs+=('.')
fi

for dir in "${dirs[@]}"; do
    # echo "${dir}"
    if [ -d ${dir} ]; then
        echo "Listing all regular, nonempty and exutable files from directory: ${dir}"
        echo "$(find ${dir} -type f -executable -not -empty)"
    else
        echo "${dir} is not a directory"
    fi
done