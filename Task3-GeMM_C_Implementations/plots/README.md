# Contents
This file contains the relevant instructions for the coursework, regarding tasks 2 and 3.
---
## Task 2

## Task 3

The code for Task 3 has been stored in a folder called 'Task3_GeMM_C_Implementations'. It contains two C files, two Python files and relevant CSV files for plotting purposes.
---
### C File no. 1

This file is called '**GEMM.c**', containing 6 different loop orderings for the matrix multiplication aspect of the assignment. It uses square test matrices from 10x10 to 400x400 to give the user a wide range of values for comparison. This task is a demonstration of how cache locality and memory access patterns can affect the speed of the program. 

To run this file, use git clone to make a copy of this repository and then run '**gcc -o GEMM.c GEMM.exe**' in the terminal of the text editor or IDE to compile and create an executable file. After you can see the executable, then add the command '**./GEMM**' to actually run the program. The output should be a CSV file and terminal output to show the times to the user. After the CSV file has been generated, run the python file (**GEMMPlotting.py**) for an easy to read .png image file.
---
### C File no. 2

This file is called '**OptGEMM.c**', containing the MNK loop ordering for the matrix multiplication aspect of the assignment. It uses the same square test matrices from 10x10 to 400x400 to give the user a wide range of values for comparison. In this file, there is the standard MNK ordering for the loop, then an introduction to 'blocking' or 'tiling', to optimise the program a bit more. Another implementation of the same ordering uses multithreading, accounting for the parallelism aspect of the coursework, which also optimises the program. The final implementation combines both aspects (blocking and multithreading) together. 

To run this file, '**gcc -o OptGEMM.c OptGEMM.exe**' in the terminal of the text editor or IDE to compile and create an executable file. After you can see the executable, then add the command '**./OptGEMM**' to actually run the program. The output should be a CSV file, and terminal output to show the times to the user. After the CSV file has been generated, run the python file (**OptPlot.py**) for 4 .png image files, (stored in the '**plots**' folder upon creation) showing a direct comparison between the different optimisation methods and the standard non-optimised method, a logarithmic graph to show execution times and a comparison between three selected matrix sizes. You can easily alter the chosen matrix dimenstions etc. 
