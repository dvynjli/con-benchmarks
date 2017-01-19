
This is an example of a program that sorts an array using several procedures.

In particular, main-bub.c uses as the sorting algorithm, bubble sort.
The main thread divides the array into the number of threads to be spawned.
Each thread performs bubble sort in the sub-array. When the threads finish,
main simultaneously traverses the sub-arrays and performs the final computation.


A second procedure, main-min.c is more communication heavy as the main 
thread spawns a number of threads with the following communication:
 - each thread can only see a part of the array (x,y)
 - main asks a thread X to find the minimum of the sub-array
 - thread X puts into x the mimum of the array and communicates to main the index
 - thread X then increments x and when x == y, it tells main that it is done

