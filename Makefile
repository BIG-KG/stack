all: hello
	hello
hello: main.o stackfunk.o const.o canary.o
	g++ main.o stackfunk.o const.o canary.o -o hello

main.o: main.cpp
	g++ -c main.cpp

stackfunk.o: stackfunk.cpp
	g++ -c stackfunk.cpp
	
const.o: const.cpp
	g++ -c const.cpp
	
canary.o: canary.cpp
	g++ -c canary.cpp

clean:
	rm -rf *.o hello