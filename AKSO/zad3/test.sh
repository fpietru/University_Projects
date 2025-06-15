#!/bin/bash
# Autor: Olaf Targowski
# Przeznaczenie: sprawdzenie poprawnoĹci zadania 3 z AKSO (freverse)
# Ta wersja SPRAWDZA odpornoĹci kodu na bĹÄdy.
# WERSJA 4.0
set -euo pipefail
[ "$#" = "1" ] || { echo "SposĂłb uĹźycia: test.sh ./freverse"; exit 123; }
program="$1"

if [ -f bajty ] && [ -f bajtyrev ] && [[ $(wc -c < bajty) -gt 4294967296 ]] \
    && [[ $(wc -c < bajtyrev) -gt 4294967296 ]]; then
    echo "UĹźywam wczeĹniejÂ wygenerowanych losowych bajtĂłw z plikĂłw 'bajty' i 'bajtyrev'."
else
    echo "GenerujÄ losowe bajty..."
    echo "sus mogus" > bajty
    dd if=/dev/urandom of=bajty oflag=append conv=notrunc bs=1M count=4096 status=progress
    echo "123567890" >> bajty
    echo "Wygenerowano."
    echo "Odwracam rzeczone bajty..."
    # Czat wygenerowaĹ.
    perl -e '
    #!/usr/bin/perl
    use strict;
    use warnings;
    use Fcntl qw(:seek);

    # === CONFIG ===
    my $BUFFER_SIZE = 1048576;

    # === ARGUMENTS === # niezbyt.
    my ($infile, $outfile) = ("bajty", "bajtyrev");

    # === OPEN INPUT FILE ===
    open(my $in, "<:raw", $infile) or die "Cannot open input file $infile: $!";

    # === OPEN OUTPUT FILE ===
    open(my $out, ">:raw", $outfile) or die "Cannot open output file $outfile: $!";

    # === GET FILE SIZE ===
    my $filesize = -s $infile;
    die "Failed to get file size for $infile\n" unless defined $filesize;

    # === PROCESS FILE IN REVERSE ===
    for (my $pos = $filesize; $pos > 0; $pos -= $BUFFER_SIZE) {
        my $read_size = ($pos < $BUFFER_SIZE) ? $pos : $BUFFER_SIZE;
        my $buffer;

        seek($in, $pos - $read_size, SEEK_SET) or die "Seek failed at position " . ($pos - $read_size) . ": $!";
        my $bytes_read = read($in, $buffer, $read_size);
        die "Read failed at position " . ($pos - $read_size) . ": $!" unless defined $bytes_read;
        die "Unexpected EOF at position " . ($pos - $read_size) if $bytes_read != $read_size;

        $buffer = reverse($buffer);
        print $out $buffer;
    }

    # === CLEANUP ===
    close($in);
    close($out);
    '
    echo "OdwrĂłcono."
fi

rozmiar_calosci=$(wc -c < bajty)

# 2 argumenty:
# $1 - rozmiar pliku w bajtach.
# $2 - "jo" wtw ma wiÄcej gadaÄ.
testuj(){
    head -c $1 bajty > test
    echo -ne "TestujÄ na $1 bajtach:\r"
    if [ "$2" = "jo" ]; then
        echo
        time "$program" test || { echo -e "\nBĹÄD WYKONANIA!!1!11!"; exit 37; }
    else
        "$program" test || { echo -e "\nBĹÄD WYKONANIA!!1!11!"; exit 38; }
    fi
    # CZEMU to Ĺcierwo exituje z 1 jak wynik to zero??????????
    prefiks=$(expr $rozmiar_calosci - $1 || true)
    if ! cmp -si 0:$prefiks test bajtyrev; then
        echo -e "\nZĹA ODPOWIEDĹš!!1!11!"
        cmp -li 0:$prefiks test bajtyrev
        exit 69;
    fi
    rm -f test
}

echo "TestujÄ exit code'y..."

