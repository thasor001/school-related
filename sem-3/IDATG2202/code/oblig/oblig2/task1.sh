#!/bin/bash
../executable/ob2task1
echo "l($(getconf PAGESIZE))/l(2)" | bc -l
