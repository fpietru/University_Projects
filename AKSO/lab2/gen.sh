#!/bin/bash

N=$1
M=$2

for ((i=0; i<N; i++)); do
	((x = $RANDOM % $M))
	echo $x 
done

