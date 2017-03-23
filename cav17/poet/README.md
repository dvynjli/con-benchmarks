Benchmarks used for experiments in CAV Submission 17:
  Abstract Interpretation with Unfoldings

The svcXXX benchmarks are directly based on the SVCOMP benchmarks from the directories *pthread* and *pthread-ext*. 
Some of them were modified to add data non-determinism and bounded thread creation.

The remaining benchmarks are models of real-world concurrent programs such as a map-reduce style DNA sequence analyser, a standard producer-consumer and a thread pool. Their functionality is representative of some of the more advanced benchmarks in the SVCOMP that have data non-determinism.
