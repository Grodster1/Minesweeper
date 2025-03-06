//
// Created by wiku2 on 24.03.2024.
//

#include "MSBoardTextView.h"

MSBoardTextView::MSBoardTextView(const MinesweeperBoard &b) : board(b) {}

void MSBoardTextView::display() const
{
    int width = board.getBoardWidth();
    int height = board.getBoardHeight();

    std::cout << "   ";
    for(int col=0; col < width; col ++)
    {
        std::cout << " " << col << " ";
    }
    std::cout << std::endl;
    for(int row=0; row < height; row++)
    {
        std::cout << " " << row << " ";
        for(int col=0; col < width; col++)
        {
            char info = board.getFieldInfo(row, col);
            std::cout << '[' << info << ']';
        }
        std::cout << std::endl;

    }

}