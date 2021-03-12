#CXX=clang++
CXX=g++

FLAGS = -O3 -std=c++14 -g 

all:
	${CXX} ${FLAGS} *.cpp

TestmainPartial:  polygon.o TestmainPartial.o
	${CXX} $^ -o $@

clean:
	rm *.o