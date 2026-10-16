#include <iostream>
#include <vector>


enum  tileState
{
    empty,
    player1,
    player2
};
enum  winState
{
    None,
    Draw,
    Player1win,
    Player2win
};

int selectCol(tileState grid[6][7]);
void ShowGrid(tileState grid[6][7]);
void placeJeton(tileState (&grid)[6][7], int col, tileState currentPlayer,int &lastX, int &lastY);
bool checkGridFreeSpace(tileState grid[6][7], winState &who);
tileState switchplayer(tileState currentPlayer);
winState checkWinLooseConditions(tileState grid[6][7], tileState currentPlayer, int line, int col);
int horizontal(tileState grid[6][7], int line, int col, tileState currentPlayer);
int vertical(tileState grid[6][7], int line, int col, tileState currentPlayer);
int diagonal1(tileState grid[6][7], int line, int col, tileState currentPlayer);
int diagonal2(tileState grid[6][7], int line, int col, tileState currentPlayer);
winState checkNbChainedCoins(int nbChainedCoins, tileState currentPlayer);


int main()
{
    winState whoWinner = None;
    tileState player = player1;
    tileState grid[6][7];
    int lastX = 0;
    int lastY = 0;
    for (int i=0; i<6; i++)
    {
        for (int j=0; j<7; j++)
        {
            grid[i][j] = empty;
        }
    }
    while (whoWinner == None)
    {
        player = switchplayer(player);
        ShowGrid(grid);
        placeJeton(grid, selectCol(grid), player,lastX,lastY);
        whoWinner = checkWinLooseConditions(grid,player,lastX,lastY);
        system("cls");
        if (!checkGridFreeSpace(grid,whoWinner))
        {
            std::cout<<"fin";
            whoWinner = Draw;
        }
        
    }
    system("cls");
    ShowGrid(grid);
    switch (whoWinner)
    {
    case Draw:
        std::cout<<"draw";
        break;
    case Player1win:
        std::cout<<"player1win";
        break;
    case Player2win:  
        std::cout<<"player2win";
        break;
    }
    return 1;
}


void ShowGrid(tileState grid[6][7])
{
    for (int i=1; i<=7; i++)
    {
        std::cout<<" "<<i;
    }
    std::cout<<std::endl;
    for (int i=0; i<6; i++)
    {
        std::cout<<"|";
        for (int j=0; j<7; j++)
        {
            switch (grid[i][j])
            {
            case empty:
                std::cout << " ";
                break;
            case player1:
                std::cout << "X";
                break;
            case player2:
                std::cout << "O";
                break;
            }
            std::cout<<"|";
        }
        std::cout<<std::endl;
    }
}
void placeJeton(tileState (&grid)[6][7], int col, tileState currentPlayer,int &lastX, int &lastY)
{
    for (int i=5; i>=0; i--)
    {
        if (grid[i][col] == empty)
        {
            lastX = i;
            lastY = col;
            grid[i][col] = currentPlayer;
            break;
        }
    }
}
bool checkGridFreeSpace(tileState grid[6][7], winState &who)
{
    for (int i=0; i<6; i++)
    {
        for (int j=0; j<7; j++)
        {
            if (grid[i][j] == empty)
            {
                return true;
            }
        }
    }
    who = Draw;
    return false;
}
int selectCol(tileState grid[6][7])
{
    int col = 0;
    bool colDisposed = false;
    while ((col < 1 || col >  7) || colDisposed == false)
    {
        std::cout<<"le chiffre rentrer n'est pas compris entre 1 et 7"<<std::endl;
        std::cout<<"entrer un nombre entre 1 et 7 pour choisir la colonne : ";
        std::cin>>col;
        if (grid[0][col-1] == empty)
        {
            colDisposed = true;
        }
        std::cout<<std::endl;
    }
    return col-1;
}
tileState switchplayer(tileState currentPlayer)
{
    switch (currentPlayer)
    {
        case player1:
        return player2;
        case player2:
        return player1;
    }
}
winState checkWinLooseConditions(tileState grid[6][7], tileState currentPlayer, int line, int col)
{
    int nbChainedCoins = 0;
    winState whoWinner = None;
    nbChainedCoins = horizontal(grid, line, col, currentPlayer);
    whoWinner = checkNbChainedCoins(nbChainedCoins, currentPlayer);
    if (whoWinner != None)
    {
        return whoWinner;
    }
    nbChainedCoins = vertical(grid, line, col, currentPlayer);
    whoWinner = checkNbChainedCoins(nbChainedCoins, currentPlayer);
    if (whoWinner != None)
    {
        return whoWinner;
    }
    nbChainedCoins = diagonal1(grid, line, col, currentPlayer);
    whoWinner = checkNbChainedCoins(nbChainedCoins, currentPlayer);
    if (whoWinner != None)
    {
        return whoWinner;
    }
    nbChainedCoins = diagonal2(grid, line, col, currentPlayer);
    whoWinner = checkNbChainedCoins(nbChainedCoins, currentPlayer);
    if (whoWinner != None)
    {
        return whoWinner;
    }
    return None;
}
int horizontal(tileState grid[6][7], int line, int col, tileState currentPlayer)
{
    int nbChainedCoins = 1;
    for (int i = 1; i < 4; i++)
    {
        if (grid[line][col-i] == currentPlayer)
        {
            nbChainedCoins++;
        }
        else
        {
            break;
        }
    }
    for (int i = 1; i < 4; i++)
    {
        if (grid[line][col+i] == currentPlayer)
        {
            nbChainedCoins++;
        }
        else
        {
            break;
        }
    }
    return nbChainedCoins;
}
int vertical(tileState grid[6][7], int line, int col, tileState currentPlayer)
{
    int nbChainedCoins = 1;
    for (int i = 1; i < 4; i++)
    {
        if (grid[line+i][col] == currentPlayer)
        {
            nbChainedCoins++;
        }
        else
        {
            break;
        }
    }
    for (int i = 1; i < 4; i++)
    {
        if (grid[line-i][col] == currentPlayer)
        {
            nbChainedCoins++;
        }
        else
        {
            break;
        }
    }
    return nbChainedCoins;
}
int diagonal1(tileState grid[6][7], int line, int col, tileState currentPlayer)
{
    int nbChainedCoins = 1;
    for (int i = 1; i < 4; i++)
    {
        if (grid[line+i][col+i] == currentPlayer)
        {
            nbChainedCoins++;
        }
        else
        {
            break;
        }
    }
    for (int i = 1; i < 4; i++)
    {
        if (grid[line-i][col-i] == currentPlayer)
        {
            nbChainedCoins++;
        }
        else
        {
            break;
        }
    }
    return nbChainedCoins;
}
int diagonal2(tileState grid[6][7], int line, int col, tileState currentPlayer)
{
    int nbChainedCoins = 1;
    for (int i = 1; i < 4; i++)
    {
        if (grid[line-i][col+i] == currentPlayer)
        {
            nbChainedCoins++;
        }
        else
        {
            break;
        }
    }
    for (int i = 1; i < 4; i++)
    {
        if (grid[line+i][col-i] == currentPlayer)
        {
            nbChainedCoins++;
        }
        else
        {
            break;
        }
    }
    return nbChainedCoins;
}
winState checkNbChainedCoins(int nbChainedCoins, tileState currentPlayer)
{
    if (nbChainedCoins >=4)
    {
        switch (currentPlayer)
        {
        case player1: 
            return Player1win;
        case player2:
            return Player2win;
        }
    }
    return None;
}