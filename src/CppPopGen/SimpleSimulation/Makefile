CC = clang++
CCFLAGS = -std=c++11 -I/opt/local/include -I../../
LDFLAGS = -std=c++11 -L/opt/local/lib

SOURCES=SimpleSimulation.cpp

EXECUTABLE=SimpleSimulation

OBJECTS=$(SOURCES:.cpp=.o)

run: all
	./$(EXECUTABLE)

all: $(SOURCES) $(EXECUTABLE)

edit:
	vim $(SOURCES)

SimpleSimulation.o: SimpleSimulation.cpp \
 ../../CppPopGen/CppPopGenBase.hpp \
 ../../CppPopGen/Random/WeightBasedSampler.hpp \
 ../../CppPopGen/SimpleSimulation/Mutation.hpp \
 ../../CppPopGen/SimpleSimulation/MutationPool.hpp \
 ../../CppPopGen/SimpleSimulation/MultiplicativeFitnessModel.hpp \
 ../../CppPopGen/SimpleSimulation/AsexualReproductionModel.hpp \
 ../../CppPopGen/SimpleSimulation/NullMutationModel.hpp \
 ../../CppPopGen/SimpleSimulation/LostOrFixedMutationsToCOUT.hpp

.cpp.o:
	$(CC) $(CCFLAGS) $< -c -o $@

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

clean:
	- rm $(OBJECTS) $(EXECUTABLE)

.PHONY: clean

