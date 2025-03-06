#!/bin/bash

for f in *.in; do
	echo -n "Plik $f "
	if diff "${f%in}out" <(sort -g "$f") > /dev/null 2>&1; then
		echo "zostal posortowany."
	else
		echo "nie zostal posortowany."
	fi
done
