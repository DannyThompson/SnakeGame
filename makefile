FLAGS = -ggdb -std=c++11 -Wextra -Wall

screen.x:  screen.o getChar.o TdArray.o Snake.o
	g++ $(FLAGS) -o screen.x screen.o TdArray.o Snake.o getChar.o -lcurses -ltermcap

screen.o: screen.cpp
	g++ $(FLAGS) -c screen.cpp -o screen.o

getChar.o: getChar.cpp 
	gcc -c -ggdb getChar.cpp -o getChar.o

Snake.o: Snake.hpp Snake.cpp
	g++ $(FLAGS) -c Snake.cpp -o Snake.o 

TdArray.o: TdArray.hpp TdArray.cpp
	g++ $(FLAGS) -c TdArray.cpp -o TdArray.o

clean:
	/bin/rm -f screen.x *~ *# *.o

run:
	./screen.x
