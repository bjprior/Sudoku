sudoku: main.o sudoku.o 
	g++ main.o sudoku.o -o sudoku

main.o: main.cpp sudoku.h
	g++ -g -c -Wall main.cpp  

sudoku.o: sudoku.cpp sudoku.h
	g++ -g -c -Wall sudoku.cpp  

clean:
	rm -f *.o sudoku


