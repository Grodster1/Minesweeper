#include <iostream>
#include <cassert>
#include "MinesweeperBoard.h"
#include "MSBSFMLView.h"
#include "MSBSFMLController.h"
#include "MSBSFMLMenu.h"
#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Minesweeper");
    window.setVerticalSyncEnabled(false);
    window.setFramerateLimit(60);

    MSBSFMLMenu menu(window);
    bool menuMode = true;
    GameMode selectedMode = EASY;

    while (menuMode && window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            menu.handleInput(event);
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return) {
                selectedMode = menu.getSelectedMode();
                menuMode = false;
            }
        }

        window.clear();
        menu.drawMenu();
        window.display();
    }

    if (!window.isOpen()) {
        return 0;
    }


    MinesweeperBoard board(20, 20, selectedMode);
    int width = board.getBoardWidth();
    int height = board.getBoardHeight();
    assert((width <= 20 && width >= 5) && "Width isn't proper");
    assert(height <= 20 && "Height is too large");

    int window_width = 3 * (width + 1) + 40 * width;
    int window_height = 3 * (height + 1) + height * 40 + 100;
    window.setSize(sf::Vector2u(window_width, window_height));

    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    window.setPosition(sf::Vector2i((desktop.width - window_width) / 2, 0));
    MSBSFMLView view(board, window);
    MSBSFMLController ctrl(board, view);

    while (window.isOpen()) {
        ctrl.play(window, view);
    }

    return 0;
}
