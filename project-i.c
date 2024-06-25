#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>

int i;
int level = 1; // Global variable to store the game level

void displayInstructions() {
    system("cls");
    printf("\t\t\t\t\tGame Instructions:\n");
    printf("-> Use arrow keys to move the snake.\n");
    printf("-> You will be provided foods at several coordinates of the screen which you have to eat. Every time you eat a food the length of the snake will be increased by 1 element and thus the score.\n");
    printf("-> You are provided with three lives. Your life will decrease as you hit the wall or snake's body.\n");
    printf("-> You can pause the game in its middle by pressing any key. To continue the paused game press any other key once again.\n");
    printf("\nPress any key to go back to the menu...");
    getch();  // Wait for user input
    system("cls");
}

void gotoxy(int x, int y) {
    COORD p;
    p.X = x;
    p.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}
void boundary() {
    int startX = 5; // Starting x position to center the boundary horizontally
    int startY = 1;  // Starting y position to center the boundary vertically
    int width = 110;  // Width of the boundary
    int height = 25; // Height of the boundary
    system("cls");

    // Draw top boundary
    gotoxy(startX, startY);
    printf("%c", 201);
    for (i = 1; i < width; i++) {
        printf("%c", 205);
    }
    printf("%c", 187);

    // Draw side boundaries
    for (i = 1; i < height; i++) {
        gotoxy(startX, startY + i);
        printf("%c", 186);
        gotoxy(startX + width, startY + i);
        printf("%c", 186);
    }

    // Draw bottom boundary
    gotoxy(startX, startY + height);
    printf("%c", 200);
    for (i = 1; i < width; i++) {
        printf("%c", 205);
    }
    printf("%c", 188);
}

void drawWalls(int level) {
    int startX = 5; // Starting x position to center the boundary horizontally
    int startY = 1;  // Starting y position to center the boundary vertically

    // Adjustments for different levels
    if (level == 2) {
        // Draw walls for medium level
        for (i = startX + 10; i < startX + 30; i++) {
            gotoxy(i, startY + 5);
            printf("%c", 220);
            gotoxy(i, startY + 20);
            printf("%c", 220);
        }
        for (i = startX + 30; i < startX + 52; i++) {
            gotoxy(i, startY + 13);
            printf("%c", 220);
		}
		for (i = startX + 58 ; i < startX + 80; i++) {
            gotoxy(i, startY + 13);
            printf("%c", 220);
        }
        for (i = startX + 80; i < startX + 100 ; i++) {
            gotoxy(i, startY + 5);
            printf("%c", 220);
            gotoxy(i, startY + 20);
            printf("%c", 220);
        }
        for (i = startY + 8 ; i < startY + 18; i++) {
            gotoxy(startX + 20, i);
            printf("%c", 219);
            gotoxy(startX + 90, i);
            printf("%c", 219);
        }
    } else if (level == 3) {
        // Draw walls for hard level
        for (i = startX + 11; i < startX + 40; i++) {
            gotoxy(i, startY + 5);
            printf("%c", 220);
            gotoxy(i, startY + 20);
            printf("%c", 220);
        }
         for (i = startX + 70; i < startX + 100; i++) {
            gotoxy(i, startY + 5);
            printf("%c", 220);
            gotoxy(i, startY + 20);
            printf("%c", 220);
        }
         for (i = startY + 6; i < startY + 11; i++) {
            gotoxy(startX + 11, i);
            printf("%c", 219);
            gotoxy(startX + 99, i);
            printf("%c", 219);
        }
           for (i = startY + 13; i < startY + 19; i++) {
            gotoxy(startX + 11, i);
            printf("%c", 219);
            gotoxy(startX + 99, i);
            printf("%c", 219);
        }
        for (i = startY + 8 ; i < startY + 18; i++) {
            gotoxy(startX + 40, i);
            printf("%c", 219);
            gotoxy(startX + 70, i);
            printf("%c", 219);
        }
          for (i = startY + 2; i < startY + 11; i++) {
            gotoxy(startX + 55, i);
            printf("%c", 219);
        }
           for (i = startY + 14; i < startY + 23; i++) {
            gotoxy(startX + 55, i);
            printf("%c", 219);
        }
    }
}

void move(int *x, int *y, char *l, char c, int len) {
    gotoxy(x[len - 1], y[len - 1]);
    printf(" ");
    for (i = len; i > 0; i--) {
        x[i] = x[i - 1];
        y[i] = y[i - 1];
    }
    *l = c;
    if (len > 1) {
        gotoxy(x[1], y[1]);
        printf("%c", 223);
    }
}

int check(int px, int py, int *x, int *y, int len) {
    for (i = 0; i < len; i++) {
        if (px == x[i] && py == y[i]) {
            return 1;
        }
    }
    return 0;
}

int checkWallCollision(int x, int y, int level) {
    if (level == 2) {
        if ((x >= 10 && x < 30 && (y == 10 || y == 20))) {
            return 1;
        }
    } else if (level == 3) {
        if ((x >= 10 && x < 30 && (y == 10 || y == 20)) || (x >= 50 && x < 70 && (y == 5 || y == 25))) {
            return 1;
        }
    }
    return 0;
}

