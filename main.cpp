#include <iostream> 
#include "SnakeGame.h"

using namespace std;

int main(){
    char playAgain;

    do {
        SnakeGame game;
        game.run();

        cout << "Would you like to play again?(Y/N) " << endl;
        cin >> playAgain;

    } while (playAgain == 'y' || playAgain == 'Y');

    cout << "Thank you for playing !!! " << endl;
    return 0;
}