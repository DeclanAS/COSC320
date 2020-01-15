#Makefile for Project 1, Declan Sheehan

proj1.exe: main.o matrix.o
	g++ -o proj1.exe main.o matrix.o

proj1B.exe: main2.o matrix.o
	g++ -o proj1B.exe main2.o matrix.o

main2.o: main2.cpp
	g++ -std=c++11 -c main2.cpp

main.o: main.cpp
	g++ -std=c++11 -c main.cpp

matrix.o: matrix.cpp
	g++ -std=c++11 -c matrix.cpp

clean:
	m *.o
