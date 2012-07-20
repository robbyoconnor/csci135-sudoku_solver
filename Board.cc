/******************************************************************************
Title: Board.cc
Author: Robert O'Connor
Created on: June 26, 2012
Description: Board represents one complete game of Board
Modifications:
 ******************************************************************************/
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <sstream>
#include <vector>
#include "Board.h"
#define ROWS 9
#define COLS 9
#define DEPTH 10 // for candidates array -- 0th element is false always

using namespace std;


// for initializing the this->candidates array this was immensely useful:
// http://stackoverflow.com/a/3969704/1508101

Board::Board(){
    this->board=new int*[ROWS]();
    this->candidates=new bool**[ROWS]();

    if(this->board&&this->candidates){ // just check to make sure.
        for(int i=0;i<ROWS;i++){
            this->board[i]=new int[COLS]();
            this->candidates[i]=new bool*[COLS]();
            for(int j=0;j<COLS;j++){
                this->candidates[i][j]=new bool[DEPTH]();
            }
        }
    }
}

Board::~Board(){
    // this is gonna be hairy...
    // time to clean up and delete pointers!
    clog<<"freeing all pointers...";
    for(int i=0;i<ROWS;i++){
        for(int j=0;j<COLS;j++){
            delete[] this->candidates[i][j];
            this->candidates[i][j]=NULL; // prevent dangling pointers

        }
    }
    delete[] this->candidates;
    delete[] this->board;
    this->candidates=NULL; // prevent dangling pointers
    this->board=NULL; // prevent dangling pointers

    clog<<"done."<<endl;
}

int** Board::getBoard() {
    return this->board;
}

void Board::printBoard(bool showCandidates){



    /** Prints the following:
      +-----------------------+
      | ? ? ? | 1 ? 5 | ? 9 ? |
      | 1 4 ? | ? ? ? | 6 7 ? |
      | ? 8 ? | ? ? 2 | 4 ? ? |
      -------------------------
      | ? 6 3 | ? 7 ? | ? 1 ? |
      | 9 ? ? | ? ? ? | ? ? 3 |
      | ? 1 ? | ? 9 ? | 5 2 ? |
      -------------------------
      | ? ? 7 | 2 ? ? | ? 8 ? |
      | ? 2 6 | ? ? ? | ? 3 5 |
      | ? ? ? | 4 ? 9 | ? 6 ? |
      +-----------------------+
     */
    cout<<"+-----------------------+"<<endl;
    unsigned char ch = '@';
    for(int i=0;i<9;i++){
        if(i%3==0&&i>0){ // print the divider for all but the first iteration.
            cout<<"-------------------------"<<endl;
        }
        for(int j=0;j<9;j++){
            ch++;
            if(j%3==0){
                cout<<"| ";
            }
            if(!showCandidates){
                if(this->board[i][j]!=0){
                    cout<<this->board[i][j]<<" ";
                }else{
                    cout<<"? ";
                }
            } else {
                if(this->board[i][j]==0) {
                    cout<<ch<<" ";
                } else {
                    cout<<this->board[i][j]<<" ";
                }
            }
        }

        cout<<"|"<<endl;
    }
    cout<<"+-----------------------+"<<endl;
}

// the proceeding three functions were inspired by: http://stackoverflow.com/q/9730280/1508101
// mainly the functions to validate rows, columns and boxes separated...

bool Board::validateRow(int number,int row){
   for (int i = 0; i < ROWS; i++) {
        if(this->board[row][i]==number) { // if it exists -- NOT valid
            return false;
        }
    }
    return true;
}

bool Board::validateColumn(int number,int col){
    for (int i = 0; i < COLS; i++) {
        if(this->board[i][col]==number) { // if it exists -- NOT valid.
            return false;
        }
    }
    return true;
}

bool Board::validateBox(int number,int row,int col){
    int r=(row/3) * 3;
    int c=(col/3) * 3;
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            if(this->board[r+i][c+j] > 0 && this->board[r+i][c+j]==number) { // if it exists -- NOT valid.
                return false;
            }
    return true;
}

bool Board::isBoardValid(int number,int row,int col){
    bool valid = this->board[row][col]==0 && validateBox(number,row,col) &&
        validateColumn(number,col) && validateRow(number,row);

    return valid;
}

