//
// Created by c on 3/13/24.
//

#ifndef LAB_2_MINESWEEPERBOARD_H
#define LAB_2_MINESWEEPERBOARD_H

enum GameMode { DEBUG, EASY, NORMAL, HARD };
enum GameState { RUNNING, FINISHED_WIN, FINISHED_LOSS };

struct Field
{
    bool hasMine;
    bool hasFlag;
    bool isRevealed;
};
class MinesweeperBoard
{
    Field board[100][100];
    GameMode mode;
    int height;
    int width;
    bool firstMove = true;
    int bombs;
    int flags = 0;
    bool gameLost = false;
    void moveBomb(int row, int col);
    bool checkIfWon() const;
    int placeBombs(enum GameMode mode);
    bool isInBounds(int row, int col) const;
    void recurence(int row, int col);

public:
    MinesweeperBoard();
    MinesweeperBoard(int width, int height, GameMode mode);
    void debug_display() const;
    inline int getBoardWidth() const {return width;};
    inline int getBoardHeight() const {return height;};
    int getMineCount() const;
    int getFlagCount() const;
    int countMines(int row, int col) const;
    bool hasMine(int row, int col) const;
    void toggleFlag(int row, int col);
    void revealField(int row, int col);
    bool isRevealed(int row, int col);
    GameState getGameState() const;
    char getFieldInfo(int row, int col) const;

};

#endif //LAB_2_MINESWEEPERBOARD_H
