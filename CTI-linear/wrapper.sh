#!/bin/bash -x

output_dir="output/"
mkdir $output_dir

i="1"
N="2"

while [ $i -lt $N ]
do

cp new_twograins_mesh_3d.geo $output_dir/
./Ice_CTI cube P1 > $output_dir/M.field

i=$[$i+1]
done
