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
    // default constructor
    Cell();
    /**
     * Construct something useful...
     * @param row the row
     * @param col the column
     */
    Cell(int row, int col);

    // get the row for the client
    int getRow();

    // get the column for the client
    int getCol();


    /**
     * This behaves as follows:
     * if this->row < b.getRow() *AND* this->col < b.getCol() we return true
     * otherwise false.
     * @param b the comparison
     * @return see above.
     */
    bool operator<(const Cell& b) const;
    /**
     * If values are identical that is the row and col values are equal then it is true.
     * @param b the comparison.
     * @return
     */
    bool operator==(const Cell& b) const;

  private:
    int row;
    int col;
};

#endif

