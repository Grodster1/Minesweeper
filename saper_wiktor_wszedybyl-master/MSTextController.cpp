//
// Created by wiku2 on 26.03.2024.
//

#include "MSTextController.h"

/*void MSTextController::showAllBombs()
{
    int width = board.getBoardWidth();
    int height = board.getBoardHeight();

    for (int row = 0; row < height; ++row)
    {
        for (int col = 0; col < width; ++col)
        {
            if(board.getFieldInfo(row, col) == 'X')
                board.revealField(row, col);
        }
    }
}*/

MSTextController::MSTextController(MinesweeperBoard &b, const MSBoardTextView &v) : board(b), view(v) {}

void MSTextController::play() const
{
    while(board.getGameState() == RUNNING)
    {
        int choice;
        int row;
        int col;

        std::cout << "What do you want to do?" << std::endl;
        std::cout << "1. Reveal field" << std::endl;
        std::cout << "2. Toggle a flag" << std::endl;
        std::cin >> choice;

        switch (choice)
        {
            case 1:
                std::cout << "Choose a field to reveal (row col): ";
                std::cin >> row >> col;
                board.revealField(row,col);
                break;

            case 2:
                std::cout << "Choose a field where to toggle a flag (row col): ";
                std::cin >> row >> col;
                board.toggleFlag(row,col);
                break;

            default:
                std::cout << "Invalid choice!" <<std::endl;
                break;
        }

        view.display();
    }
    if (board.getGameState() == FINISHED_LOSS)
    {
        std::cout << "YOU LOSE!!!" << std::endl;
    }
    else
        std::cout << "YOU WIN!!!" << std::endl;
}