void over(int x, int y, int len) {
    gotoxy(80, 29);
    printf("%c", 254);
    gotoxy(1, 1);
    printf("Game Over!!!\n");
    printf("%cScore : %d   ", 179, len - 1);
    while (getch() != 13)
        ;
    exit(0);
}

void playGame() {
    system("cls");
    boundary();
    drawWalls(level);
    getch();
    srand(time(NULL));
    int *x, *y, px, py, fx, fy, len = 1;
    char c = 'd', l = 'd';
    clock_t t;

    x = (int *)malloc(sizeof(int) * (len + 1));
    y = (int *)malloc(sizeof(int) * (len + 1));

    // Generate initial snake position
    do {
        px = ((rand() % 58) * 2) + 3;
        py = (rand() % 28) + 1;
    } while (checkWallCollision(px, py, level));

    x[0] = px;
    y[0] = py;

    gotoxy(px, py);
    printf("0");

    gotoxy(x[0], y[0]);
    printf("%c", 247);

    // Generate initial food position
    do {
        fx = ((rand() % 58) * 2) + 3;
        fy = (rand() % 28) + 1;
    } while (checkWallCollision(fx, fy, level) || check(fx, fy, x, y, len));

    gotoxy(fx, fy);
    printf("o");

    while (1) {
        do {
            t = clock();
            while (clock() < t + 250 && !kbhit())
                ;
            if (clock() < t + 250) {
                c = getch();
                if (c == 75 && l == 77)
                    c = 77;
                else if (c == 77 && l == 75)
                    c = 75;
                else if (c == 80 && l == 72)
                    c = 72;
                else if (c == 72 && l == 80)
                    c = 80;
            }

            switch (c) {
                case 0:
                    break;
                case 111:
                    break;
                case 80: // Down
                    move(x, y, &l, c, len);
                    gotoxy(x[0], ++y[0]);
                    printf("v");
                    if (y[0] >= 29 || checkWallCollision(x[0], y[0], level)) {
                        over(x[0], y[0], len);
                    }
                    break;
                case 72: // Up
                    move(x, y, &l, c, len);
                    gotoxy(x[0], --y[0]);
                    printf("%c", 220);
                    if (y[0] < 1 || checkWallCollision(x[0], y[0], level)) {
                        over(x[0], y[0], len);
                    }
                    break;
                case 75: // Left
                    move(x, y, &l, c, len);
                    gotoxy(x[0] = x[0] - 2, y[0]);
                    printf("%c", 223);
                    if (x[0] < 1 || checkWallCollision(x[0], y[0], level)) {
                        over(x[0], y[0], len);
                    }
                    break;
                case 77: // Right
                    move(x, y, &l, c, len);
                    gotoxy(x[0] = x[0] + 2, y[0]);
                    printf("%c", 223);
                    if (x[0] >= 119 || checkWallCollision(x[0], y[0], level)) {
                        over(x[0], y[0], len);
                    }
                    break;
                default:
                    break;
            }
            for (i = 4; i < len; i++) {
                if (x[0] == x[i] && y[0] == y[i])
                    over(x[0], y[0], len);
            }
        } while (x[0] != fx || y[0] != fy);

        gotoxy(x[len], y[len]);
        printf("o");
        len++;

        x = (int *)realloc(x, sizeof(int) * (len + 1));
        y = (int *)realloc(y, sizeof(int) * (len + 1));

        // Generate new food position
        do {
            fx = ((rand() % 58) * 2) + 3;
            fy = (rand() % 28) + 1;
        } while (checkWallCollision(fx, fy, level) || check(fx, fy, x, y, len));

        gotoxy(fx, fy);
        printf("o");
    }
}

void checkHighScore() {
    system("cls");
    printf("\t\t\t\t\tChecking High Score.....\n");
    printf("\nPress any key to go back to the menu...");
    getch();  // Wait for user input
    system("cls");
}

void selectLevel() {
    system("cls");
    printf("\t\t\t\t\tSelect Game Level:\n");
    printf("\t\t\t\t\t1. Easy\n");
    printf("\t\t\t\t\t2. Medium\n");
    printf("\t\t\t\t\t3. Hard\n");
    printf("\t\t\t\t\tEnter your choice: ");
    scanf("%d", &level);
    if (level < 1 || level > 3) {
        level = 1; // Default to easy if an invalid level is chosen
    }
    system("cls");
}

int main() {
    int option;
    char name[100];
    system("color 17");
    printf("Enter your name: ");
    scanf("%s", name);
    do {
        system("cls");
        printf("\t\t\t\t\t\tWelcome to Demo Project\n");
        printf("\t\t\t\t\t 1. Game Instruction\n");
        printf("\t\t\t\t\t 2. Start Game\n");
        printf("\t\t\t\t\t 3. Check High Score\n");
        printf("\t\t\t\t\t 4. Select Level\n");
        printf("\t\t\t\t\t 5. Exit\n");
        printf("\t\t\t\t\t Enter your choice: ");
        scanf("%d", &option);
        switch (option) {
            case 1:
                displayInstructions();
                break;
            case 2:
                playGame();
                break;
            case 3:
                checkHighScore();
                break;
            case 4:
                selectLevel();
                break;
            case 5:
                printf("\t\t\t\t\tExit\n");
                break;
            default:
                printf("Invalid choice. Please enter a number between 1 and 5.\n");
                break;
        }
    } while (option != 5);
    return 0;
}

