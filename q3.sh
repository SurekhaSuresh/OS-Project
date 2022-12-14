#!/bin/bash
for (( i=16; i<=134217728; i=i*2 ))
do 
	./run3 ubuntu-21.04-desktop-amd64.iso $i >> run3output.csv
	echo "Completed $i blocksize"
done