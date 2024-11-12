g++ -o gen gen.cpp
gcc -o brut brut.c
gcc -o a a.c
i=0
while true
do
    ./gen $i > in
    ./brut < in > out1
    ./a < in > out2
	
    if diff out1 out2 > res; then
		echo "OK $i"
	else
		echo "WA $i"
		echo "Wejscie:"
		cat in
		echo "Brut:"
		cat out1
		echo "Rozw:"
		cat out2
		break
	fi
	((i++))
done