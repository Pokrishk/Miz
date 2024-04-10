#include <iostream>
#include <conio.h> 
#include <windows.h> 

using namespace std;

const int width = 20;
const int height = 20;

class Snake {
private:
    int x, y;
    int tailX[400], tailY[400];
    int Tail;

public:
    Snake() {
        x = width / 2;
        y = height / 2;
        Tail = 0;
    }

    void Move(int dir) {
        int tailtooX = tailX[0];
        int tailtooY = tailY[0];
        int tailtoo2X, tailtoo2Y;
        tailX[0] = x;
        tailY[0] = y;
        for (int i = 1; i < Tail; i++) {
            tailtoo2X = tailX[i];
            tailtoo2Y = tailY[i];
            tailX[i] = tailtooX;
            tailY[i] = tailtooY;
            tailtooX = tailtoo2X;
            tailtooY = tailtoo2Y;
        }
        switch (dir) {
        case 0:
            x--;
            break;
        case 1:
            x++;
            break;
        case 2:
            y--;
            break;
        case 3:
            y++;
            break;
        default:
            break;
        }
    }

    void IncreaseTail() {
        Tail++;
    }

    int getX() const {
        return x;
    }

    int getY() const {
        return y;
    }

    int getTail() const {
        return Tail;
    }

    int getTailX(int index) const {
        return tailX[index];
    }

    int getTailY(int index) const {
        return tailY[index];
    }
};

class Food {
private:
    int x, y;

public:
    Food() {
        x = rand() % width;
        y = rand() % height;
    }

    int getX() const {
        return x;
    }

    int getY() const {
        return y;
    }

    void Spawn() {
        x = rand() % width;
        y = rand() % height;
    }
};

void Play(Snake& snake, Food& food) {
    system("cls");
    for (int i = 0; i < width + 2; i++)
        cout << "-";
    cout << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0)
                cout << "|";
            if (i == snake.getY() && j == snake.getX())
                cout << "%";
            else if (i == food.getY() && j == food.getX())
                cout << "*";
            else {
                bool print = false;
                for (int k = 0; k < snake.getTail(); k++) {
                    if (snake.getTailX(k) == j && snake.getTailY(k) == i) {
                        cout << "&";
                        print = true;
                    }
                }
                if (!print)
                    cout << " ";
            }

            if (j == width - 1)
                cout << "|";
        }
        cout << endl;
    }

    for (int i = 0; i < width + 2; i++)
        cout << "-";
    cout << endl;
}

void Input(Snake& snake) {
    if (_kbhit()) {
        switch (_getch()) {
        case 'a':
            snake.Move(0);
            break;
        case 'd':
            snake.Move(1);
            break;
        case 'w':
            snake.Move(2);
            break;
        case 's':
            snake.Move(3);
            break;
        }
    }
}

bool Collision(const Snake& snake, const Food& food) {
    if (snake.getX() == food.getX() && snake.getY() == food.getY())
        return true;
    else
        return false;
}

void Logic(Snake& snake, Food& food, bool& End) {
    if (snake.getX() >= width || snake.getX() < 0 || snake.getY() >= height || snake.getY() < 0)
        End = true;
    for (int i = 0; i < snake.getTail(); i++) {
        if (snake.getX() == snake.getTailX(i) && snake.getY() == snake.getTailY(i))
            End = true;
    }
    if (Collision(snake, food)) {
        food.Spawn();
        snake.IncreaseTail();
    }
}

int main() {
    Snake snake;
    Food food;
    bool End = false;

    while (!End) {
        Play(snake, food);
        Input(snake);
        Logic(snake, food, End);
        Sleep(100);
    }
}
