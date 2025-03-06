//
// Created by wiku2 on 26.03.2024.
//

#ifndef LAB_2_MSTEXTCONTROLLER_H
#define LAB_2_MSTEXTCONTROLLER_H

#include <iostream>
#include "MinesweeperBoard.h"
#include "MSBoardTextView.h"

class MSTextController {
    MinesweeperBoard &board;
    const MSBoardTextView &view;

public:
    MSTextController(MinesweeperBoard &b, const MSBoardTextView &v);
    void play() const;
};


#endif //LAB_2_MSTEXTCONTROLLER_H
