/******************************************************************************
Title: Cell.cc
Author: Robert O'Connor
Created on: June 26, 2012
Description: Container class for mapping Cells to placeholder strings.
Modifications:
 ******************************************************************************/
#include "Cell.h"

Cell::Cell(int row, int col){
    this->row = row;
    this->col = col;
}

int getRow() {
    return this->row;
}

int getCol() {
    return this->col;
}