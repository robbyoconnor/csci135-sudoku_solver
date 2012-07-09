/******************************************************************************
Title: Game.h
Author: Robert O'Connor
Created on: June 26, 2012
Description: Game -- encapsulates the activity of the game itself including
checking candidate values and eliminating them.
 *******************************************************************************/
#ifndef GAME_H
#define GAME_H
#include "Board.h"

class Game{
  public:
    // default constructor which will do quite a bit of lifting
    Game();

    // destructor to delete some pointers... a lot of them.
    ~Game();

    /**
     * Retrieve the current representation of the board.
     *
     */
    Board getBoard();

    /**
     * Set the current representation of the board.
     *
     */
    void setBoard(Board board);


    /**
     * This function will handle the heavy lifting of checking for candidate values and eliminating those candidates.
     * This is the sole function (aside from accessors and mutators for the Board field) that are exposed to the client.
     *
     */
    void solve();
/************************/

/** private members */
  private:
    // the final representation that will be written out
    // only thing exposed to the client.
    Board board;

    // used to generate the possible "candidate" values for given squares.
    // not exposed to the client.
    bool *candidates[9][9];


    /**
     * Validate a given row
     * @param number the number to search for
     * @param row the row to validate
     * @return true if valid, false otherwise.
     */
    bool validateRow(int number, int row);

    /**
     * Validate a given column
     * @param number the number to check
     * @param col the column to check
     * @return true if valid, false otherwise.
     */
    bool validateColumn(int number, int col);

    /**
     * Validate a given box
     * @param number the number to check
     * @param row the row which this box is part of
     * @param col the column that this box is part of
     * @return true if valid, false otherwise.
     */
    bool validateBox(int number,int row, int col);

    /**
     *
     * This handles recording the candidates that will need to be checked.
     * Pre-conditions: number is between 1 and 9; row and column are positive and not greater than 9.
     * Post-condition; The candidate[row][column][number-1] contains a 1.
     *
     * Note: row and column may be inverted.
     *
     * @param number the number to add
     * @param row the row in the board that this candidate corresponds to
     * @param col the column that this candidate corresponds to
     * @param clear flag to tell the function to clear that value. Default value is false; set to true to clear.
     */
    void setCandidateValue(int number,int row,int col, bool clear);

    /**
     * This function simply does in one goes through and sees what's not in each row...and adds that number
     * as a candidate
     */
    void determineCandidates();

    /**
     * Determines if the given number is a candidate
     *
     * Note: row and column may be inverted.
     * @param number the number to check
     * @param row the row to check
     * @param col the column to check
     * @return true if its a candidate false otherwise.
     */
   bool isCandidate(int number, int row, int col);
};
#endif
