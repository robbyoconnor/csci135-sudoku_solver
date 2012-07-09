CC=g++
FILES=Board.cc Game.cc main.cc 
sudoku: 
	$(CC) -g $(FILES) -o sudoku	

clean: 
	rm -rf sudoku* 





# build tests
build-tests: .build-tests-post

.build-tests-pre:
# Add your pre 'build-tests' code here...

.build-tests-post: .build-tests-impl
# Add your post 'build-tests' code here...


# run tests
test: .test-post

.test-pre:
# Add your pre 'test' code here...

.test-post: .test-impl
# Add your post 'test' code here...
