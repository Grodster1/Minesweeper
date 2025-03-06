//
// Created by c on 3/13/24.
//

#include <iostream>
#include <cmath>
#include <cstdlib>
#include "MinesweeperBoard.h"

void MinesweeperBoard::moveBomb(int row, int col) {
    int new_row;
    int new_col;
    bool bombMoved = false;

    while (!bombMoved) {
        new_row = rand() % height;
        new_col = rand() % width;

        // Sprawdzamy czy nowe pole i jego otoczenie nie zawierają min
        bool checkingFields = true;
        for (int r = -1; r <= 1; ++r) {
            for (int c = -1; c <= 1; ++c) {
                int currentRow = new_row + r;
                int currentCol = new_col + c;
                if (isInBounds(currentRow, currentCol) && board[currentRow][currentCol].hasMine) {
                    checkingFields = false;
                    break;
                }
            }
            if (!checkingFields) {
                break;
            }
        }
        if (checkingFields) {
            board[new_row][new_col].hasMine = true;
            board[row][col].hasMine = false;
            bombMoved = true;
        }
    }
}


bool MinesweeperBoard::checkIfWon() const
{
    int notRevealed = 0;
    for(int row=0; row < height; ++row)
    {
        for(int col=0; col < width; ++col)
        {
            if (!board[row][col].isRevealed)
            {
                notRevealed ++;
            }
        }
    }
    if(notRevealed == getMineCount())
        return true;
    else
        return false;
}

int MinesweeperBoard::placeBombs(enum GameMode mode)
{
    int fieldsNumber = height * width;
    int bomb_count = 0;
    int i = 0;


    if (mode == EASY)
    {
        bomb_count = std::ceil(0.1 * fieldsNumber);
    }
    else if (mode == NORMAL)
    {
        bomb_count = std::ceil(0.2 * fieldsNumber);
    }
    else if (mode == HARD)
    {
        bomb_count = std::ceil(0.3 * fieldsNumber);
    }

    while (i < bomb_count)
    {
        int row = rand() % height;
        int col = rand() % width;

        if (board[row][col].hasMine == false)
        {
            board[row][col].hasMine = true;
            i++;
        }
    }

    if (mode == DEBUG)
    {
        for(int c = 0; c < width; ++c)
        {
            board[0][c].hasMine = true;
        }
        for(int r = 2; r < height; r=r+2)
        {
            board[r][0].hasMine = true;
        }
        for(int field = 1; field < height; field ++)
        {
            if(field < width)
            {
                board[field][field].hasMine = true;
            }
        }
    }
    return bomb_count;
}

bool MinesweeperBoard::isInBounds(int row, int col) const
{
    if ((row < 0 || row >= height) || (col < 0 || col >= width))
        return false;

    else
        return true;

}

MinesweeperBoard::MinesweeperBoard(int width, int height, enum GameMode mode)
{
    this->width = width;
    this->height = height;
    this->mode = mode;


    for(int row = 0; row < height; row ++)
    {
        for(int col = 0; col < width; col++)
        {
            board[row][col] = {false, false, false};
        }
    }
    bombs = placeBombs(mode);
}

MinesweeperBoard::MinesweeperBoard()
{
    height = 4;
    width = 4;
    bombs = 4;
    mode = DEBUG;

    for(int row=0; row < height; row++)
    {
        for(int col=0; col < width; col++)
        {
            board[row][col] = {false, false, false};
        }
    }

    board[0][0] = {true, false, false};
    board[0][1] = {true, false, false};
    board[1][2] = {true, false, false};
    board[0][2] = {true, false, false};


}


void MinesweeperBoard::debug_display() const
{
    std::cout << "     ";
    for(int col=0; col < width; col ++)
    {
        std::cout << "  " << col << "  ";
    }
    std::cout << std::endl;
    for(int row=0; row < height; row++)
    {
        std::cout << "  " << row << "  ";
        for(int col=0; col < width; col++)
        {
            if(board[row][col].hasMine == true)
            {
                std::cout << "[M";
            }
            else
            {
                std::cout << "[.";
            }
            if(board[row][col].isRevealed == true)
            {
                std::cout << 'o';
            }
            else
            {
                std::cout << '.';
            }
            if(board[row][col].hasFlag == true)
            {
                std::cout << "f]";
            }
            else
            {
                std::cout << ".]";
            }
        }
        std::cout << std::endl;

    }
}

