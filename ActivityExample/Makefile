CC = g++
CPPFLAGS = -Wall -g

OBJECTS = ActivityImpl.o ActivityReactor.o

default:	example

example: example.o $(OBJECTS)
	 $(CC) $(CPPFLAGS) -o example example.o $(OBJECTS)
	 @echo

clean:
	 @rm -f example.o $(OBJECTS) example *~

ActivityImpl.o: ActivityImpl.h Activity.h
ActivityReactor.o: ActivityReactor.h Activity.h

