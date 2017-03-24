Benchmarks used in CAV 17
=========================

Bechmarks coming fro the SVCOMP'17 and '16 (in total 6 different families):

- ``cond.c``
- ``lazy_true.c``
- ``lazy_false.c``
- ``monab_1.c``
- ``monab_2.c``
- ``rand.c``
- ``sigma_true.c``
- ``sigma_false.c``
- ``stf.c``

Most of these have been modified from the original benchmark proposed in the
SVCOMP:

- Data races have been removed using POSIX mutexes
- Data-nondeterminism has been added when possible, to make the analysis more
  interesting.
- If the benchmark created unboundedly many threads, there is now a preprocessor
  macro fixing the number of threads created (sometimes the loop in the ``main``
  that creates the threads has been manually unrolled).
- Some analyzers do not support the use ``pthread_join(3)``, we often removed
  them (and updated the benchmark to perform the same task).

The remaining benchmarks are models (4 different families) come from real-world
concurrent programs:

- ``atgc.c``:
  uses ``NUM_THREADS`` threads to count the number of nucleotides in a
  non-deterministically choosen DNA sequence.
- ``findmax.c``:
  a producer threads non-deterministically allocates ``MAX_ITEMS`` numbers, and send
  them, in decreasing numeric order, to a consumer.
- ``thpool.c``:
  the ``main`` thread creates a thread pool (of only 1 thread), to which it sends
  (using spinlocks and mutexes) requests for work and from which it waits for
  replys with the results.
- ``tpoll.c``:
  ``NUM_THREADS`` sort an array of non-deterministically choosen integers using
  bubble sort, and signal their termination by setting a bit in the ``channel``
  variable. The ``main`` thread should now detect the termination of all
  threads, but the code contains a bug.

