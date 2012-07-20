/******************************************************************************
Title: main.cc
Author: Robert O'Connor
Created on: June 26, 2012
Description: Main entry for the application.
Usage: sudoku
Build with: make
Modifications:
 ******************************************************************************/
#include "Sudoku.h"
#include <iostream>
#include <string>

#define ROWS 9
#define COLS 9
using namespace std;

//function prototypes
void playGame();
void printMenu();

int main(int argc,char *argv[]){
    Sudoku sudoku;
    cout<<"This program will attempt to solve a user-defined, partially filled out Sudoku puzzle."<<endl;
    cout<<"In the event that it cannot, all candidates will be listed."<<endl;
    cout<<"--------------------------------------------------------------------------------------"<<endl;
    bool done = false;
    do {
        cin.clear();
        cout<<"\n\nPlease use the associated numbers to select your option."<<endl;
        cout<<"--------------------------------------------------------"<<endl;
        cout<<"1. Solve a puzzle"<<endl;
        cout<<"2. Quit"<<endl;
        cout<<"Selection: ";
        int answer;
        cin>>answer;
        cout<<endl;
        switch(answer) {
            case 1:
                sudoku.enterBoard();
                sudoku.printBoard(false);
                sudoku.solve();
                sudoku.printBoard(true);
                break;
            case 2:
                done = true;
                break;
            default:
                cout<<"Invalid selection."<<endl;
                break;

        }
    }while(!done);
    return 0;
}