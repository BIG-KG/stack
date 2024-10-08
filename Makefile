all: hello
	hello1
hello: main.o stackfunk.o const.o canary.o inner_stack_metods.o
	g++ main.o stackfunk.o const.o canary.o inner_stack_metods.o -o hello1

main.o: main.cpp
	g++ -c main.cpp
	
inner_stack_metods.o: inner_stack_metods.cpp
	g++ -c inner_stack_metods.cpp

stackfunk.o: stackfunk.cpp
	g++ -c stackfunk.cpp
	
const.o: const.cpp
	g++ -c const.cpp
	
canary.o: canary.cpp
	g++ -c canary.cpp

clean:
	rm -rf *.o hello