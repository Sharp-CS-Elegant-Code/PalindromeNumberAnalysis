#!/bin/bash

cd ../src
for s in BuildHalvesSolution CharArraySolution FastBuildHalvesSolution IntArraySolution StringSolution VectorSolution ArithmeticSolution; do
    rm ${s}.o 2> /dev/null
    make ${s}.o
    rm ${s}.out 2> /dev/null
    make ${s}.out
done
rm Experiments.out 2> /dev/null
make Experiments.out
./Experiments.out
cd ../results

