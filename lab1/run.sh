make a
for i in $(seq 1 15);
do
    ./a < ./testy/dzielny$i.in > ./out
    if diff ./out ./testy/dzielny$i.out > res; then
        echo "OK $i"
    else
        echo "WA $i"
        # cat ./testy/dzielny$i.in
        echo "Wzorcowka:"
        # cat ./testy/dzielny$i.out
        echo "Moje Rozw:"
        # cat ./out
    fi
done