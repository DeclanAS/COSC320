#makefile project 2 COSC320-001 | Declan Sheehan

run:
	g++ -std=c++11 -c main.cpp -g
	g++ -o proj2.exe main.o -g

clean:
	rm -k main.o

