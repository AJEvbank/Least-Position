# Least-Position

Names: Nick Alvarez, Caleb Bellando, Austin Eubank

The algorithm runs as it would sequentially, but in the choose function the
processes only check a slice of the dist array and then communicate the local
minimum. These values are passed up to process 0 "play-off" style and each
process which receives a value compares it with its own local minimum and
passes on the lesser value. Process zero then determines the global minimum and
broadcasts it to the other processes. Because of this it is important that each
process has the same dist array.

Therefore, after the for loop in f, the dist array is passed to all processes.
In this for loop, each process checks only a slice of the dist array before
they each pass on their slice to rank zero which then broadcasts the entire
dist array to all processes.

Note that a constraint of this program is that n must be evenly divisible by
the number of processes.
