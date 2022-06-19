#include <iostream>
#include <random>
#include <algorithm>
#include <fstream>

#define STR_EMPTY " - "
#define STR_CROSS " x "
#define STR_NOUGHT " 0 "

#define STR_USER_INPUT "USER TURN: [i][j] in range of 0 to size expected:\n"
#define STR_MOVE_IS_BUSY "MOVE IS BUSY, TRY ANOTHER ONE\n"
#define STR_WRONG_VALS "WONRG VALUES, TRY ANOTHER ONE\n"

#define WIN 1
#define LOOSE -1
#define DRAW 0


enum TypeOfMove{cross, nought, empty};

class TicTacGame
{
    //by default comp is 0;
    private:
        int size;
        int winMovesNumber;
        int **field;
        bool isCompCross;
        int movesLeft;



    public:
        TicTacGame();
        TicTacGame(int size, int winMovesNumber,bool isCompCross, bool isRand=false);

        ~TicTacGame();
        
        int getSize();
        int getWinMovesNumber();
        void allocateEmptyCells();
        
        bool isMoveFree(int i, int j, int** field);
        
        //interface
        std::string toStringField(int ** newField);
        bool userMove(); 
        void computerMove();
        void  setRandomMove(int& i, int& j);

        bool isIputCorrect(int i,int j);

        //for testing
        void generateRandFiled();

        int rowWinEval(int **fieldC);
        int diagonalWinEval(int **fieldC);
        int generalWinEval(int **fieldC, int movesLeftC);

        void play();
        
        void setCoppyOfField(int ** oldField,int ** newField);
        void deleteField(int ** newField);

        int miniMax(int copyMovesLeft, int** copyField, bool maxMin,int alpha, int beta);

        //for testing
        void fieldGenerateDiagonalWins();
        void fieldGEnerateRowWins(int **fieldC, int movesLeftC);
        
        //0 
        //comp 1
        //not -1


};