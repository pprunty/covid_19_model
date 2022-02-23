CC	:= g++
CFLAGS 	:= -Wall -Wextra -O3 --std=c++17
LDFLAGS := -lm 
IFLAGS  := 
EXE1 	:= main
EXE2	:= 2d_walk
CFILES	:= main.cc 2d_walk.cc grid.cc person.cc
OBJECTS1 := main.o grid.o person.o
OBJECTS2 := 2d_walk.o grid.o person.o


all: ${EXE1} ${EXE2}


$(EXE1): $(OBJECTS1)
	$(CC) $(CFLAGS) -o $(EXE1) $(OBJECTS1) $(LDFLAGS)

$(EXE2): $(OBJECTS2)
	$(CC) $(CFLAGS) -o $(EXE2) $(OBJECTS2) $(LDFLAGS)

main.o: main.cc
	$(CC) $(CFLAGS) -c main.cc

2d_walk.o: 2d_walk.cc
	$(CC) $(CFLAGS) -c 2d_walk.cc

grid.o: grid.cc
	$(CC) $(CFLAGS) -c grid.cc

person.o: person.cc
	$(CC) $(CFLAGS) -c person.cc



.PHONY: clean
clean:
	rm -f $(EXE1) $(EXE2) $(OBJECTS1) 2d_walk.o *.txt
