#!/bin/bash

N=$((`nproc` * 2))
mkdir -p csv
make

echo "PERFORMANCE EVALUATION : producers-consumers.c "
echo "thread number,time" > csv/prod-cons.csv
for i in `seq 2 $N`;
do
    p=$((i % 2))
    x=$((i / 2))
    y=$(((i / 2) + p))
    for j in 1 2 3 4 5;
    do
        echo -n "$i," >> csv/prod-cons.csv
        ts=$(date +%s%N)
        ./producteurs-consommateurs $x $y
        tt=$((($(date +%s%N) - $ts)/1000000))
        echo $tt >> csv/prod-cons.csv
    done
done

echo "PERFORMANCE EVALUATION : philosophes.c "
echo "thread number,time" > csv/philo.csv
for i in `seq 2 $N`;
do
    p=$((i % 2))
    x=$((i / 2))
    y=$(((i / 2) + p))
    for j in 1 2 3 4 5;
    do
        echo -n "$i," >> csv/philo.csv
        ts=$(date +%s%N)
        ./philosophes $i
        tt=$((($(date +%s%N) - $ts)/1000000))
        echo $tt >> csv/philo.csv
    done
done

echo "PERFORMANCE EVALUATION : reader_writer.c "
echo "thread number,time" > csv/reader_writer.csv
for i in `seq 2 $N`;
do
    p=$((i % 2))
    x=$((i / 2))
    y=$(((i / 2) + p))
    for j in 1 2 3 4 5;
    do
        echo -n "$i," >> csv/reader_writer.csv
        ts=$(date +%s%N)
        ./reader_writer -r $x -w $y
        tt=$((($(date +%s%N) - $ts)/1000000))
        echo $tt >> csv/reader_writer.csv
    done
done

