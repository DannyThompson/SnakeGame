//Daniel Thompson
#ifndef _TDARRAY
#define _TDARRAY
#include "Snake.hpp"
#include<iostream>

class TdArray{

public:
  TdArray(int x, int y);
  ~TdArray();

  int fSize(); //Returns the size of the FreePool

  //The below function Noah helped us figure out
  // returns a cell in the matrix
  int& cell(int row, int col){ return matrix[row][col]; }
  
  node getPool(int p); // Returns a node in the freePool
  
  void munch(int p); //Sets the munchy node
  node getMunch(); // Returns the Munchie node
  
  void Update(int row, int col); //This inserts an index in the matrix
  void Remove(int row, int col); //Removes an index in a matrix
  int cols() { return col; } 
  int rows() { return row; }
  void poolBuilder(); //builds the freepool
  void print(); // Used to testing purposes. NO longer shown in main
  Snake *snake; // Pointer to snake

private:
  
  node munchie; //Singular munchie node. This is used in main
  node *freePool; //FreePool is a node type. SNAKE class holds the public node
  int **matrix; //Double pointer GRID/MATRIX
  int size; // Size pf tje freepool
  int col; // Column of the matrix
  int row; // Row of the matrix
  //  int pRow; //Row of freepool
  //int pCol; //Col of freepool
};
#endif
  
  
