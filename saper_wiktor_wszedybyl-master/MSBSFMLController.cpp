//
// Created by wiku2 on 20.04.2024.
//
#include <iostream>
#include "MSBSFMLController.h"
#include <vector>

MSBSFMLController::MSBSFMLController(MinesweeperBoard &b, MSBSFMLView &v) : board(b), view(v) {}


void MSBSFMLController::play(sf::RenderWindow & window, MSBSFMLView & view) const
{
    int mouse_x;
    int mouse_y;
    int gap;
    int size;
    double offset_x;

    sf::Event event;
    while (window.pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
        {
            window.close();
            return;
        }
        if(event.type == sf::Event::Resized)
            window.setView(sf::View(sf::FloatRect(0,0, event.size.width, event.size.height)));

        if(event.type == sf::Event::MouseButtonPressed)
        {
            if(board.getGameState() == RUNNING)
            {
                mouse_x = event.mouseButton.x;
                mouse_y = event.mouseButton.y;
                gap = view.getGap();
                size = view.getSize();
                offset_x = view.getOffsetX();

                int col = (mouse_x - offset_x ) / (size+gap);
                int row = (mouse_y - 100 - gap) / (size+gap);

                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    std::cout << row << ' ' << col << std::endl;
                    board.revealField(row, col);
                }
                else if (event.mouseButton.button == sf::Mouse::Right)
                {
                    std::cout << row << ' ' << col << std::endl;
                    board.toggleFlag(row, col);
                }
            }
        }
    }
    window.clear();
    if(board.getGameState()==RUNNING)
        view.draw(window);
    if(board.getGameState()==FINISHED_LOSS)
    {
        view.displayMines(window);
        view.lostText(window);
    }
    if(board.getGameState()==FINISHED_WIN)
    {
        view.draw(window);
        view.wonText(window);
    }
    window.display();
}
