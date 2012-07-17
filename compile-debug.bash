#!/bin/bash

rm -rf debugging.txt ; make clean sudoku ; ./sudoku.exe < puzzle &>debugging.txt
