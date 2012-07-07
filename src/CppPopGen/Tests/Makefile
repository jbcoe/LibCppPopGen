CC = g++-mp-4.7
CCFLAGS = -std=c++0x -I../.. -I /opt/local/include 
LDFLAGS = -std=c++0x -L/opt/local/lib -lcppunit

SOURCES=TestRunner.cpp

EXECUTABLE=TestRunner

OBJECTS=$(SOURCES:.cpp=.o)

run: all
	./$(EXECUTABLE)

all: $(SOURCES) $(EXECUTABLE)

edit:
	vim $(SOURCES)

TestRunner.o: TestRunner.cpp \
 ../../CppPopGen/Random/TestWeightBasedSampler.hpp \
 ../../CppPopGen/Random/WeightBasedSampler.hpp \
 ../../CppPopGen/CppPopGenBase.hpp

.cpp.o:
	$(CC) $(CCFLAGS) $< -c -o $@

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

clean:
	- rm $(OBJECTS) $(EXECUTABLE)

.PHONY: clean
