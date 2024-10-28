i=0
while true
do
    ./gen $i > in
    ./brut < in > out1
    ./testowanie < in > out2
	
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