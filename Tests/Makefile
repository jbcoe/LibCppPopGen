CC = g++
CCFLAGS = -I /opt/local/include 
LDFLAGS = -L/opt/local/lib -lcppunit

SOURCES=TestRunner.cpp

EXECUTABLE=TestRunner

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
