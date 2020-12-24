# Resume
Resume
Smith-Waterman Algorithm in OpenMP
A highly efficient and simple implementation of the Smith-Waterman algorithm for local alignment of sequences.

Sample Output
Demo Doccou alpha

How to Use
Serial Version
Compile the project

gcc serial_smithW.c -o serial_smithW -fopenmp -DDEBUG
Run the program:

./serial_smithW <number_of_col> <number_of_rows>
Parallel Version
Compile the project

gcc omp_smithW.c -o omp_smithW -fopenmp -DDEBUG
Run the program:

./omp_smithW <number_of_threads> <number_of_col> <number_of_rows>
