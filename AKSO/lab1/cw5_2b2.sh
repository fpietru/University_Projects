#!/bin/bash

if sort --check=silent $1
then echo "File $1 is sorted"
else echo "File $1 is not sorted"
fi
