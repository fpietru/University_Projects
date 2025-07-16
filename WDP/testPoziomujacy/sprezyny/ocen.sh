if [[ "$1" != "" ]]; then
    prog="$1"
else
    prog=.
fi
make $prog
for (( i=0; i<=10; i++ ))
do
	./$prog < ./testy/in/problems_13408_spr$i.in > out
	if diff out ./testy/out/problems_13408_spr$i.out > res; then
		echo "OK $i"
	else
		echo "WA $i"
	fi
done
rm out res
