CPPFLAGS = -I.
CXXFLAGS = -Wall -g

OBJECTS = Instance.o Engine.o example.o
LIBS = fwk/BaseCollection.o fwk/BaseNotifiee.o fwk/Exception.o

default:	example

example:	example.o $(OBJECTS) $(LIBS)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f example $(OBJECTS) *~

Instance.o: Instance.cpp Instance.h
example.o: example.cpp
