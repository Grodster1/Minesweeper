//
// Created by wiku2 on 24.03.2024.
//

#ifndef LAB_2_MSBOARDTEXTVIEW_H
#define LAB_2_MSBOARDTEXTVIEW_H

#include <iostream>
#include "MinesweeperBoard.h"

class MSBoardTextView{
    const MinesweeperBoard &board;

public:
    MSBoardTextView(const MinesweeperBoard &b);
    void display() const;
};


#endif //LAB_2_MSBOARDTEXTVIEW_H
