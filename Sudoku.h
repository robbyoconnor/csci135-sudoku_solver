/******************************************************************************
Title: Sudoku.h
Author: Robert O'Connor
Created on: June 26, 2012
Description: Sudoku -- encapsulates the activity of the game itself including
checking candidate values and eliminating them.
 *****************************************************************************/
#ifndef SUDOKU_H
#define SUDOKU_H

#include "Board.h"

class Sudoku{
  public:
   /**
    * Handles getting the board from the user and processing it.
    */
   void enterBoard();

   /**
    * Delegates control to a function of the same name in the Board class.
    */
   void solve();

    /**
    * Pretty print the board to the screen.
    * @param printCandidates whether or not to print candidates.
    *
    */
   void printBoard(bool printCandidates);

  private:
    // the board -- all functionality is there.
    Board board;
};
#endif