void Board::solve(){
    // modified from https://github.com/wimleers/sudoku/blob/master/src/Sudoku.cpp#L166
     bool found = this->isBoardValid(); //Only enter the filling loop if the board is valid
    int numPossible;
    cout<<"Adding all candidates to the puzzle..."<<endl;
    for (int i = 0; i < ROWS; i++) // Preparation; set all element 0's to false, and all the rest to true
        for (int j = 0; j < ROWS; j++) {
            this->candidates[i][j][0] = false;
            for (int k = 1; k < 10; k++)
                this->candidates[i][j][k] = true;
        }
    while (!this->isSolved() && found) { // While we still found possible moves
        found = false; // if this is true, a valid candidate was found and filled in.
        for (int i = 0; i<ROWS; i++) {
            cout<<"Eliminating candidates..."<<endl;
            for (int j=0;j<COLS;j++) {
                numPossible = 0; // We keep the number of possibilities
                for (int k=0;k<=9;k++) { // Looking for possible solutions per box
                    if (this->candidates[i][j][k]) { // If it hasn't already been marked as impossible (we're working incrementally)
                        this->candidates[i][j][k] = this->isBoardValid(k,i,j);
                        if (this->candidates[i][j][k]) // If it is still a valid move
                            numPossible++;
                    }
                }
                if (numPossible == 1) {
                    for (int k = 1; k<=9; k++)
                        if (this->candidates[i][j][k])
                            this->board[i][j]= k;
                    found = true;
                }
            }
        }
    }
    if(!found) cout<<"No more candidates to eliminate."<<endl;

}

bool Board::isSolved(){
    bool solved=true;
    for(int i=0;i<ROWS;i++){
        for(int j=0;j<COLS;j++){
            if(!this->board[i][j]>0){
                return false;
            }
        }
    }
    return true;
}

bool Board::isBoardValid() {
    return this->isValidRows() && this->isValidCols() && this->isValidBoxes();
}
// the following 3 functions were adapted (or taken from https://github.com/wimleers/sudoku/blob/master/src/Board.cpp#L297
bool Board::isValidRows() {
    bool elementOccured[10];
    bool valid = true;

    for (int i = 0; valid && i<ROWS;i++) { // Iterate over the different columns of the board
        for (int j = 0; j < 10; j++) // Initialize the boolean array
            elementOccured[j] = false;
        for (int j = 0; valid && j<COLS; j++) {// Iterate over the current column
            int curElem = this->board[i][j];
            valid = !elementOccured[curElem]; // Board is still valid if element hasn't occured yet
            if (curElem != 0)
                elementOccured[curElem] = true;
        }
    }
    return valid;
}

bool Board::isValidCols() {
    bool elementOccured[10];
    bool valid = true;

    for(int i=0;i<COLS;i++) {
        for(int j=0;j<COLS;j++) {
            elementOccured[j] = false;
        }
        for(int j=0;j<COLS;j++) {
            int curElement = this->board[j][i];
            valid = !elementOccured[curElement];
            elementOccured[curElement] = curElement!=0;
        }
    }
    return valid;
}

bool Board::isValidBoxes() {

    bool elementOccured[10];
    bool valid = true;
    for (int startX = 0; valid && startX < 9; startX += 3) // Iterate over the blocks, horizontally
        for (int startY = 0; valid && startY < 9; startY += 3) { // Iterate over the blocks, vertically
            for (int j = 0; j < 10; ++j) // Initialize the boolean array
                elementOccured[j] = false;
            for (int i = startX; valid && (i % 3 != 0 || i == startX); ++i) // Iterate over the current block
                for (int j = startY; valid && (j % 3 != 0 || j == startY); ++j) {
                    int curElem = this->board[j][i];
                    valid = !elementOccured[curElem]; // Board is still valid if element hasn't occurred yet
                    if (curElem != 0)
                        elementOccured[curElem] = true;
                }
        }

    return valid;
}

string Board::getCandidatesFor(char ch,int row,int col){
    stringstream out;
    for(int k=0;k<DEPTH;k++){
        out<<ch<<": ";
        if(this->candidates[row][col][k]){
            out<<this->candidates[row][col][k]<<" ";
        }
    }
    return out.str();
}