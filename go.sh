#! /bin/bash
clear
make
echo "**************************************************************************************************************************************"

if [ "$#" -ne 1 ]
then
  #echo $1
  NUM_PROCESSES=2
else
  #echo 2
  NUM_PROCESSES=$1
fi

time mpirun -np $NUM_PROCESSES ./main

echo "**************************************************************************************************************************************"

echo Done