#!/bin/bash

# Define available files
file1="src/AC_UNSAFE/fdopendir_ac_unsafe_test.c"
file2="src/AS_UNSAFE_HEAP/fdopendir_as_unsafe_heap_test.c"
file3="src/MT_SAFE/fdopendir_mt_safe_test.c"

# Prompt the user to select a file
echo "Which file do you want to compile and run?"
echo "1) $file1 (AC-Unsafe Test)"
echo "2) $file2 (AS-Unsafe Heap Test)"
echo "3) $file3 (MT-Safe Test)"

read -p "Make your selection (1, 2, or 3): " choice

# Determine the selected file
if [[ "$choice" == "1" ]]; then
    selected_file=$file1
    tool="valgrind --tool=memcheck --leak-check=full --track-origins=yes --show-leak-kinds=all"
elif [[ "$choice" == "2" ]]; then
    selected_file=$file2
    tool="valgrind --tool=memcheck --leak-check=full --track-origins=yes --show-leak-kinds=all"
elif [[ "$choice" == "3" ]]; then
    selected_file=$file3
    tool="valgrind --tool=helgrind --trace-children=yes"
else
    echo "Invalid selection. Exiting."
    exit 1
fi

# Determine the output file name (removing the .c extension)
output_file="${selected_file%.c}"

# Compile the selected file
echo "Selected file: $selected_file"
echo "Compiling..."
gcc -g -o "$output_file" "$selected_file" -pthread

# Check if compilation succeeded
if [[ $? -ne 0 ]]; then
    echo "Compilation failed. Please check your code."
    exit 1
fi

# Run the compiled file with the appropriate tool
echo "Running with $tool..."
$tool ./"$output_file"

# Check if execution failed
if [[ $? -ne 0 ]]; then
    echo "An error occurred during execution with $tool."
    exit 1
fi
