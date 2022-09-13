INC=-I../stf -I../stf/sdb -I../stf/smv

all:
	clang++ ~/libstf.so $(INC) *.cpp -o ~/tictactoe
	~/tictactoe