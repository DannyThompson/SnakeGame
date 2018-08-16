//Daniel Thompson
//This file functions as a `main`.

#include<curses.h>
#include"getChar.hpp"
#include"TdArray.hpp"
#include<cstdlib>
#include<iostream>
#include<string>

void startup( void );
void terminate( void );

void drawBoard(TdArray* matrix) {
  int rows = matrix->rows();
  int cols = matrix->cols();
  for(int r = 0; r < rows; r++) {
      for(int col = 0; col < cols; col++ ) {
	int cell = matrix->cell(r, col);
	if(cell == -1) {
	  mvaddch(r + 5, col + 5,'*');
	} else {
	  mvaddch(r + 5, col + 5, ' ');
	}
      }
  }
}

//Function to generate Munchey.
int munchey(TdArray *matrix) {
  time_t  t;
  time(&t);
  srand(unsigned(t));
  int muncher = rand() % 8 + 1;
  int p = rand() % matrix->fSize();
  matrix->munch(p);
  return muncher;
}

int main() {
  int row;
  int col;
  std::cout << "Enter the amount of desired playable Rows between 9 and 25: ";
  std::cin >> row;
  std::cout << "Enter the amount of desired playable Columns between 9 and 80: ";
  std::cin >> col;

  while(row < 9 || row > 25) {
    std::cout << "Enter the amount of desired Rows between 9 and 25: ";
    std::cin >> row;
  }
  
  while(col < 9 || col > 80) {
      std::cout << "Enter the amount of desired Columns between 9 and 80: ";
      std::cin >> col;
    }

  //The original sizes given include the border
  //This will make the ACTUAL playable space the numbers given
  row+=2;
  col+=2;
  int cell = 0;
  TdArray *matrix = new TdArray(row, col);
  bool growing = false;
  int snake = 0;//Size of the snake
  int growAmount = 0; // Amount to grow after eating munchy
  int cur_r = row / 2; //Sets snake to middle of the board	   
  int cur_c = col / 2 - 4; //Same as above, but columns are offset incase you give minumum board size. This way you wont start outside the board
  char ch;

   startup();
   move(10, 10);

   //Prints Score and the name.
   //If the column # is too small, in the name portion, only "SNAKE will be printed.
   //If you give the minimum size, you can not possibly fit the name and score
   mvaddstr(row + 5, col - 5, "SCORE: " );
   mvaddstr(row + 5, col + 1, std::to_string(snake).c_str() );
   mvaddstr(4, 5, "SNAKE by Daniel Thompson");

   //Draws board
   drawBoard(matrix);

   //Initial condition
   matrix->snake->moveHead(cur_r, cur_c);
   
   //This makes the snake start out with a size of 8
   for(int i = 0; i < 8; i++) {
       
       matrix->Remove(cur_r, cur_c);
       //Iterates the column so the snake doesnt grow on top of itself
       cur_c++;
       matrix->snake->moveHead(cur_r, cur_c);
       //Could get away with this, but the snake would appear as 8 @'s at the start instead, so this makes the initial body o's
       mvaddch(matrix->snake->body().row + 5, matrix->snake->body().col + 5, 'o');
       mvaddch(matrix->snake->getHead().row + 5, matrix->snake->getHead().col + 5, '@');
     }
   
   //mvaddch(matrix->snake->getHead().row + 5, matrix->snake->getHead().col + 5, '@');
   
   //Generates a munchy
   int mun = munchey(matrix);
   ch = (char)('0'+ mun);
   mvaddch(matrix->getMunch().row + 5, matrix->getMunch().col + 5, ch);
   
   
   refresh();
   while(cell != -1) {
     char userKey = get_char();

     //These are the movement keys.
     //You can use the VIM keys, or standards WASD movement
     //Move Up
     if(userKey == 'k' || userKey == 'w') {
       cur_r -= 1;
     } else if(userKey == 'h' || userKey == 'a') { //Move Left
       cur_c -= 1;
     } else if(userKey == 'l' ||  userKey == 'd') { //Move Right
       cur_c += 1;
     } else if(userKey == 'j' ||  userKey == 's') { //Move Down
       cur_r += 1;
     } else if(userKey == ' ') {
       continue;
     }

     
     //If the head enters a cell with -1 val, you lose.
     cell = matrix->cell(cur_r, cur_c);
     if(cell == -1 ) {
	     terminate();
	     delete matrix;
	     delete matrix->snake; //Not sure if this actually works. Since snake was used as a pointer from TdArray(Matrix), it was never newed up in main
	     std::cout << "\nYour final score: " << snake << std::endl;
	     exit(0);	 
     }

     
     //If munchy is eated, amount to grow is set to that value, and growing continues for that length
     //Then a new munchy will be generated
     if(cur_r == matrix->getMunch().row && cur_c == matrix->getMunch().col) {
	      growAmount += mun;
	      mun = munchey(matrix);
	      ch = (char)('0' + mun);
	      mvaddch(matrix->getMunch().row + 5, matrix->getMunch().col + 5, ch);
	      growing = true;
       }

     //Moves the head of the snake
     matrix->Remove(cur_r, cur_c);
     matrix->snake->moveHead(cur_r, cur_c);
       

     //If it isn't growing, the tail wil move, otherwise, it will stay in place while it grows
       if(!growing) {
	   matrix->snake->moveTail();
	   matrix->Update(matrix->snake->getTail().row, matrix->snake->getTail().col);
	   mvaddch(matrix->snake->getTail().row + 5, matrix->snake->getTail().col + 5, ' ');
	 }
       
       //Checks the amount the snake is growing for
    if(growAmount > 0) {
	   snake++;
	   growAmount--;
	   if(growAmount == 0) {
	     growing = false;
	   }
	 }
       
       //Continue moving
       mvaddch(matrix->snake->body().row + 5, matrix->snake->body().col + 5, 'o');
       mvaddch(matrix->snake->getHead().row+ 5, matrix->snake->getHead().col + 5, '@');
       //Update score here
       mvaddstr(row + 5, col + 1, std::to_string(snake).c_str() );
       
       refresh();
   }
}

//This and the below function are left here from the original main.
void startup( void ) {
     initscr();	 /* activate the curses */
     curs_set(0);/* do not display the cursor */
     clear();	 /* clear the screen that curses provides */
     noecho();	 /* prevent the input chars to be echoed to the screen */
     cbreak();	 /* change the stty so that characters are delivered to the
		    program as they are typed--no need to hit the return key!*/
}

void terminate( void ) {
     mvcur( 0, COLS - 1, LINES - 1, 0 );
     clear();
     refresh();
     endwin();
}
