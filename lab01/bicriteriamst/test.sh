#!/bin/bash

for i in {0..30} 
do
	echo "Case $i"
	diff output$i.txt <(./a.out < input$i.txt)
done
