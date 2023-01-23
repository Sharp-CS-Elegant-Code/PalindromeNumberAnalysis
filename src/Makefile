CXX = g++
CXXFLAGS = -g3 -Wall -Wextra
LDFLAGS = -g3

Experiments.out: Experiments.o Solutions.o
	${CXX} ${LDFLAGS} -o $@ $^

Experiments.o: Experiments.cpp

Solutions.o: Solutions.cpp 

BuildHalvesSolution.out: BuildHalvesSolution.o Solutions.o
	${CXX} ${LDFLAGS} -o $@ $^

BuildHalvesSolution.o: BuildHalvesSolution.cpp

CharArraySolution.out: CharArraySolution.o Solutions.o
	${CXX} ${LDFLAGS} -o $@ $^

CharArraySolution.o: CharArraySolution.cpp

FastBuildHalvesSolution.out: FastBuildHalvesSolution.o Solutions.o
	${CXX} ${LDFLAGS} -o $@ $^

FastBuildHalvesSolution.o: FastBuildHalvesSolution.cpp

IntArraySolution.out: IntArraySolution.o Solutions.o
	${CXX} ${LDFLAGS} -o $@ $^

IntArraySolution.o: IntArraySolution.cpp

StringSolution.out: StringSolution.o Solutions.o
	${CXX} ${LDFLAGS} -o $@ $^

StringSolution.o: StringSolution.cpp

VectorSolution.out: VectorSolution.o Solutions.o
	${CXX} ${LDFLAGS} -o $@ $^

VectorSolution.o: VectorSolution.cpp

ArithmeticSolution.out: ArithmeticSolution.o Solutions.o
	${CXX} ${LDFLAGS} -o $@ $^

ArithmeticSolution.o: ArithmeticSolution.cpp