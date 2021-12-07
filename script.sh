#!/bin/bash

N=$((`nproc` * 2))
mkdir -p csv
make

echo "PERFORMANCE EVALUATION : producers-consumers.c "
echo "thread number,time" > csv/pro_con.csv
for i in `seq 2 $N`;
do
    p=$((i % 2))
    x=$((i / 2))
    y=$(((i / 2) + p))
    for j in 1 2 3 4 5;
    do
        echo -n "$i," >> csv/pro_con.csv
        ts=$(date +%s%N)
        ./pro_con $x $y
        tt=$((($(date +%s%N) - $ts)/1000000))
        echo $tt >> csv/pro_con.csv
    done
done

echo "PERFORMANCE EVALUATION : philosophes.c"
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
echo "thread number,time" > csv/rw.csv
for i in `seq 2 $N`;
do
    p=$((i % 2))
    x=$((i / 2))
    y=$(((i / 2) + p))
    for j in 1 2 3 4 5;
    do
        echo -n "$i," >> csv/rw.csv
        ts=$(date +%s%N)
        ./rw $x $y
        tt=$((($(date +%s%N) - $ts)/1000000))
        echo $tt >> csv/rw.csv
    done
done



