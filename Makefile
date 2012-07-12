CC=g++
FILES=Sudoku.cc Board.cc main.cc
sudoku:
	$(CC) -g $(FILES) -o sudoku

clean:
	rm -rf sudoku*