g++ testerka.cpp kol.cpp -o testerka
for i in {0..99}
do
    ./testerka < ./duze/in/$i.in > wyjscie
    if diff wyjscie ./duze/out/$i.out > res; then
		echo "OK $i"
	else
		echo "WA $i"
		echo "Wejscie:"
		cat ./duze/in/$i.in
		echo "Moje:"
		cat wyjscie
		echo "Rozw:"
		cat ./duze/out/$i.out
		break
	fi
done