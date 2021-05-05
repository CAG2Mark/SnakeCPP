#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <vector>
#include <unistd.h>
#include <conio.h>
#include <cstdlib>

using namespace std;

vector<int*> coords;

void clear() {
    system("cls");
    //printf("\033[H\033[J");
}

int X, Y;

int fruit[] = {0, 0};

int dirs[4][2] = {
    {0, -1}, 
    {1, 0}, 
    {0, 1}, 
    {-1, 0}};

void update_fruit(int pos = -1) {
    // generate free locations

    if (pos == -1) pos = abs(rand()) % X*Y;

    for (auto i : coords) {
        if (*(i) + *(i+1)*X == pos) {
            update_fruit(++pos);
            return;
        }
    }
    

    fruit[0] = pos % X;
    fruit[1] = pos / X;
}

int main(int argc, char **argv) {
    X = 70, Y = 20;

    // 0 = up, 1 = right, 2 = down, 3 = left
    char dir = 0;

    int initial = 10;
    int length = initial;

    coords = vector<int*>(length, NULL);
    for (int i = 0; i < length; ++i) {
        coords[i] = (int*) malloc(sizeof(int) * 2);
        coords[i][0] = X/2, coords[i][1] = Y/2 + i;
    }

    update_fruit();

    for(;;) {

        if (_kbhit() && getch() == 224) {
            switch (getch()) {
                case 72:
                    dir = 0;
                break;
                case 77:
                    dir = 1;
                break;
                case 80:
                    dir = 2;
                break;
                case 75:
                    dir = 3;
                break;
            }
        }

        // shift coords
        for (int i = length - 1; i > 0; --i) {
            coords[i][0] = coords[i-1][0];
            coords[i][1] = coords[i-1][1];
        }

        coords[0][0] += dirs[dir][0];
        coords[0][1] += dirs[dir][1];

        // temp

        int cur_x = coords[0][0], cur_y = coords[0][1];

        // loss detection
        
        if (cur_x < 0 || cur_x >= X || cur_y < 0 || cur_y >= Y) {
            break;
        }
        else {
            char flag = 0;
            // check if head is the same as any coords in the current
            for (int i = 1; i < length; ++i) {
                //printf("%d. (%d, %d) <-> (%d, %d)\n", i, cur_x, cur_y, coords[i][0], coords[i][1]);
                if (cur_x == coords[i][0] && cur_y == coords[i][1]) {
                    flag = 1;
                    // break;
                }
            }
            if (flag) break;
        }

        // fruit detection
        if (cur_x == fruit[0] && cur_y == fruit[1]) {
            update_fruit();
            coords.push_back((int*)malloc(sizeof(int)*2));
            coords[length][0] = coords[length-1][0];
            coords[length][1] = coords[length-1][1];

            ++length;
        }
        
        clear();

        // build string
        char* output = (char*) malloc((X + 1) * (Y + 2) * sizeof(char));

        for (int i = 0; i < Y; ++i) {
            for (int j = 0; j < X; ++j) {
                output[(X+1)*i + j] = '.';
            }
            output[(X+1)*i + X] = 10;
        }

        for (int i = 0; i < length; ++i) {
            output[(coords[i][1])*(X+1) + coords[i][0]] = 'X';
        }

        output[(fruit[1])*(X+1) + fruit[0]] = 'O';

        printf("%s\nScore: %d | Fruit: (%d, %d)\n", output, length - initial, fruit[0], fruit[1]);

        usleep(130000);
        
    }

    // clear();

    return 0;   
}