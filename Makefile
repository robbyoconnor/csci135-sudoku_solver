CC=g++
FILES=Game.cc main.cc
sudoku:
	$(CC) -g $(FILES) -o sudoku

clean:
	rm -rf sudoku*