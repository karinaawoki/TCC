#!/bin/bash

num=100
max=20

for seed in `seq 1 $max`
do
echo "num_vertices: $1   SEED: $seed   metade:$metade"
	metade=$(($num/2));
    #./_gen $1 $seed   > comp/t$1s$seed
     ./_t5 ../src/testeCaminhoLongo/oi$num $metade
	num=$(( $num*2 ));
done
