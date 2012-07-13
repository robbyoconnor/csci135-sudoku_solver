/******************************************************************************
Title: Board.cc
Author: Robert O'Connor
Created on: June 26, 2012
Description: Board represents one complete game of Board
Modifications:
 ******************************************************************************/
#include <iostream>
#include "Board.h"
#define ROWS 9
#define COLS 9
#define DEPTH 9 // for candidates array

/** TODO: REMOVE DEBUGGING CODE!!!! */


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
    using namespace std;
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
    using namespace std;


    string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    //string symbols = "!@#$%^&*()[]{}|,.<>*-+~`:;_\\/";

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
        if(i%3==0 && i>0) { // print the divider for all but the first iteration.
            cout<<"-------------------------"<<endl;
        }
        for(int j=0;j<9;j++){
            if(j%3==0){
                cout<<"| ";
            }
            cout<<this->board[i][j]<<" ";

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
            std::cout<<std::endl<<number<<" exists in row "<<row<<std::endl; //TODO: remove
            return false;
        }
    }
    return true;
}

bool Board::validateColumn(int number,int col){
    for (int i = 0; i < ROWS; i++) {
        if(this->board[i][col]==number) {
            std::cout<<std::endl<<number<<" exists in column "<<col<<std::endl; //TODO: remove
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
                std::cout<<std::endl<<number<<" exists in the box enclosed by "<<row<<" and "<<col<<std::endl; //TODO: remove
                std::cout<<"Coordinates within the box is ("<<(row+i)<<","<<(col+j)<<")"<<std::endl; //TODO: remove
                return false;
            }
    return true;

}

bool Board::isBoardValid(int number,int row,int col){
    return this->board[row][col]==0 && validateBox(number,row,col) &&
        validateColumn(number,col)&& validateRow(number,row);
}
void Board::setCandidateValue(int number,int row,int col,bool clear){
    // number *MUST* be between 1 and 9.
    if(!(number>9||row>9||col>9)){
        if(!(number<=0 || row<=0 || col<=0)){
            if(number==1){
                this->candidates[row][col][0]=(clear?0:1);
            }else{
                this->candidates[row][col][number-1]=(clear?0:1);
            }
        }
    }
}



bool Board::isCandidate(int number,int row,int col){
    // number *MUST* be between 1 and 9.
    // checked both bounds in separate if statements for clarity.
    if(!(number>9||row>9||col>9)){
        if(!(number<=0||row<=0||col<=0)){
            // Handle the number 1 different than all others so we don't go out of bounds.
            if(number==1){
                if(this->candidates[row][col][0]>0){
                    return true;
                }
            }else{
                return this->candidates[row][col][number-1]>0;

            }
        }
    }
}

void Board::determineCandidates(){
    using namespace std; //TODO: remove
    // we short-cut if one of these fails -- it is assumed all will fail
    for(int i=0;i<ROWS;i++){
        for(int j=0;j<COLS;j++){

            cerr<<"\nCandidates found for cell ("<<i<<","<<j<<"):"; //TODO: remove
            for(int k=1;k<10;k++){
                if(this->isBoardValid(k,i,j)){
                    // so it meets this criteria...let's add it.
                     cerr<<k<<" "; //TODO REMOVE
                    setCandidateValue(k,i,j,false);
                }
            }
        }
        cerr<<endl; //TODO: remove
    }
    for(int i=0;i<ROWS;i++) {
        for(int j=0;j<COLS;j++) {
            cout<<"\nCandidates for cell ("<<i<<","<<j<<") is: "; //TODO REMOVE
            for(int k=0;k<DEPTH;k++) {
                cout<<candidates[i][j][k]<<" "; //TODO: remove
            }
            cout<<endl; //TODO: remove
        }
    }
}

void Board::solve(){
    using namespace std;
    // first determine the candidate values for each cell in each row and each column (this covers the 9x9 sub-grids)
    cout<<"Adding all candidates to the puzzle...";
    determineCandidates();
    cout<<"done."<<endl;
    // now we try and eliminate candidates -- once checked, we must clear them as a candidate.
    for(int i=0;i<ROWS;i++){
        cout<<"Eliminating candidates from puzzle..."<<endl;
        for(int j=0;j<COLS;j++){
            for(int k=1;k<10 && !isSolved(); k++){
                if(isCandidate(k,i,j)){
                    if(isBoardValid(k,i,j)){
                        this->board[i][j]=k;
                        }
                    }
                }
            }
        }
    cout<<"done."<<endl;
    cout<<"No more candidates to eliminate."<<endl;
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