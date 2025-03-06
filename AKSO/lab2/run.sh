#!/bin/bash

L=$1
N=$2
M=$3
dirIn="in"
dirOut="out"

echo "Tworze katalog $dirIn"
[ -d $dirIn ] && rm -rf $dirIn
mkdir $dirIn

echo "Tworze katalog $dirIN"
[ -d $dirIn ] && rm -rf $dirIn
mkdir $dirIn

for ((i=1; i<=L; i++)); do
    fileIn="./$dirIn/$i.in"
    fileOut="./$dirOut/$i.out"
    touch $fileIn
    for ((j=0; j<N; j++)); do
	    ((x = $RANDOM % $M))
    done 
done

done


echo "Wypelniam go plikami testowymi"
for ((i=1; i<=L; i++)); do
    ./gen.sh $N $M > ./$dirIn/$i.in 
done


echo "Generuje pliki wyjsciowe"
for ((i=1; i<=L; i++)); do
    sort -g < ./$dirIn/$i.in > ./$dirOut/$i.out
done 