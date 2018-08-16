//Daniel Thompson
#include"TdArray.hpp"
#include<iostream>
#include<cstdlib>
#include<iomanip>

//This 2D array/Matrix is created with inputted Rows and Columns on startup
TdArray::TdArray(int x, int y) {
  row = x;
  col  = y;
  size = (row - 2) * (col - 2); //Size of the freepool
  matrix = new int *[row];

  //Makes the array 2d
  for(int i = 0; i < row; i++)
      matrix[i] = new int[col];

  freePool = new node[size];
  snake = new Snake(10, 10, fSize() );
  
  //sets the -1's then builds the freepool
  int z = 0;
  for(int i = 0; i < row; i++) {
      for(int j = 0; j < col; j++) {
	  if( i == 0 || i == (x - 1) ) {
	    matrix[i][j] = -1;
	  } else if( j == 0 || j == (y - 1) ) {
	    matrix[i][j] = -1;
	  } else {
	      matrix[i][j] = z;
	      z++;
	    }
	}
    }
  //Calls a below function to build the freePool
  poolBuilder();
}

//Used for testing originally in main with curses commented out. No longer used
void TdArray::print() {
  for(int i = 0; i < row; i++) {
      for(int j = 0; j < col; j++) {
	if( i == 0 || i == row - 1 ) {
	    std::cout << std::setw(4) << matrix[i][j];
	} else if( j == 0 || j == col - 1 ) {
	    std::cout << std::setw(4) << matrix[i][j];
	} else {
	    std::cout << std::setw(4) << matrix[i][j];
	}
      }
      std::cout << std::endl;
    }
}

//Returns a munchie Node
node TdArray::getMunch() {
  return munchie;
}

//Sets the munchie node to a Random node in the freepool.
//P is a randomly generated integer from main
void TdArray::munch(int p) {
  munchie = freePool[p];
}

node TdArray::getPool(int p) {
  return freePool[p];
}

//This functions use is described in the HPP.
void TdArray::Update(int row, int col) {
  matrix[row][col] = matrix[freePool[size].row][freePool[size].col];
  
  freePool[size - 1].row = row;
  freePool[size - 1].col = col;

  size++;
}

//Chad helped a few of us a lot here...
//Removing part of the grid 
void TdArray::Remove(int row, int col) {
  int idx = matrix[row][col];
  freePool[idx].row = freePool[size-1].row;
  freePool[idx].col = freePool[size-1].col;
  matrix[row][col] = -1;
  matrix[freePool[idx].row][freePool[idx].col] = idx;
   
  size--;
}

//Explained in the HPP
int TdArray::fSize() {
  return size;
}

//Builds freePool
void TdArray::poolBuilder() {
  int n = 0;
  for(int i = 0; i < row; i++) {
      for(int j = 0; j < col; j++) {
	  if( i != 0 && i != (row - 1) && j != 0 && j != (col - 1) ) {
	    if( n < fSize() ) {
		  freePool[n].row = i;
		  freePool[n].col = j;
		  n++;
		}
	    }
	}
    }    
}


TdArray::~TdArray() {
  std::cout << "Deleting rows \n";
  for(int i = 0; i < row; i++)
    delete [] matrix[i];

  std::cout << "Deleting rest\n";
  delete [] matrix;
  delete [] freePool;
}


