//Daniel Thompson
#ifndef _SNAKE
#define _SNAKE


//Struct. Same concept as cell, but done as a struct instead of its own class
//Originally this was in the private section but ran into issues with it there
  struct node
  {
    int row;
    int col;
  };

class Snake{

public:
  Snake(int x, int y, int size);
  ~Snake();
  bool grow(int n); //Grows the size
  node getHead(); // Returns the col && row vals of the head.
  node getTail();
  node body();
  int getHeadIndex() { return head; } //Returns index of head. Not sure if will be needed.  
  int getTailIndex() { return tail; } // returns the index of the tail
  void moveHead(int r, int c);
  void moveTail();
  int getSize() { return _size; } // returns the size of the array.
  
private:

  node *snakey; //Pointer
  int head; // Index of the head
  int tail; // Index of the tail
  int _size; //Size of the circular snake array
  
};
#endif
