#makefile for Lab-1, Declan Sheehan

# Creates executeable if either of the
# Dependencies change
lab1: main.o timer.o
	g++ -o Lab1.exe  main.o timer.o

# Rule for creating main.o
main.o: main.cpp timer.h
	g++ -c main.cpp

# Rule for creating timer.o
timer.o: timer.cpp timer.h
	g++ -c foo.cpp

# Rule for cleaning
clean:
	rm *.o