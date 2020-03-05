#!/bin/bash
k=$#
avg=0
sum=0
for i in $@
do
sum=$(($sum+$i))
done
echo avg=$(($sum/$#))
