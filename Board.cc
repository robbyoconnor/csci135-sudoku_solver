/******************************************************************************
Title: Board.cc
Author: Robert O'Connor
Created on: June 26, 2012
Description: Board represents one complete game of Board
Modifications:
 ******************************************************************************/
#include <iostream>
#include <map>
#include <ctime>
#include <cstdlib>
#include <string>
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

void Board::printBoard(bool showCandidates, bool debug, int number, int row, int col){



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
    for(int i=0;i<9;i++){
        if(i%3==0&&i>0){ // print the divider for all but the first iteration.
            cout<<"-------------------------"<<endl;
        }
        for(int j=0;j<9;j++){
            if(j%3==0){
                cout<<"| ";
            }
            if(this->getNumberOfCandidatesFor(i,j)==1) {
                cout<<this->board[i][j]<<" "; // output if we have a singular candidate
            } else { // otherwise we put a place-holder
                map<Cell,char> map = getPlaceHolders(); // get the placeholders
                map<Cell,char>::iterator it = map.begin();
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
        if(this->board[i][row]==number) {
            return false;
        }
    }
    return true;
}

bool Board::validateColumn(int number,int col){
    for (int i = 0; i < ROWS; i++) {
        if(this->board[i][col]==number) {
            return false;
        }
    }
    return true;
}

bool Board::validateBox(int number,int row,int col){
    row=(row/3) * 3;
    col=(col/3) * 3;
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            if(this->board[row+i][col+j] > 0 && this->board[row+i][col+j]==number) {
                return false;
            }
    return true;

}

bool Board::isBoardValid(int number,int row,int col){
    bool valid = this->board[row][col]==0 && validateBox(number,row,col) &&
        validateColumn(number,col) && validateRow(number,row);

    return valid;
}

void Board::setCandidateValue(int number,int row,int col,bool clear){
    // number *MUST* be between 1 and 9.
    if(!(number>9||row>9||col>9)){
        if(!(number>=1 || row<=0 || col<=0)){
            this->candidates[row][col][number]=(clear?0:1);

        }
    }
}



bool Board::isCandidate(int number,int row,int col){
    // number *MUST* be between 1 and 9.
    // checked both bounds in separate if statements for clarity.
    if(!(number>9||row>9||col>9)){
        if(!(number<=0||row<=0||col<=0)){
            return this->candidates[row][col][number]>0;
        }
    }
}

void Board::initializeCandidates(){
    cout<<"Adding candidates to the puzzle."<<endl;
    for(int i=0;i<ROWS;i++){
        for(int j=0;j<COLS;j++){
            for(int k=1;k<10;k++){
                this->candidates[i][j][k] = 1;
            }
        }
    }
}

void Board::solve(){
    this->initializeCandidates();
    this->eliminateCandidates();
    this->addDefinitesToBoard();
}

bool Board::isSolved(){
    for(int i=0;i<ROWS;i++){
        for(int j=0;j<COLS;j++){
            if(!this->board[i][j]>0)
                return false;
        }
    }
    return true;
}



int Board::getNumberOfCandidatesFor(int row,int col) {
    int count=0;
    for(int i=0;i<ROWS;i++) {
        for(int j=0;j<COLS;j++) {
            for(int k=0;k<DEPTH;k++) {
                if(this->candidates[i][j][k]>0)
                    count++;
            }
        }
    }
    return count;
}

void Board::eliminateCandidates() {
    for(int i=0;i<ROWS;i++) {
        cout<<"Eliminating candidates..."<<endl;
        for(int j=0;j<COLS;j++) {
            for(int k=0;k<DEPTH;k++) {
                if(this->isCandidate(k,i,j) && !this->isBoardValid(k,i,j)) {
                    this->setCandidateValue(k,i,j,true); // eliminate it as a candidate!
                }
            }
        }
    }
    cout<<"done."<<endl;
    cout<<"No more candidates to eliminate."<<endl;
}

void Board::addDefinitesToBoard(){
    for(int i=0;i<ROWS;i++){
        for(int j=0;j<COLS;j++){
            for(int k=1;k<10&& !isSolved();k++){
                if(!this->getNumberOfCandidatesFor(i,j)>1 && this->isCandidate(k,i,j)) {
                    this->board[i][j] = k;
                    this->setCandidateValue(k,i,j,true); // clear it now.
                }
            }
        }
    }
}

map<Cell,string> Board::getPlaceHolders() {

    string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"; // first will try and use this (shrinking it as we use it.
    string symbols = "!@#$%^&*()[]{}|,.<>*-+~`:;_\\/"; // then go to this.
    srand((unsigned)time(NULL)); // seed random number generator.
    for(int i=0;i<ROWS;i++){
        for(int j=0;j<COLS;j++){
            for(int k=1;k<10&& !isSolved();k++){ // indices for candidates start at 1.
                if(getNumberOfCandidatesFor(i,j)>1) {
                    Cell c(i,j);
                    char ch  = '';
                    if(letters.length()>0) { // we randomly pick a letter and erase it.
                        int idx = rand() % letters.length();
                        ch = letters[idx];
                        string::iterator it = letters.begin()+idx;
                        letters.erase(it); // remove that letter.

                    } else {
                        int idx = rand() % symbols.length();
                        ch = symbols[idx];
                        string::iterator it = symbols.begin()+idx;
                        symbols.erase(it); // remove that symbol.
                    }
                    map[c] = ch; // add it to the map

                }
            }
        }
    }
    return map;
}