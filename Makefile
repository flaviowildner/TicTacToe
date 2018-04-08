GCC=gcc
FILE=TicTacToe


all:
	$(GCC) $(FILE).c -o $(FILE)
clean:
	rm -f $(FILE)
