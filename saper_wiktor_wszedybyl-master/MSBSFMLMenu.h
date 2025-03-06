#ifndef MSBSFMLMENU_H
#define MSBSFMLMENU_H

#include <SFML/Graphics.hpp>
#include "MinesweeperBoard.h"

class MSBSFMLMenu {

    int width;
    int height;
    sf::RenderWindow & window;
    sf::Font font;
    sf::Text easyText;
    sf::Text normalText;
    sf::Text hardText;
    sf::Text debugText;
    int selectedModeIndex;
    GameMode selectedMode;

public:
    MSBSFMLMenu(sf::RenderWindow & win);
    void handleInput(sf::Event & event);
    void drawMenu();
    GameMode getSelectedMode() const;
};

#endif // MSBSFMLMENU_H
