/******************************************************************************
Title: Board.h
Author: Robert O'Connor
Created on: June 26, 2012
Description: Board class for Sudoku game.
 ******************************************************************************/
#ifndef BOARD_H
#define BOARD_H

 #include <string>

class Board{
  public:
    /** constructors **/
    Board();

    /** destructor **/
    ~Board();

    /**
     * Current representation of the board.
     */
    int** getBoard();


    /**
     * Pretty print the board to the screen.
     * @param printCandidates whether or not to print candidates (Default value is false).
     *
     */
    void printBoard(bool showCandidates);

    /**
     * This function will handle the heavy lifting of checking for candidate values and eliminating those candidates.
     * This is the sole function (aside from accessors and mutators for the Board field) that are exposed to the client.
     *
     */
    void solve();

    /************************/

    /** private members and functions */
      private:

        /**
     *
     * Places in the board without a "definite" value will contain a "0."
     * This is a 9x9 2D array.
     *
     */
    int **board;

    // used to generate the possible "candidate" values for given squares.
    // not exposed to the client.
    bool ***candidates;

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
     * Helper function that combines all validity checks
     * @param number the number to check
     * @param row the row
     * @param col the column
     * @return true if valid -- false otherwise.
     */
    bool isBoardValid(int number, int row, int col);

    /**
     * Helper function to check the board as a whole automatically.
     * @return true if the board is valid; false otherwise.
     */
    bool isBoardValid();

    /**
     * Checks the rows for validity
     * @return true if any numbers occur more than once.
     */
    bool isValidRows();

    /**
     * Checks the rows for validity
     * @return true if any numbers occur more than once.
     */
    bool isValidCols();

    /**
     * Checks the rows for validity
     * @return true if any numbers occur more than once.
     */
    bool isValidBoxes();


    /**
     *
     * Checks for a solved board.
     * @returns true if there are no empty cells (value > 0 for all 81 cells)
     *
     */
    bool isSolved();

    /**
     * Helper function for printBoard() to get the list of candidates as a string.
     * @param row the row
     * @param col the col
     */
    std::string getCandidatesFor(char character, int row,int col);

};
#endif
