
findmax
=======

This is the example in Fig. 1 of the POPL'17 submission. The producer sends
sorted numbers into a fifo, and the consumer consumes then in order, storing
them into a sorted array. THe send and recv operations of the fifo have
spinlocks, which should be ok if we have cutoffs.

The folder buggy

main1.c is the very first version I implemented, without testing; it produces
only 0 in the sorted version

main2.c is after I realize the bug in queue_extract, I need to first decrement
the size and then access the last. But there is still another bug!

main3.c is after I realize that I need to extract the first of the queue and
not the last, it is a fifo, not a stack!

main.c == main3.c, modulo better printfs

atgc-count
==========

- Frama-c: imprecission due to the fact that the analysis imprecisely determines
  the id of one thread, and so it's unable to understand which positions of the
  sequence each thread is reading

threadpool
==========

- We only have one thread, which simultes a thread in a pool of threads
- The thread receives requests to work from the main thread; to signal a
  request, the main thread sets the variable "control" to 1
- The thread then starts to work, reading an argument from the variable "arg"
  and setting the result of the task to variable "result"
- The thread then increments the control variable, setting it to 2
- The main thread waits until the control variable is equal to 2 to read the
  results and assert that they are correct.
