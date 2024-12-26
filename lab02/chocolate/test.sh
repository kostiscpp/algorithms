#!/bin/bash

for i in {1..24} 
do
	echo "Case $i"
	#diff output$i.txt <
	time (./a.out < input$i.txt)
done
