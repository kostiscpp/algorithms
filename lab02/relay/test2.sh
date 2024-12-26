# !/bin/bash

for i in {16..22}
do
    echo "Case $i"

    # Run the program and capture its exit status
    ./a.out < input$i.txt > temp_output$i.txt
    status=$?

    # Check if the program ended with a segmentation fault
    if [ $status -eq 139 ]; then
        echo "Segmentation Fault (SIGSEGV)"
        continue # Skip to the next iteration of the loop
    fi

    # Compare output if no segfault
    if diff output$i.txt temp_output$i.txt > /dev/null; then
        echo "AC"
    else
        echo "WA"
    fi

    # Optional: Remove the temporary output file
    rm temp_output$i.txt
done

