# Least-Position

The algorithm runs as it would sequentially, but in the choose function the
processes only check a slice of the dist array and then communicate the local
minimum. These values are passed up to process 0 "play-off" style and each
process which receives a value compares it with its own local minimum and
passes on the lesser value. Because of this it is important 
