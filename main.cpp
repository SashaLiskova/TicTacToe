#include "TicTacGame.h"

int main()
{
    //TicTacGame game(3,3,true, true);
    std::cout<<"give the size:\n";
    int size;
    int numOfWins;

    std::cin>>size>>numOfWins;

    //generate x win
    TicTacGame game(size,numOfWins,true);
    game.play();

    


}

