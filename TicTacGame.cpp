#include "TicTacGame.h"

//empty constr
TicTacGame::TicTacGame()
{
    size=0;
    winMovesNumber=0;
    field=NULL;
}

TicTacGame::TicTacGame(int size, int winMovesNumber, bool isCompCross,bool isRand)
{
    this->size=size;
    this->winMovesNumber=winMovesNumber;
    this->isCompCross=isCompCross;

    field = new int*[size];

    if(isRand)
    {
        generateRandFiled();
        movesLeft=0;
    }else
    {
        allocateEmptyCells();
        movesLeft=size*size;
    }
}

TicTacGame::~TicTacGame()
{
    for(int i=0; i<size;i++)
    {
        delete field[i];
    }
    delete field;

    field =NULL;
}

void TicTacGame::allocateEmptyCells()
{
    for(int i = 0; i< size; i++)
    {
        field[i]=new int[size];

        for(int j=0; j<size; j++)
        {
            field[i][j]=TypeOfMove::empty;
        }
    }
}

std::string TicTacGame::toStringField(int ** newField)
{
    std::string output="";
    
    for(int i=0; i<size; i++)
    {
        for(int j=0; j<size; j++)
        {
            switch(newField[i][j])
            {
                case TypeOfMove::empty:
                    output+=STR_EMPTY;
                    break;
                case TypeOfMove::cross:
                    output+=STR_CROSS;
                    break;
                case TypeOfMove::nought:
                    output+=STR_NOUGHT;
                    break;
            }
            
        }
        
        output+="\n";

    }
    return output;
}

void TicTacGame::generateRandFiled()
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(TypeOfMove::cross, TypeOfMove::nought);

    for(int i=0; i<size; i++)
    {
        field[i]=new int[size];
        for(int j=0; j<size; j++)
        {
            field[i][j]=dist6(rng);
        }
    }
}

bool TicTacGame::isMoveFree(int i, int j, int** newField)
{
    return newField[i][j]==TypeOfMove::empty;
}

bool TicTacGame::userMove()
{
    std::cout<<STR_USER_INPUT;
    //todo-1: possible garbage vals
    //so its' better get string and get out of it int and recheck 
    
    int i,j;
    std::cin>>i>>j;

    while(!isMoveFree(i,j,field))
    {
        std::cout<<STR_MOVE_IS_BUSY;
        std::cin>>i>>j;
    }

  
    isCompCross?field[i][j]=TypeOfMove::nought:field[i][j]=TypeOfMove::cross;
  

    return true;
    
}

//todo-1:
bool TicTacGame::isIputCorrect(int i,int j)
{
    return i>=0 && i<size && j>=0 && j<size;
}

int TicTacGame::rowWinEval(int **fieldC)
{
    int horizontalWinCount = 0;
    int verticalWinCout = 0;


    for(int i=0; i<size; i++)
    {
        for(int j=0; j<size-1; j++)
        {
            
            if(fieldC[i][j]==fieldC[i][j+1]&&fieldC[i][j]!=TypeOfMove::empty)
            {
                horizontalWinCount++;

                //std::cout<<"vals "<<i<<" "<<j<<" & "<<i<<" "<<j+1<<" horizontalWinCount "<<horizontalWinCount<<"\n";

                if(horizontalWinCount==winMovesNumber-1)
                {
                    if(isCompCross)
                    {
                        int eval = fieldC[i][j] == TypeOfMove::cross?WIN:LOOSE;
                        return eval;
                    }else
                    {
                        int eval = fieldC[i][j] == TypeOfMove::cross?LOOSE:WIN;
                        return eval;
                    }
                    
                }

            }else
            {
                horizontalWinCount=0;
            }

            
            if(fieldC[j][i]==fieldC[j+1][i]&&fieldC[j][i]!=TypeOfMove::empty)
            {
                verticalWinCout++;
                //std::cout<<"vals "<<j<<" "<<i<<" & "<<j+1<<" "<<i<<" verticalWinCout  "<<verticalWinCout<<"\n";

                if(verticalWinCout==winMovesNumber-1)
                {
                    if(isCompCross)
                    {
                        int eval = fieldC[j][i] == TypeOfMove::cross?WIN:LOOSE;
                        return eval;
                    }else
                    {
                        int eval = fieldC[j][i] == TypeOfMove::cross?LOOSE:WIN;
                        return eval;
                    }
                    
                }
            }else
            {
                verticalWinCout=0;
            }
            
        }

        verticalWinCout=0;
        horizontalWinCount=0;

    }

    return DRAW;
}

