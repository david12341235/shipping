CPPFLAGS = -I.
CXXFLAGS = -Wall -g

OBJECTS = Instance.o Engine.o example.o Segment.o Location.o Conn.o
LIBS = fwk/BaseCollection.o fwk/BaseNotifiee.o fwk/Exception.o

default:	example

example:	example.o $(OBJECTS) $(LIBS)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f example $(OBJECTS) *~

Instance.o: Instance.cpp Instance.h
example.o: example.cpp
Engine.o: Engine.cpp Engine.h
Segment.o: Segment.cpp Segment.h
Location.o: Location.cpp Location.h
Conn.o: Conn.cpp Conn.h
