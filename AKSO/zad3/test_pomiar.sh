#!/bin/bash
# Autor: Olaf Targowski WspĂłĹautor Stefan Twarowski 
# Przeznaczenie: pomiar czasu zadania 3 z AKSO (freverse)
set -euo pipefail
[ "$#" = "1" ] || { echo "SposĂłb uĹźycia: test_pomiar.sh ./freverse"; exit 123; }
program="$1"

if [ -f bajty ] && [[ $(wc -c < bajty) -gt 4294967296 ]]; then
    echo "UĹźywam wczeĹniej wygenerowanych losowych bajtĂłw z pliku 'bajty'."
    echo "JeĹźeli testowany program jest bĹÄdny, a uĹźyto w tym samym folderze test.sh,"
    echo "to naleĹźy usunÄÄ pliki 'bajty' i 'bajtyrev'."
else
    echo "GenerujÄÂ losowe bajty..."
    echo "sus mogus" > bajty
    dd if=/dev/urandom of=bajty oflag=append conv=notrunc bs=1M count=4096 status=progress
    echo "123567890" >> bajty
    echo "Wygenerowano."
fi

wyr_real=""
wyr_user=""
ile=4
for i in $(seq 1 $ile); do
    /bin/time -o _res123 -f "%e %U" $program bajty
    times=$(cat _res123)
    real=$(echo $times | cut -d' ' -f1)
    user=$(echo $times | cut -d' ' -f2)
    wyr_real="$wyr_real $real + "
    wyr_user="$wyr_user $user + "
    echo "Real: $real, User: $user"
    rm -f _res123
done
wyr_real="scale=2;($wyr_real 0) / $ile"
wyr_user="scale=2;($wyr_user 0) / $ile"
licz(){
    echo $@ | bc | tr '.' ',' | sed "s/^\,/0,/"
}
sr_real=$(licz $wyr_real)
sr_user=$(licz $wyr_user)
echo "Ĺredni real time dla pliku o rozmiarze 4GB z hakiem: $sr_real"
echo "Ĺredni user time dla pliku o rozmiarze 4GB z hakiem: $sr_user"
