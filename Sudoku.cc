/******************************************************************************
Title: Sudoku.cc
Author: Robert O'Connor
Created on: June 26, 2012
Description: Sudoku-- acts as a broker between the Board class (
 * hiding much of its functionality behind a layer of abstraction).
Modifications:
 ******************************************************************************/

#include "Sudoku.h"
#include "Board.h"
#include <iostream>

#define ROWS 9
#define COLS 9

using namespace std;

void Sudoku::enterBoard(){
    char c;
    for(int i=0;i<ROWS;i++){
        for(int j=0;j<COLS;j++){
            cin>>c;
            if(c!='?'){
                this->board.getBoard()[i][j]=(int)c-'0';
            }
        }
    }
}

void Sudoku::solve() {
    this->board.solve();
}

void Sudoku::printBoard(bool showCandidates) {
    this->board.printBoard(showCandidates,false,0,0,0);
}