int TicTacGame::diagonalWinEval(int **fieldC)
{
    int leftDiagonalUpCount=0;
    int leftDiagonalDownCount=0;

    int rightDiagonalUpCount=0;
    int rightDiagonalDownCount=0;


    for(int i=0; i<=size-winMovesNumber;i++)
    {
        for(int j=0; j<size-1-i;j++)
        {
            //fpr up part
            if(fieldC[j][j+i]==fieldC[j+1][j+i+1] && fieldC[j][j+i] != TypeOfMove::empty)
            {
                leftDiagonalUpCount++;

                 if (leftDiagonalUpCount == winMovesNumber - 1)
                 {
                    if (isCompCross)
                    {
                        int eval = fieldC[j][j+i] == TypeOfMove::cross ? WIN : LOOSE;
                        return eval;
                    }
                    else
                    {
                        int eval = fieldC[j][j+i] == TypeOfMove::cross ? LOOSE : WIN;
                        return eval;
                    }
                 }

            }else
            {
                leftDiagonalUpCount=0;
            }
            
            //for down part no need to recount twice for main deiagonal
            if (i != 0)
            {
                if (fieldC[j + i][j] == fieldC[j + i + 1][j + 1] && fieldC[j + i][j] != TypeOfMove::empty)
                {

                    leftDiagonalDownCount++;

                    if (leftDiagonalDownCount == winMovesNumber - 1)
                    {
                        if (isCompCross)
                        {
                            int eval = fieldC[j + i][j] == TypeOfMove::cross ? WIN : LOOSE;
                            return eval;
                        }
                        else
                        {
                            int eval = fieldC[j + i][j] == TypeOfMove::cross ? LOOSE : WIN;
                            return eval;
                        }
                    }
                }else
                {
                    leftDiagonalDownCount=0;
                }
            }


            //RIGHT DIADONAL
            if(fieldC[j][size - 1 - j-i] == fieldC[j + 1][size - 2 - j-i] && fieldC[j][size - 1 - j-i] != TypeOfMove::empty)
            {
                rightDiagonalUpCount++;

                 if (rightDiagonalUpCount == winMovesNumber - 1)
                 {
                    if (isCompCross)
                    {
                        int eval = fieldC[j][size - 1 - j-i] == TypeOfMove::cross ? WIN : LOOSE;
                        return eval;
                    }
                    else
                    {
                        int eval = fieldC[j][size - 1 - j-i] == TypeOfMove::cross ? LOOSE : WIN;
                        return eval;
                    }
                 }

            }else
            {
                rightDiagonalUpCount=0;
            }
            
            //for down part no need to recount twice for main deiagonal
            if (i != 0)
            {
                if (fieldC[j+i][size-1-j] == fieldC[j+i+1][size-2-j] && fieldC[j+i][size-1-j] != TypeOfMove::empty)
                {

                    rightDiagonalDownCount++;

                    if (rightDiagonalDownCount == winMovesNumber - 1)
                    {
                        if (isCompCross)
                        {
                            int eval = fieldC[j+i][size-1-j] == TypeOfMove::cross ? WIN : LOOSE;
                            return eval;
                        }
                        else
                        {
                            int eval = fieldC[j+i][size-1-j] == TypeOfMove::cross ? LOOSE : WIN;
                            return eval;
                        }
                    }
                }
                else
                {
                    rightDiagonalDownCount=0;
                }
            }



        }
        
        //with new i ->another comb
        leftDiagonalUpCount=0;
        leftDiagonalDownCount=0;

        rightDiagonalUpCount=0;
        rightDiagonalDownCount=0;

    }

    
    return DRAW;
}
//todo-3 test more
int TicTacGame::generalWinEval(int **fieldC, int movesLeftC)
{
    // int possibleWinnerAfterMoves = size*size - 2*winMovesNumber+1;
    // // // std::cout<<"possibleWinnerAfterMoves "<<possibleWinnerAfterMoves<<"\n";
    // // // std::cout<<"movesLeft "<<movesLeftC<<"\n";
    // if(movesLeftC>possibleWinnerAfterMoves)
    // {
    //       return 0;
    // }

    int diagonalWin=diagonalWinEval(fieldC);
    if(diagonalWin==0)
    {
       return rowWinEval(fieldC);
    }else
        return diagonalWin;
}

void TicTacGame::play()
{
    bool isCompMove=false;

    //firtsMove

    int i, j;

    if(isCompCross)
    {  
        setRandomMove(i,j);
        field[i][j] = TypeOfMove::cross;
        movesLeft--;
        std::cout<<toStringField(field)<<"\n";

    }

    std::cout<<toStringField(field)<<"\n";


    while(movesLeft>0&&generalWinEval(field, movesLeft)==0)
    {
        if(isCompMove)
        {
            computerMove();
            isCompMove=false;

        }else
        {
            userMove();
            isCompMove=true;
        }

        std::cout<<toStringField(field)<<"\n";
        movesLeft--;
    }

    std::cout<<"res: "<<generalWinEval(field, movesLeft)<<"\n";

}

void TicTacGame::computerMove()
{
    //todo-2

    std::pair<int, int>bestMove;
    int ** copyField = new int*[size];

    setCoppyOfField(field,copyField);

    int maxEval=INT16_MIN;
    int copyOfMovesLeft =movesLeft;

    for(int i=0;i<size; i++)
    {
        for(int j=0;j<size; j++)
        {
            if(field[i][j]==TypeOfMove::empty)
            {
                if(isCompCross)
                    copyField[i][j]=TypeOfMove::cross;
                else
                    copyField[i][j]=TypeOfMove::nought;
                
                int eval = miniMax(copyOfMovesLeft, copyField,false,INT16_MIN,INT16_MAX);

                if(eval>maxEval)
                {
                    bestMove.first=i;
                    bestMove.second=j;
                    maxEval=std::max(maxEval,eval);
                }

                if(isCompCross)
                    copyField[i][j]=TypeOfMove::empty;


            }
        }
    }

    deleteField(copyField);

    if(isCompCross)
    {
        field[bestMove.first][bestMove.second]=TypeOfMove::cross;
    }else
    {
        field[bestMove.first][bestMove.second]=TypeOfMove::nought;
    }

}

