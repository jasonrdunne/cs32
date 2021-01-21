<<<<<<< HEAD
#CXX=clang++
CXX=g++

FLAGS = -O3 -std=c++14 

all:
	${CXX} ${FLAGS} *.cpp
=======
# Makefile for lab00, Jason Dunne, CS32, W21

CXX=clang++
# CXX=g++

helloWorld: helloWorld.o
	${CXX} helloWorld.o -o helloWorld

helloWorld.o: helloWorld.cpp
	${CXX} -c helloWorld.cpp

clean:
	/bin/rm -f *.o helloWorld

 lab00Test: lab00Test.o tddFuncs.o arrayFuncs.o
	${CXX} lab00Test.o tddFuncs.o arrayFuncs.o -o lab00Test
>>>>>>> bebd4fe9ede0e5247117c3c5c9e45286e81e4266
