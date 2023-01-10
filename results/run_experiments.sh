#!/bin/bash

cd ../src
for s in BuildHalvesSolution CharArraySolution FastBuildHalvesSolution IntArraySolution StringSolution VectorSolution; do
    rm ${s}.out 2> /dev/null
    make ${s}.out
done
rm Experiments.out 2> /dev/null
make Experiments.out
# ./Experiments.out
cd ../results