void TicTacGame::setRandomMove(int& i, int& j)
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(0, size-1);

    i=dist6(rng);
    j=dist6(rng);

}

void TicTacGame::setCoppyOfField(int ** oldField,int ** newField)
{
    for(int i=0; i<size; i++)
    {
        newField[i] = new int[size];
        for(int j=0; j<size; j++)
        {
            newField[i][j]=oldField[i][j];
        }

    }

}

void TicTacGame::deleteField(int ** newField)
{
    for(int i=0; i<size; i++)
    {
        delete newField[i];
    }

    delete newField;
    newField= NULL;
}

int TicTacGame::miniMax(int copyMovesLeft, int** copyField,bool maxMin, int alpha, int beta)
{
    copyMovesLeft--;
    int generalEval = generalWinEval(copyField,copyMovesLeft);

    if(copyMovesLeft==0&&generalEval==0)
        return DRAW;
    else if(copyMovesLeft!=0&&generalEval!=0)
        return generalEval;
    else if(copyMovesLeft==0&&generalEval!=0)
        return generalEval;


    if (maxMin)
    {
        int maxEval = INT16_MIN;

        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                if (copyField[i][j] == TypeOfMove::empty)
                {
                    if (isCompCross)
                        copyField[i][j] = TypeOfMove::cross;
                    else
                        copyField[i][j] = TypeOfMove::nought;

                    int eval = miniMax(copyMovesLeft, copyField, !maxMin, alpha,beta);
                    maxEval = std::max(maxEval, eval);
                    alpha = std::max(alpha,maxEval);
                    
                    copyField[i][j] = TypeOfMove::empty;

                    if(beta<=alpha)
                        break;
                }
            }
        }
        // std::cout<<"WAS HERE****************\n";
        // std::cout<<"WAS HERE**************** "<<maxEval<<"\n";

        return maxEval;
    }else
    {
        int minEval = INT16_MAX;
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                if (copyField[i][j] == TypeOfMove::empty)
                {
                    if (isCompCross)
                        copyField[i][j] = TypeOfMove::nought;
                    else
                        copyField[i][j] = TypeOfMove::cross;

                    int eval = miniMax(copyMovesLeft, copyField,!maxMin, alpha, beta);
                    minEval = std::min(minEval, eval);
                    beta=std::min(beta,minEval);

                    copyField[i][j] = TypeOfMove::empty;

                    if(beta<=alpha)
                    {
                        break;
                    }
                }
            }
        }
        // std::cout<<"------------------- "<<minEval<<"\n";
        return minEval;
    }
}

void TicTacGame::fieldGenerateDiagonalWins()
{
    //types of diagonals : left normal, right normal, leftup, left down, righ up right down

    //left normal [j][j]  ; left up [j][j+i]; left down [j+i][j];
    //right normal[j][size-1-j] right up[j][size - 1 - j-i], right down[j+i][size-1-j]

    //generate rand iright diagonal 
    //generate rand left diagonal




    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(0, 1);

    bool leftDiagonalWin=dist6(rng);
    bool isWin=dist6(rng);
    
    if (leftDiagonalWin)
    {
        if (isWin)
        {
            field[1][3] = TypeOfMove::cross;
            field[2][2] = TypeOfMove::cross;
            field[3][1] = TypeOfMove::cross;
        }
        else
        {
            field[1][3] = TypeOfMove::nought;
            field[2][2] = TypeOfMove::nought;
            field[3][1] = TypeOfMove::nought;
        }
    }else
    {
        if (isWin)
        {
            field[1][3] = TypeOfMove::cross;
            field[2][2] = TypeOfMove::cross;
            field[3][1] = TypeOfMove::cross;
        }
        else
        {
            field[1][3] = TypeOfMove::nought;
            field[2][2] = TypeOfMove::nought;
            field[3][1] = TypeOfMove::nought;
        }

    }

    movesLeft=movesLeft-3;
    int count =0; 
    while(count<3)
    {
        int i,j;

        setRandomMove(i,j);

        while(!isMoveFree(i,j,field))
        {
            setRandomMove(i,j);
        }

        if(isWin)
        {
            field[i][j]=TypeOfMove::nought;
        }
        else
        {
            field[i][j]=TypeOfMove::cross;
        }
        
        movesLeft--;
        count++;

    }

    std::cout<<toStringField(field)<<"\n";
    std::cout<<"win: "<<generalWinEval(field, movesLeft)<<"\n";


}

void fieldGEnerateRowWins(int **fieldC, int movesLeftC)
{

}
