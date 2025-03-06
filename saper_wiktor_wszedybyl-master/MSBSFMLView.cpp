//
// Created by c on 4/10/24.
//
#include <iostream>
#include <SFML/Graphics.hpp>
#include "MSBSFMLView.h"
#include "MinesweeperBoard.h"
#include <sstream>


MSBSFMLView::MSBSFMLView(const MinesweeperBoard &b, sf::RenderWindow & window) : board(b)
{
    width = board.getBoardWidth();
    height = board.getBoardHeight();
    board_width = (width * size) + (width+1) * gap;
    board_height = (height * size) + (height+1) * gap;
    windowSize = window.getSize();
    windowWidth = int(windowSize.x);
    windowHeight = int(windowSize.y);
    offsetX = (windowWidth - board_width - 0.5*gap) / 2;
    centerX = window.getSize().x / 2.0f;

    loadTextures();
}

double MSBSFMLView::getOffsetX()
{
    return offsetX;
}


int MSBSFMLView::getGap()
{
    return gap;
}

int MSBSFMLView::getSize()
{
    return size;
}

void MSBSFMLView::loadTextures()
{

    sf::Texture texture_lost;
    texture_lost.loadFromFile("resources/lose.png");
    textures["lose"] = texture_lost;

    sf::Texture texture_won;
    texture_won.loadFromFile("resources/win.png");
    textures["win"] = texture_won;

    sf::Texture texture_flag;
    texture_flag.loadFromFile("resources/flag.png");
    textures["flag"] = texture_flag;

    sf::Texture texture_mine;
    texture_mine.loadFromFile("resources/mine.png");
    textures["mine"] = texture_mine;

    sf::Texture texture_one;
    texture_one.loadFromFile("resources/one.png");
    textures["1"] = texture_one;

    sf::Texture texture_two;
    texture_two.loadFromFile("resources/two.png");
    textures["2"] = texture_two;

    sf::Texture texture_three;
    texture_three.loadFromFile("resources/three.png");
    textures["3"] = texture_three;

    sf::Texture texture_four;
    texture_four.loadFromFile("resources/four.png");
    textures["4"] = texture_four;

    sf::Texture texture_five;
    texture_five.loadFromFile("resources/five.png");
    textures["5"] = texture_five;

    sf::Texture texture_six;
    texture_six.loadFromFile("resources/six.png");
    textures["6"] = texture_six;

    sf::Texture texture_seven;
    texture_seven.loadFromFile("resources/seven.png");
    textures["7"] = texture_seven;

    sf::Texture texture_eight;
    texture_eight.loadFromFile("resources/eight.png");
    textures["8"] = texture_eight;
}


void MSBSFMLView::draw(sf::RenderWindow & window)
{

    sf::RectangleShape bground((sf::Vector2f(board_width, board_height + 100)));
    bground.setFillColor(sf::Color::White);
    bground.setPosition(centerX - board_width / 2.0f, 0);

    window.draw(bground);
    flagCount(window);
    updateFlagCount(window);

    for (int col = 0; col < width; ++col)
    {
        for (int row = 0; row < height; ++row)
        {
            float posX = centerX - board_width / 2.0f + (col + 1) * gap + col * size;
            float posY = 100+(row + 1) * gap + row * size;

            sf::RectangleShape tlo(sf::Vector2f(size, size));
            tlo.setFillColor(sf::Color(79, 79, 77));
            tlo.setPosition(posX, posY);
            window.draw(tlo);

            sf::RectangleShape count(sf::Vector2f(size, size)); // Obiekt do rysowania liczby min
            count.setFillColor(sf::Color(160, 163, 161));

            sf::RectangleShape item(sf::Vector2f(size, size)); // Obiekt do rysowania flagi lub miny
            item.setFillColor(sf::Color::White);

            char fieldInfo = board.getFieldInfo(row, col);
            int minesCount = board.countMines(row, col);

            switch(fieldInfo) {
                case 'F':
                    item.setTexture(&textures["flag"]);
                    item.setPosition(posX, posY);
                    window.draw(item);
                    break;
                case 'X':
                    item.setTexture(&textures["mine"]);
                    item.setPosition(posX, posY);
                    window.draw(item);
                    break;
                case ' ':
                    count.setPosition(posX,posY);
                    window.draw(count); // Rysuj puste pole
                    continue;
                default:
                    if (minesCount >= 1 and minesCount <= 8) {
                        count.setTexture(&textures[std::to_string(minesCount)]);
                        count.setPosition(posX, posY);
                        window.draw(count); // Rysuj liczbę min
                    }
                    break;
            }
        }
    }

}

void MSBSFMLView::lostText(sf::RenderWindow &window)
{
    sf::RectangleShape lose_text(sf::Vector2f(board_width-2*gap, 100-gap));
    lose_text.setFillColor(sf::Color::White);
    lose_text.setPosition(centerX - board_width / 2.0f + gap, gap);
    lose_text.setTexture(&textures["lose"]);
    window.draw(lose_text);
}

void MSBSFMLView::wonText(sf::RenderWindow &window)
{

    sf::RectangleShape win_text(sf::Vector2f(board_width-2*gap, 100-gap));
    win_text.setFillColor(sf::Color::White);
    win_text.setPosition(centerX - board_width / 2.0f + gap, gap);
    win_text.setTexture(&textures["win"]);
    window.draw(win_text);
}


void MSBSFMLView::displayMines(sf::RenderWindow &window)
{
    draw(window);

    for (int col = 0; col < width; ++col)
    {
        for (int row = 0; row < height; ++row)
        {
            float posX = centerX - board_width / 2.0f + (col + 1) * gap + col * size;
            float posY = 100+(row + 1) * gap + row * size;

            sf::RectangleShape item(sf::Vector2f (size, size));
            item.setFillColor(sf::Color::White);

            if(board.hasMine(row,col))
            {
                item.setTexture(&textures["mine"]);
                item.setPosition(posX, posY);

                window.draw(item);
            }
        }
    }
}

void MSBSFMLView::flagCount(sf::RenderWindow &window)
{
    sf::RectangleShape flagCount_bg((sf::Vector2f(board_width-2*gap, 100-gap)));
    flagCount_bg.setFillColor(sf::Color(79, 79, 77));
    flagCount_bg.setPosition(centerX - board_width / 2.0f + gap, gap);
    window.draw(flagCount_bg);


    sf::RectangleShape flag(sf::Vector2f (100-gap,100-gap));
    flag.setTexture(&textures["flag"]);
    flag.setPosition(gap,gap);
    window.draw(flag);
}

void MSBSFMLView::updateFlagCount(sf::RenderWindow &window)
{
    int flags = board.getFlagCount();
    int flags_left = board.getMineCount() - flags;
    std::ostringstream stream_string;

    static sf::Font font;
    static bool fontLoaded = false;
    if (!fontLoaded) {
        if (!font.loadFromFile("resources/fonts/arial.ttf")) {
            return;
        }
        fontLoaded = true;
    }

    sf::RectangleShape clearRect(sf::Vector2f(100-gap, 100-gap));
    clearRect.setFillColor(sf::Color(79, 79, 77));
    clearRect.setPosition(centerX, gap);
    window.draw(clearRect);

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(80);
    text.setFillColor(sf::Color::White);

    stream_string << flags_left;
    text.setString(stream_string.str());
    text.setPosition(centerX,gap);

    window.draw(text);
}




