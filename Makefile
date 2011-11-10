CPPFLAGS = -I.
CXXFLAGS = -Wall -g

OBJECTS = Instance.o Engine.o Segment.o Location.o Conn.o
LIBS = fwk/BaseCollection.o fwk/BaseNotifiee.o fwk/Exception.o

default:	test1 example

example:	example.o $(OBJECTS) $(LIBS)
	$(CXX) $(CXXFLAGS) -o $@ $^

test1:	test1.o $(OBJECTS) $(LIBS)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f example $(OBJECTS) *~

Instance.o: Instance.cpp Instance.h fwk/PtrInterface.h fwk/Ptr.h Engine.h
test1.o: test1.cpp Instance.h fwk/PtrInterface.h fwk/Ptr.h
example.o: example.cpp Instance.h fwk/PtrInterface.h fwk/Ptr.h
Engine.o: Engine.cpp Engine.h Instance.h fwk/PtrInterface.h fwk/Ptr.h fwk/NamedInterface.h
Segment.o: Segment.cpp Segment.h Instance.h fwk/PtrInterface.h fwk/Ptr.h fwk/NamedInterface.h
Location.o: Location.cpp Location.h Instance.h fwk/PtrInterface.h fwk/Ptr.h fwk/NamedInterface.h
Conn.o: Conn.cpp Conn.h Instance.h fwk/PtrInterface.h fwk/Ptr.h fwk/NamedInterface.h

