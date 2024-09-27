all: hello
	hello
hello: main.o stackfunk.o
	g++ main.o stackfunk.o -o hello

main.o: main.cpp
	g++ -c main.cpp

stackfunk.o: stackfunk.cpp
	g++ -c stackfunk.cpp

clean:
	rm -rf *.o hello