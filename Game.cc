/******************************************************************************
Title: Game.cc
Author: Robert O'Connor
Created on: June 26, 2012
Description: Game-- encapsulates the activity of the game itself including
checking candidate values and eliminating them
Modifications:
******************************************************************************/

#include "Game.h"
#include <iostream>
#define ROWS 9
#define COLS 9
#define DEPTH 9 // for candidates array

Game::Game() {
    Board b;
    for(int i=0;i<ROWS;i++) {
        for(int j=0;j<ROWS;j++) {
            candidates[i][j] = new bool[COLS]();
            for(int k=0;k<DEPTH;k++) {
                candidates[i][j][k] = new bool[ROWS][COLS][DEPTH](); // initialize the candidates array
           }
        }
    }
}

Game::~Game() {
    // this is gonna be hairy...
    // time to clean up and delete pointers!
    for(int i=0;i<ROWS;i++) {
        for(int j=0;j<ROWS;j++) {
          delete[] candidates[i][j];
        }
    }
    delete[] candidates;
}

Board Game::getBoard() {
    return board;
}

void Game::setBoard(Board b) {
    board = b;
}




void Game::solve() {
    using namespace std;
    // first determine the candidate values for each cell in each row and each column (this covers the 9x9 sub-grids)
    cout<<"Adding all candidates to the puzzle...";
    determineCandidates();
    cout<<"done."<<endl;
    // now we try and eliminate candidates -- once checked, we must clear them from the candidates/
    for(int i=0;i<ROWS;i++) {
        cout<<"Eliminating candidates from puzzle...";
        for(int j=0;j<COLS;j++) {
            for(int k=1;k<10;k++) {
                if(isCandidate(k,i,j)) {
                    if((board.getBoard()[i][j] > 0) && validateRow(k,i) && validateColumn(k,j) && validateBox(k,i,j)) {
                        setCandidateValue(k,i,j,true); // clear it as a candidate...
                        board.getBoard()[i][j] = k;
                    } else {
                        continue;
                    }
                }
            }
        }
    }
    cout<<"done"<<endl;
    cout<<"No more candidates to eliminate."<<endl;
}

// the proceeding three functions were inspired by: http://stackoverflow.com/q/9730280/1508101
// mainly the functions to validate rows, columns and boxes separated...
bool Game::validateRow(int number, int row) {
    for(int col=0;col<COLS;col++) {
        if(board.getBoard()[row][col] == number) {
            return false;
        }
    }
    return true;
}

bool Game::validateColumn(int number, int col) {
    for(int row=0;row<ROWS;row++) {
        if(board.getBoard()[row][col] == number) {
            return false;
        }
    }
    return true;
}

bool Game::validateBox(int number, int row, int col) {
    // The algorithm for handling the boxes was inspired from: http://stackoverflow.com/a/4718285/1508101
    int bx = (row/3)*3;
    int by = (col/3)*3;
    for(;bx<bx+3;bx++) {
        for(;by+3;by++) {
            if(board.getBoard()[bx][by] == number) {
                return false;
            }
        }
    }
    return true;
}

void Game::setCandidateValue(int number, int row, int col, bool clear=false) {
    // number *MUST* be between 1 and 9.
    if(!(number > 9 || row > 9 || col > 9)) {
        if(!(number <= 0 || row <= 0 || col <= 0)) {
            if(number == 1) {
                candidates[row][col][0] = (clear ? 0 : 1);
            } else {
                candidates[row][col][number-1] = (clear ? 0 : 1);
            }
        }
    }
}

void Game::determineCandidates() {
    // we short-cut if one of these fails -- it is assumed all will fail
    for(int i=0;i<ROWS;i++) {
        for(int j=0;j<COLS;j++) {
            for(int k=1;k<10;k++) {
                if(validateRow(j,i)) {
                    if(validateColumn(k,j)) {
                        if(validateBox(k,i,j)) {
                            // so it meets all criteria...let's add it.
                            setCandidateValue(k,i,j);
                        }
                    }
                }
            }
        }
    }
}

bool Game::isCandidate(int number, int row, int col) {
    // number *MUST* be between 1 and 9.
    // checked both bounds in separate if statements for clarity.
    if(!(number > 9 || row > 9 || col > 9)) {
        if(!(number <= 0 || row <= 0 || col <= 0)) {
            // Handle the number 1 different than all others so we don't go out of bounds.
            if(number == 1) {
                if(candidates[row][col][0] > 0) {
                    return true;

                } else {
                    return false;
                }
            } else {
                if(candidates[row][col][number-1] > 0) {
                    return true;
                } else {
                    return false;
                }
            }
        }
    }
}