/******************************************************************************
Title: Cell.h
Author: Robert O'Connor
Created on: June 26, 2012
Description: Container class for mapping Cells to placeholder strings.
Modifications:
 ******************************************************************************/

#ifndef CELL_H
#define	CELL_H

class Cell{
  public:
    Cell();
    int getRow();
    int getCol();
  private:
    int row;
    int col;
};

#endif	/* CELL_H */