# Nie testujemy exit :).
for sc in read write open close stat fstat lseek mmap munmap msync; do
    for sc2 in read write open close stat fstat lseek mmap munmap msync; do
        [[ $sc > $sc2 ]] && continue
        rozmiar=134217743 # 128MB+15
        prefiks=$(expr $rozmiar_calosci - $rozmiar || true)
        head -c $rozmiar bajty > test
        
        set +e
        strace -e inject=$sc:error=ENOANO -e inject=$sc2:error=ESTRPIPE -o _res123 "$program" test
        retcode=$?
        set -e
        echo -ne "Przetestowano na $rozmiar bajtach blokujÄc $sc i $sc2.            \r"
        if grep -qE "ENOANO|ESTRPIPE" _res123; then
            if ! [ $retcode = "1" ]; then
                echo -e "\nPomimo poraĹźki syscalla, program zwrĂłciĹ kod $retcode zamiast 1 !!!"
                exit 69;
            fi
            czy_fatalne=""
            if grep -q "ENOANO" _res123; then
                for a in read write open stat fstat lseek mmap; do
                    [ $a = $sc ] && czy_fatalne=owszem
                done
            fi
            if grep -q "ESTRPIPE" _res123; then
                for a in read write open stat fstat lseek mmap; do
                    [ $a = $sc2 ] && czy_fatalne=owszem
                done
            fi
            if [ "$czy_fatalne" = owszem ]; then
                if ! cmp -sn $rozmiar test bajty; then
                    echo -e "\nPomimo poraĹźki kluczowego syscalla, plik zostaĹ zmodyfikowany!!!"
                    cmp -ln $rozmiar test bajty
                    exit 69;
                fi
            else
                if ! cmp -si 0:$prefiks test bajtyrev; then
                    echo -e "\nPomimo poraĹźki niekluczowego syscalla, plik nie zostaĹ odwrĂłcony!!!"
                    cmp -li 0:$prefiks test bajtyrev
                    exit 69;
                fi
            fi
        else
            if ! [ $retcode = "0" ]; then
                echo -e "\nPomimo braku poraĹźki, program zwrĂłciĹ kod $retcode zamiast 0 !!!"
                exit 69;
            fi
            if ! cmp -si 0:$prefiks test bajtyrev; then
                echo -e "\nBlokowany syscall nie zostaĹ wywoĹany, a mimo tego ZĹA ODPOWIEDĹš!!1!11!"
                cmp -li 0:$prefiks test -
                exit 69;
            fi
        fi
        rm -f test _res123
    done
done

echo "Koniec testowania exit code'Ăłw.                               "

echo "TestujÄ sprawdzanie argumentĂłw..."

set +e

"$program" /
res=$?; [ "$res" != "1" ] && { echo -e "Program zwrĂłciĹ $res zamiast 1 przy wywoĹaniu z /"; exit 38; }
"$program" .
res=$?; [ "$res" != "1" ] && { echo -e "Program zwrĂłciĹ $res zamiast 1 przy wywoĹaniu z ."; exit 38; }
"$program"
res=$?; [ "$res" != "1" ] && { echo -e "Program zwrĂłciĹ $res zamiast 1 przy wywoĹaniu z niczym."; exit 38; }
head -c 1048591 bajty > test
"$program" test test
res=$?; [ "$res" != "1" ] && { echo -e "Program zwrĂłciĹ $res zamiast 1 przy wywoĹaniu z test test"; exit 38; }
"$program" test test test
res=$?; [ "$res" != "1" ] && { echo -e "Program zwrĂłciĹ $res zamiast 1 przy wywoĹaniu z test test test"; exit 38; }
"$program" /dev/urandom
res=$?; [ "$res" != "1" ] && { echo -e "Program zwrĂłciĹ $res zamiast 1 przy wywoĹaniu z /dev/urandom"; exit 38; }
"$program" /dev/zero
res=$?; [ "$res" != "1" ] && { echo -e "Program zwrĂłciĹ $res zamiast 1 przy wywoĹaniu z /dev/zero"; exit 38; }

s=symlink12312
ln -sf nieistniejacy_plik12321 $s
"$program" $s
res=$?; [ "$res" != "1" ] && { echo -e "Program zwrĂłciĹ $res zamiast 1 przy wywoĹaniu z $s -> nieistniejacy_plik12321"; exit 38; }
ln -sf test $s
"$program" $s
res=$?; [ "$res" != "0" ] && { echo -e "Program zwrĂłciĹ $res zamiast 0 przy wywoĹaniu z $s -> test"; exit 38; }

rm -f $s

set -e

echo "Koniec sprawdzania argumentĂłw."

for rozmiar in $(seq 0 1024); do
    testuj $rozmiar niejo
done

for wykladnik in $(seq 12 2 32); do
    rozmiar=1
    for i in $(seq 1 $wykladnik); do
        rozmiar=$(expr $rozmiar '*' 2)
    done
    jo="niejo"
    [[ $wykladnik -gt 27 ]] && jo="jo"
    testuj $rozmiar $jo
    rozmiar=$(expr $rozmiar + $(printf "%llu" 0x$(openssl rand -hex 1)))
    # Za chwilÄ na peĹnym pliku ztestujemy jak wykl=32.
    if [[ $wykladnik -lt 32 ]]; then
        testuj $rozmiar $jo
    fi
done

testuj $rozmiar_calosci jo
