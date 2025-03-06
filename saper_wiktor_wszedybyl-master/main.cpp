#include <iostream>
#include <string>
#include <cmath>
#include<cstdlib>
#include "MinesweeperBoard.h"
#include "MSBoardTextView.h"
#include "MSTextController.h"



int main()
{
    srand(time(0));
    MinesweeperBoard board(10 ,10,DEBUG);
    //MinesweeperBoard board;
    MSBoardTextView view(board);
    MSTextController ctrl(board, view);
    board.debug_display();
    view.display();
    ctrl.play();

    return 0;
}
