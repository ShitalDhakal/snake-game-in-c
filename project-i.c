#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>

int i;
int level = 1; // Add a global variable to store the game level

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
    system("cls");
    // Draw top boundary
    printf("%c", 201);
    for (i = 1; i < 119; i++) {
        printf("%c", 205);
    }
    printf("%c", 187);

    // Draw side boundaries
    for (i = 1; i < 29; i++) {
        gotoxy(0, i);
        printf("%c", 186);
        gotoxy(119, i);
        printf("%c", 186);
    }

    // Draw bottom boundary
    gotoxy(0, 29);
    printf("%c", 200);
    for (i = 1; i < 119; i++) {
        printf("%c", 205);
    }
    printf("%c", 188);

    // Add inner boundary for level 2
    if (level >= 2) {
        for (i = 10; i < 110; i++) {
            gotoxy(i, 10);
            printf("%c", 205);
            gotoxy(i, 20);
            printf("%c", 205);
        }
        for (i = 10; i < 20; i++) {
            gotoxy(10, i);
            printf("%c", 186);
            gotoxy(110, i);
            printf("%c", 186);
        }
    }

    // Add additional obstacles for level 3
    if (level == 3) {
        for (i = 15; i < 105; i++) {
            gotoxy(i, 5);
            printf("%c", 205);
            gotoxy(40, 25);
            printf("%c", 205);
        }
        for (i = 5; i < 25; i++) {
            gotoxy(15, i);
            printf("%c", 186);
            gotoxy(105, 78);
            printf("%c", 186);
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

void startGame() {
    system("cls");
    boundary();
    getch();
    srand(time(NULL));
    int *x, *y, px = ((rand() % 58) * 2) + 3, py = (rand() % 28) + 1, len = 1;
    char c, l;
    clock_t t;

    x = (int *)malloc(sizeof(int) * (len + 1));
    y = (int *)malloc(sizeof(int) * (len + 1));
    x[0] = 25;
    y[0] = 20;

    gotoxy(px, py);
    printf("0");

    gotoxy(x[0], y[0]);
    printf("%c", 247);

    while (1) {
        do {
            t = clock();
            int delay = 250 / level; // Adjust delay based on level
            while (clock() < t + delay && !kbhit())
                ;
            if (clock() < t + delay) {
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
                case 80:
                    move(x, y, &l, c, len);
                    gotoxy(x[0], ++y[0]);
                    printf("v");
                    if (y[0] == 29 || (level >= 2 && (y[0] == 10 || y[0] == 20) && x[0] >= 10 && x[0] <= 110) || (level == 3 && (y[0] == 5 || y[0] == 25) && x[0] >= 15 && x[0] <= 105))
                        over(x[0], y[0], len);
                    break;
                case 72:
                    move(x, y, &l, c, len);
                    gotoxy(x[0], --y[0]);
                    printf("^");
                    if (y[0] == 0 || (level >= 2 && (y[0] == 10 || y[0] == 20) && x[0] >= 10 && x[0] <= 110) || (level == 3 && (y[0] == 5 || y[0] == 25) && x[0] >= 15 && x[0] <= 105))
                        over(x[0], y[0], len);
                    break;
                case 75:
                    move(x, y, &l, c, len);
                    gotoxy(x[0] = x[0] - 2, y[0]);
                    printf("<");
                    if (x[0] == 0 || (level >= 2 && (x[0] == 10 || x[0] == 110) && y[0] >= 10 && y[0] <= 20) || (level == 3 && (x[0] == 15 || x[0] == 105) && y[0] >= 5 && y[0] <= 25))
                        over(x[0], y[0], len);
                    break;
                case 77:
                    move(x, y, &l, c, len);
                    gotoxy(x[0] = x[0] + 2, y[0]);
                    printf(">");
                    if (x[0] == 119 || (level >= 2 && (x[0] == 10 || x[0] == 110) && y[0] >= 10 && y[0] <= 20) || (level == 3 && (x[0] == 15 || x[0] == 105) && y[0] >= 5 && y[0] <= 25))
                        over(x[0], y[0], len);
                    break;
                default:
                    break;
            }
            for (i = 4; i < len; i++) {
                if (x[0] == x[i] && y[0] == y[i])
                    over(x[0], y[0], len);
            }
        } while (x[0] != px || y[0] != py);

        gotoxy(x[len], y[len]);
        printf("o");
        len++;

        x = (int *)realloc(x, sizeof(int) * (len + 1));
        y = (int *)realloc(y, sizeof(int) * (len + 1));

        do {
            py = (rand() % 28) + 1;
            px = ((rand() % 58) * 2) + 3;
        } while (check(px, py, x, y, len));

        gotoxy(px, py);
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
        printf("Invalid choice. Setting level to Easy.\n");
        level = 1;
    }
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
                startGame();
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

