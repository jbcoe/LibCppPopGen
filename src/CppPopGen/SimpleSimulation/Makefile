CC = g++-mp-4.7
CCFLAGS = -std=c++0x -I/opt/local/include -I../
LDFLAGS = -std=c++0x -L/opt/local/lib

SOURCES=SimpleSimulation.cpp

EXECUTABLE=SimpleSimulation

OBJECTS=$(SOURCES:.cpp=.o)

run: all
	./$(EXECUTABLE)

all: $(SOURCES) $(EXECUTABLE)

edit:
	vim $(SOURCES)

.cpp.o:
	$(CC) $(CCFLAGS) $< -c -o $@

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

clean:
	- rm $(OBJECTS) $(EXECUTABLE)

.PHONY: clean
