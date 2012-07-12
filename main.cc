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

string enterDefinites(Sudoku g);

int main(int argc,char *argv[]){
    Sudoku g;
    cout<<"This program will attempt to find the solution to";
    cout<<"user-defined Sudoku puzzles. If a solution cannot be found,";
    cout<<"all possible candidates for each cell will be shown."<<endl;
    cout<<"---------------------------------------------------------------------"<<endl;
    cout<<"Enter the starting state of the Sudoku puzzle."<<endl;
    cout<<"line by line with no spaces between each tile."<<endl;
    cout<<"If a tile is empty, enter \'?\'"<<endl;
    g.enterBoard();
    g.printBoard(false);
    g.solve();
    g.printBoard(true);
    return 0;
}