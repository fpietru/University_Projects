make gen
make wzo
make brut
i=0
while true
do
	./gen $i > in1
	./brut < in1 > out1
	./wzo < in1 > out2
	if diff out1 out2 > res; then # diff zwraca 0 jeśli pliki są takie same
		echo "OK $i"
	else
		echo "WA $i"
		echo "Wejscie:"
		cat in1
		echo "Brut:"
		cat out1
		echo "Rozw:"
		cat out2
		break
	fi
	((i++))
done
