#!/bin/bash

max=10
metade=$(($1/2))

echo "num_vertices: $1   SEED: $seed   metade:$metade"
for seed in `seq 1 $max`
do
    ./_gen $1 $seed   > comp/t$1s$seed
    ./_t5 comp/t$1s$seed $metade
done