int MinesweeperBoard::getMineCount() const
{
    int bomb_count = 0;
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            if (board[row][col].hasMine)
            {
                bomb_count ++;
            }
        }
    }
    return bomb_count;
}

int MinesweeperBoard::countMines(int row, int col) const
{
    int bomb_count = 0;

    if (isInBounds(row,col) && board[row][col].isRevealed)
    {
        for (int c = -1; c <= 1; ++c )
        {
            if(isInBounds(row-1, col+c) && board[row-1][col+c].hasMine)
                bomb_count++;
            if(isInBounds(row+1, col+c) && board[row+1][col+c].hasMine)
                bomb_count++;
        }
        if (isInBounds(row,col-1) && board[row][col-1].hasMine)
            bomb_count++;
        if (isInBounds(row, col+1) && board[row][col+1].hasMine)
            bomb_count++;
    }
    else
    {
        return -1;
    }

    return bomb_count;
}



bool MinesweeperBoard::hasMine(int row, int col) const
{
    if (isInBounds(row, col) && board[row][col].hasMine && !board[row][col].isRevealed)
        return true;
    else
        return false;
}

void MinesweeperBoard::toggleFlag(int row, int col)
{

    if (isInBounds(row,col) && !board[row][col].isRevealed && getGameState() == RUNNING){
        if (!board[row][col].hasFlag) {
            if (getFlagCount() < getMineCount()) {
                board[row][col].hasFlag = true;
                flags++;
            }
        }
        else{
            board[row][col].hasFlag = false;
            flags --;
        }
    }
}

void MinesweeperBoard::revealField(int row, int col)
{
    if (getGameState() != RUNNING)
        return;
    if (!isInBounds(row, col))
        return;
    if (board[row][col].hasFlag || board[row][col].isRevealed)
        return;

    board[row][col].isRevealed = true;

    if (firstMove) {
        for (int r = -1; r <= 1; ++r) {
            for (int c = -1; c <= 1; ++c) {
                int currentRow = row + r;
                int currentCol = col + c;
                if (isInBounds(currentRow, currentCol) && board[currentRow][currentCol].hasMine) {
                    moveBomb(currentRow, currentCol);
                }
            }
        }
        firstMove = false;
    }
    if (!board[row][col].hasMine) {
        if (countMines(row, col) == 0) {
            recurence(row, col);
        }
        return;
    }
    if (!firstMove || mode == DEBUG) {
        gameLost = true;
        return;
    }
}

bool MinesweeperBoard::isRevealed(int row, int col)
{
    if (isInBounds(row,col) && board[row][col].isRevealed)
        return true;
    else
        return false;
}

GameState MinesweeperBoard::getGameState() const
{
    if(gameLost)
        return FINISHED_LOSS;

    else if(checkIfWon())
        return FINISHED_WIN;
    else
        return RUNNING;
}

char MinesweeperBoard::getFieldInfo(int row, int col) const
{
    if(!isInBounds(row,col))
        return '#';
    else if(!board[row][col].isRevealed && board[row][col].hasFlag)
        return 'F';
    else if(!board[row][col].isRevealed && !board[row][col].hasFlag)
        return '_';
    else if(board[row][col].isRevealed && board[row][col].hasMine)
        return 'X';
    else if(board[row][col].isRevealed && countMines(row,col) > 0)
    {
        int m = countMines(row,col);
        char mines = static_cast<char>(m + '0');
        return mines;
    }
    else
        return ' ';
}

void MinesweeperBoard::recurence(int row, int col)
{
    if(!isInBounds(row, col))
        return;

    if(board[row][col].hasFlag)
        return;

    if(countMines(row,col) == 0)
    {
        for(int r = -1; r <=1; ++r)
        {
            for(int c = -1; c <= 1; ++c)
            {
                if(isInBounds(row+r, col + c) and !board[row + r][col + c].isRevealed and !board[row + r][col + c].hasFlag)
                {
                    board[row+r][col + c].isRevealed = true;
                    recurence(row+r, col + c);
                }
            }
        }
    }
}

int MinesweeperBoard::getFlagCount() const
{
    return flags;
}


