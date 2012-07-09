/******************************************************************************
Title: Board.h
Author: Robert O'Connor
Created on: June 26, 2012
Description: Board class for Sudoku game.
 ******************************************************************************/
#ifndef BOARD_H
#define BOARD_H

class Board{
  public:
    /** constructors **/
    Board();
    Board(int**);

    /** destructor **/
    ~Board();

    /**
     * Current representation of the board.
     */
    int** getBoard();

    /**
     * Set the current representation of the board.
     *
     * @param board the board that will represent the final layout of the solved or incomplete board.
     */
    void setBoard(int **board);

    /**
     * Pretty prints out the Sudoku board
     */
    void printBoard();
  private:
    /**
     *
     * Places in the board without a "definite" value will contain a "0."
     * This is a 9x9 2D array.
     *
     */
    int** board;

};
#endif
