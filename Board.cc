/******************************************************************************
Title: Board.cc
Author: Robert O'Connor
Created on: June 26, 2012
Description: Board represents one complete game of Sudoku
Modifications:
 ******************************************************************************/

#include "Board.h"
#define ROWS 9
#define COLS 9
#include <iostream>
Board::Board(int **board) {
    board = board;
}

Board::Board() {
    for (int i = 0; i < ROWS; i++) {        
        board[i] = new int[COLS]();
    }
}

Board::~Board() {
    // pointer clean up happens here->
    // first, iterate and delete all sub-arrays
    // then, we delete the entire thing->
    for (int i = 0; i < ROWS; i++) {
        delete[] board[i];
    }
    delete[] board;
}

int** Board::getBoard() {
    return board;
}

void Board::setBoard(int** b) {
    board = b;
}


void Board::printBoard(){

}
