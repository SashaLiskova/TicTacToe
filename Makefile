ticTac: TicTacGame.o main.o
	g++ TicTacGame.o main.o -o ticTac

TicTacGame.o: TicTacGame.cpp
	g++ -c TicTacGame.cpp

main.o: main.cpp
	g++ -c main.cpp

clean:
	rm *.o ticTac