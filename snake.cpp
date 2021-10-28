// snake.cpp 
// version 1.1

#include <iostream>

#include <windows.h>

#include <conio.h>

using namespace std;
const int map_width = 16;
const int map_height = 8;
int x, y, score, fruitX, fruitY;

bool gameOver;

int tailX[64], tailY[64];
int nTail;

enum eDirection {
        STOP = 0, LEFT, RIGHT, UP, DOWN
};
eDirection dir;

void Setup() {
        dir = STOP;
        gameOver = false;
        x = map_width / 2 - 1;
        y = map_height / 2 - 1;
        fruitX = rand() % map_width - 1;
        fruitY = rand() % map_height;
        score = 0;
}

void Draw() {
        system("cls");
        for (int i = 0; i < map_width + 1; i++) {
                cout << "#";
        }
        cout << endl;

        for (int i = 0; i < map_height; i++) {
                for (int j = 0; j < map_width; j++) {
                        if (j == 0 || j == map_width - 1)
                                cout << "#";
                        if (i == y && j == x)
                                cout << "O";
                        else if (i == fruitY && j == fruitX)
                                cout << "N";
                        else {
                                bool print = false;
                                for (int k = 0; k < nTail; k++) {
                                        if (tailX[k] == j && tailY[k] == i) {
                                                print = true;
                                                cout << "*";
                                        }
                                }
                                if (!print) {
                                        cout << " ";
                                }

                        }
                }
                cout << endl;

        }
        for (int i = 0; i < map_width + 1; i++) {
                cout << "#";
        }
        cout << endl;
        cout << "score: " << score;
}

void Input() {
        if (_kbhit()) {
                switch (_getch()) {
                case 'a':
                        dir = LEFT;
                        break;
                case 'e':
                        dir = RIGHT;
                        break;
                case ',':
                        dir = UP;
                        break;
                case 'o':
                        dir = DOWN;
                        break;
                case 'x':
                        gameOver = true;
                }
        }
}
void Logic() {
        int prevX = tailX[0];
        int prevY = tailY[0];
        int prev2X, prev2Y;
        tailX[0] = x;
        tailY[0] = y;
        for (int i = 1; i < nTail; i++) {

                prev2X = tailX[i];
                prev2Y = tailY[i];

                tailX[i] = prevX;
                tailY[i] = prevY;

                prevX = prev2X;
                prevY = prev2Y;

        }
        switch (dir) {
        case LEFT:
                x--;
                break;
        case RIGHT:
                x++;
                break;
        case UP:
                y--;
                break;
        case DOWN:
                y++;
                break;

        }
        //if (x > map_width || x < 0 || y > map_height || y < 0)
        //gameOver = TRUE;
        if (x >= map_width - 1)
                x = 0;
        else if (x < 0)
                x = map_width - 2;

        if (y >= map_height)
                y = 0;
        else if (y < 0)
                y = map_height - 1;

        for (int i = 0; i < nTail; i++) {
                if (tailX[i] == x && tailY[i] == y) {
                        gameOver = true;
                }
        }
        if (x == fruitX && y == fruitY) {
                score += 10;
                fruitX = rand() % map_width - 1;
                fruitY = rand() % map_height;
                nTail++;
        }
}

int main() {
        Setup();
        while (!gameOver) {
                Draw();
                Input();
                Logic();
                Sleep(250);
        }
}
