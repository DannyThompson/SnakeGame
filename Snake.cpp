//Daniel Thompson
#include "Snake.hpp"
#include<cstdlib>
#include<iostream>

//constructor
Snake::Snake(int x, int y, int size) {
  snakey = new node[size];
  snakey[0].row = x;
  snakey[0].col = y;
  _size = size;
  head = 0;
  tail = 0;
}

//Destructor. Not entirely sure if this works the way it should.
//See README for more details
Snake::~Snake() {
  std::cout << "Deleting snake";
  delete []snakey;
}

//The snake grows if the number given is > 1 (a munchie)
bool Snake::grow(int n) {
  if( n > 1 ) {
      _size += n;
      return true;
    }  
  return false;  
}

//Returns the head of the snake. '@' on the gameboard
node Snake::getHead() {
  return snakey[head];
}

node Snake::body() {
  return snakey[head - 1];
}

//Returns the tail of the snake
node Snake::getTail() {
  return snakey[tail];
}

//This moves the indeces
void Snake::moveHead(int r, int c) {
  head = ( (head + 1) + _size ) % _size; 
  snakey[head].row = r;
  snakey[head].col = c;
}

//Moves the tail. Only used if the snake isn't growing
void Snake::moveTail() {
  tail = ( (tail + 1) + _size )  % _size;
}
