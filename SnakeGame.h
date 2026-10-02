#ifndef SNAKEGAME_H
#define SNAKEGAME_H

#include "LinkedList.h"
#include "Position.h"

using SnakeBody = LinkedList<Position>;

class SnakeGame {
    private:
    SnakeBody snake;
    Position food;

    int score;
    bool isGameOver;

    int width;
    int height;

    void spawnFood();
    void render();
    void update(char input);
    
    public:
    SnakeGame();
    void run();
};


#endif