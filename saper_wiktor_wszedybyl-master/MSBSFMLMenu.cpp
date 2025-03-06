#include "MSBSFMLMenu.h"

MSBSFMLMenu::MSBSFMLMenu(sf::RenderWindow & win) : window(win), selectedModeIndex(0), selectedMode(EASY)
{


    font.loadFromFile("resources/fonts/arial.ttf");

    easyText.setFont(font);
    easyText.setString("Easy");
    easyText.setCharacterSize(27);
    easyText.setPosition(200,100);

    normalText.setFont(font);
    normalText.setString("Normal");
    normalText.setCharacterSize(27);
    normalText.setPosition(200, 200);

    hardText.setFont(font);
    hardText.setString("Hard");
    hardText.setCharacterSize(27);
    hardText.setPosition(200, 300);

    debugText.setFont(font);
    debugText.setString("Debug");
    debugText.setCharacterSize(27);
    debugText.setPosition(200, 400);
}

void MSBSFMLMenu::handleInput(sf::Event &event)
{
    if(event.type == sf::Event::KeyPressed)
    {
        if(event.key.code == sf::Keyboard::Up)
        {
            selectedModeIndex = (selectedModeIndex - 1 + 4) % 4;
        }
        else if (event.key.code == sf::Keyboard::Down)
        {
            selectedModeIndex = (selectedModeIndex + 1) % 4;
        }

        switch (selectedModeIndex)
        {
            case 0:
                selectedMode = EASY;
                break;
            case 1:
                selectedMode = NORMAL;
                break;
            case 2:
                selectedMode = HARD;
                break;
            case 3:
                selectedMode = DEBUG;
                break;
        }
    }
}

void MSBSFMLMenu::drawMenu()
{
    switch(selectedMode)
    {
        case EASY:
            easyText.setFillColor(sf::Color::Cyan);
            normalText.setFillColor(sf::Color::White);
            hardText.setFillColor(sf::Color::White);
            debugText.setFillColor(sf::Color::White);
            break;
        case NORMAL:
            easyText.setFillColor(sf::Color::White);
            normalText.setFillColor(sf::Color::Cyan);
            hardText.setFillColor(sf::Color::White);
            debugText.setFillColor(sf::Color::White);
            break;
        case HARD:
            easyText.setFillColor(sf::Color::White);
            normalText.setFillColor(sf::Color::White);
            hardText.setFillColor(sf::Color::Cyan);
            debugText.setFillColor(sf::Color::White);
            break;
        case DEBUG:
            easyText.setFillColor(sf::Color::White);
            normalText.setFillColor(sf::Color::White);
            hardText.setFillColor(sf::Color::White);
            debugText.setFillColor(sf::Color::Cyan);
            break;
    }

    window.draw(easyText);
    window.draw(normalText);
    window.draw(hardText);
    window.draw(debugText);
}

GameMode MSBSFMLMenu::getSelectedMode() const
{
    return selectedMode;
}