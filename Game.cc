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
#include <cstdlib>
#include <new>
#define ROWS 9
#define COLS 9
#define DEPTH 9 // for candidates array
// for initializing the candidates array this was immensely useful:
// http://stackoverflow.com/a/3969704/1508101
Game::Game() {
    definites = new int*[ROWS]();
    candidates = new bool**[ROWS]();
    if(definites && candidates) { // just check to make sure.
        for(int i=0;i<ROWS;i++) {
            definites[i] = new int[COLS]();
            candidates[i] = new bool*[COLS]();
            for(int j=0;j<COLS;j++) {
                candidates[i][j] = new bool[DEPTH]();
            }
        }
    }
}
Game::~Game() {
    using namespace std;
    // this is gonna be hairy...
    // time to clean up and delete pointers!
    cerr<<"freeing all pointers...";
    for(int i=0;i<ROWS;i++) {
        for(int j=0;j<COLS;j++) {
            delete[] candidates[i][j];
            candidates[i][j] = NULL;

        }
    }
    delete[] candidates;
    delete[] definites;
    candidates = NULL;
    definites = NULL;

    cerr<<"done"<<endl;
}

void Game::solve() {
    using namespace std;
    // first determine the candidate values for each cell in each row and each column (this covers the 9x9 sub-grids)
    cout<<"Adding all candidates to the puzzle..."
    determineCandidates();
    cout<<"done."<<endl;
    // now we try and eliminate candidates -- once checked, we must clear them from the candidates/
    for(int i=0;i<ROWS;i++) {
        cout<<"Eliminating candidates from puzzle..."<<endl;
        for(int j=0;j<COLS;j++) {
            for(int k=1;k<10;k++) {
                if(isCandidate(k,i,j)) {
                    if((definites[i][j] > 0) && validateRow(k,i) && validateColumn(k,j) && validateBox(k,i,j)) {
                        setCandidateValue(k,i,j,true); // clear it as a candidate...
                        definites[i][j] = k;
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
        if(definites[row][col] == number) {
            return false;
        }
    }
    return true;
}

bool Game::validateColumn(int number, int col) {
    for(int row=0;row<ROWS;row++) {
        if(definites[row][col] == number) {
            return false;
        }
    }
    return true;
}

bool Game::validateBox(int number,int row,int col){

    row=(row/3) * 3;
    col=(col/3) * 3;

    for(int r=0;r<3;r++)
        for(int c=0;c<3;c++)
            if(definites[row+r][col+c]==number)
                return false;

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

bool Game::isSolved() {
    for(int i=0;i<ROWS;i++) {
        for(int j=0;j<COLS;j++) {
            if(!definites[i][j] > 0)
                return false;
        }
    }
    return true;
}
void Game::enterBoard() {
    using namespace std;
    char c;
    for(int i=0;i<ROWS;i++) {
        for(int j=0;j<COLS;j++) {
            cin >> c;
            if(c != '?') {
              definites[i][j] = (int)c - '0';
            }
        }
    }
}

void Game::printBoard(bool printCandidates){
    using namespace std;
    /**
        +-----------------------------+
        | 6  7  2 | 1  4  5 | 3  9  8 |
        | 1  4  5 | 9  8  3 | 6  7  2 |
        | 3  8  9 | 7  6  2 | 4  5  1 |
        |---------------------------- |
        | 2  6  3 | 5  7  4 | 8  1  9 |
        | 9  5  8 | 6  2  1 | 7  4  3 |
        | 7  1  4 | 3  9  8 | 5  2  6 |
        |-----------------------------|
        | 5  9  7 | 2  3  6 | 1  8  4 |
        | 4  2  6 | 8  1  7 | 9  3  5 |
        | 8  3  1 | 4  5  9 | 2  6  7 |
        +-----------------------------+
     */
    cout<<"+-----------------------------------+"<<endl;
    for(int i=0;i<ROWS;i++) {
        cout<<"| ";
        for(int j=0;j<COLS;j++) {
            cout<<definites[i][j]<< " ";


        }
        cout<<endl;
    }
    cout<<"+-----------------------------------+"<<endl;
}

void Game::printBox(int row, int col, bool showCandidates) {


}