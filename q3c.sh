#!/bin/bash
for (( i=16; i<=134217728; i=i*2 ))
do 
	./run3 ubuntu-21.04-desktop-amd64.iso $i >> run3nocacheoutput.csv
	sudo sh -c "/usr/bin/echo 3 > /proc/sys/vm/drop_caches"
	echo "Completed $i blocksize"
done