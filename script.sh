#!/bin/bash

NPROC=$((nproc * 2)) # 2x le nombre de threads sur cette machine
mkdir -p data
make

echo "[POSIX] - Philosophes test"
echo "thread, time" > data/posix_philo.csv
for i in `seq 2 $N`; do
    #evaluation des philosophes
done

echo "[POSIX] Producer-consumer test"
echo "thread, time" > data/posix_pro_con.csv #ajout du nom des colones
for i in `seq 2 $N`; do
    #evaluation pro_cons
done

echo "[POSIX] - Reader-writer test"
echo "thread,time" > data/posix_rw.csv
for i in `seq 2 $N`; do
    #Evaluation des read-write
done


