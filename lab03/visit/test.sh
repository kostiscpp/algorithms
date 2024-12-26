#!/bin/bash

for i in {1..22} 
do
	echo "Case $i"
	diff output$i.txt <(./a.out < input$i.txt)
done
