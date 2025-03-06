//
// Created by c on 4/10/24.
//

#ifndef LAB_2_MSBSFMLVIEW_H
#define LAB_2_MSBSFMLVIEW_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "MinesweeperBoard.h"

class MSBSFMLView {

    const MinesweeperBoard &board;
    int size = 40;
    int gap = 3;
    int width;
    int height;
    int board_width; //uwzględnienie przerwy pomiędzy polami
    int board_height;
    int windowWidth;
    int windowHeight;
    double offsetX;
    float centerX;
    sf::Vector2u windowSize;
    std::map<std::string, sf::Texture> textures;


public:
    explicit MSBSFMLView(const MinesweeperBoard &b, sf::RenderWindow & window);
    void draw(sf::RenderWindow & window);
    void displayMines(sf::RenderWindow & window);
    void flagCount(sf::RenderWindow & window);
    void updateFlagCount(sf::RenderWindow & window);
    void lostText(sf::RenderWindow & window);
    void wonText(sf::RenderWindow & window);
    void loadTextures();
    double getOffsetX();
    int getGap();
    int getSize();

};


#endif //LAB_2_MSBSFMLVIEW_H
