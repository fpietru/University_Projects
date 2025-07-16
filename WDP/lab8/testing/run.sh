g++ @opcjeCpp -o a a.cpp
g++ -o gen gen.cpp
i=0
while true
do
    ./gen $i > in
    echo "$i"
    head in
    time ./a < in > out
done