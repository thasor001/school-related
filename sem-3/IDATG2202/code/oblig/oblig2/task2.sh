#!/bin/bash
lscpu | grep 'L1d cache\|L2 cache\|L3 cache'
for i in 4000 40000 400000 4000000 40000000 400000000; do echo "Array with $i integers:"; ../executable/ob2task2 $i; echo ; done
for (( i = 50000 ; i < 20000000 ; i += 50000)); do ../executable/ob2task2 $i; done >> a.dat
