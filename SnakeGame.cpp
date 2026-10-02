#include "SnakeGame.h"
#include <iostream>
#include <cstdlib>
#include <stdexcept>

using namespace std;


SnakeGame::SnakeGame(){
    width = 20;
    height = 10;
    score = 0;
    isGameOver = false;

    snake.insert(0,{5,7});
    snake.insert(0,{5,6});
    snake.insert(0,{5,5});

    spawnFood();
}

void SnakeGame::spawnFood(){
    bool validSpot = false;

    while(!validSpot){
        food.row = (rand() % (height - 2)) + 1;
        food.column = (rand() % (width - 2)) + 1;

        validSpot = true;
        for(int i = 0; i < snake.getLength(); i++){
            if(food == snake.get(i)){
                validSpot = false;
                break;
            }
        }
    }
}

void SnakeGame::render(){
    system("cls");

    string board[10];
    for(int r = 0; r < height; r++){
        board[r] = string(width, ' ');
        board[r][0] = '#';
        board[r][width - 1] = '#';
    }
    for(int c = 0; c < width; c++){
        board[0][c] = '#';
        board[height - 1][c] = '#';
    }


    board[food.row][food.column] = '*';


    for(int i = 0; i < snake.getLength(); i++){
        Position s = snake.get(i);

        if(i == 0){
            board[s.row][s.column] = 'O';
        } else {
            board[s.row][s.column] = 'o';
        }
    }


    for(int r = 0; r < height; r++){
        cout<<board[r]<<endl;
    }
    cout << "Score: " << score << " | Length: " << snake.getLength() << "\n";
}

void SnakeGame::update(char input){

    Position head = snake.get(0);
    Position nextHead = head;

    if (input == 'w' || input == 'W') {
        nextHead.row--;
    } else if (input == 's' || input == 'S') {
        nextHead.row++;
    } else if (input == 'a' || input == 'A') {
        nextHead.column--;
    } else if (input == 'd' || input == 'D') {
        nextHead.column++;
    } else {
        return; 
    }

    if (snake.getLength() > 1 && nextHead == snake.get(1)){
        return;
    }

    if(nextHead.row <= 0 || nextHead.row >= height - 1 || 
        nextHead.column <= 0 || nextHead.column >= width - 1){
            isGameOver = true;
            return;
    }

    for(int i = 0; i < snake.getLength() - 1; i++){
        if(snake.get(i) == nextHead){
            isGameOver = true;
            return;
        }
    }

    snake.insert(0, nextHead);

    if(nextHead == food){
        score += 10;
        spawnFood();
    } else {
        snake.remove(snake.getLength() - 1);
    }

}

void SnakeGame::run(){
    char input;
    while(!isGameOver){
        render();
        cout << "Enter W/A/S/D to move: " << endl;
        cout << "Enter Q to quit. "<<endl;
        cin >> input;

        if(input == 'q' || input == 'Q'){
            isGameOver = true;
            break;
        }

        update(input);
    }

    render();
    cout<<"Game Over"<<endl;
    cout<<"Final Score: "<< score << endl;
}