//
// Created by wiku2 on 20.04.2024.
//

#ifndef LAB_2_MSBSFMLCONTROLLER_H
#define LAB_2_MSBSFMLCONTROLLER_H


#include <iostream>
#include <SFML/Graphics.hpp>
#include "MSBSFMLView.h"
#include "MinesweeperBoard.h"
#include <vector>


class MSBSFMLController {

    MinesweeperBoard & board;
    const MSBSFMLView & view;


public:
    MSBSFMLController(MinesweeperBoard & b, MSBSFMLView & v);
    void play(sf::RenderWindow & window, MSBSFMLView & view) const;
};


#endif //LAB_2_MSBSFMLCONTROLLER_H
