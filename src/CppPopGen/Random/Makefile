CC=g++-mp-4.6
CFLAGS=-O0 -std=c++0x 
SOURCES=WeightBasedSampler.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE = WeightBasedSampler

run: all
	./$(EXECUTABLE)

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -c -o $@

WeightBasedSampler.o : WeightBasedSampler.cpp WeightBasedSampler.hpp

clean:
	- rm $(OBJECTS) $(EXECUTABLE)

.PHONY: clean

