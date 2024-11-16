if [[ "$1" != "" ]]; then
    prog="$1"
else
    prog=.
fi
make $prog
for (( i=0; i<=10; i++ ))
do
	./$prog < ./testy/in/problems_13443_dom$i.in > out
	if diff out ./testy/out/problems_13443_dom$i.out > res; then
		echo "OK $i"
	else
		echo "WA $i"
	fi
done
rm out res
