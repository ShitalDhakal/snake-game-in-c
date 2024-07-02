#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include <string.h>

int i,j;
int level = 1; // Global variable to store the game level
char playerName[100]; // Global variable to store the player's name


typedef struct {
    char name[100];
    int score;
    char date[100];
} HighScore;


void displayInstructions();
void gotoxy(int x, int y);
void boundary();
void drawWalls(int level);
int checkWallCollision(int x, int y, int level);
void move(int *x, int *y, char *l, char c, int len);
int check(int px, int py, int *x, int *y, int len);
void over(int len);
void playGame();
void checkHighScore();
void selectLevel();
void saveHighScore(char *name, int score);
void HighScoresDescending(HighScore scores[], int count);
void readHighScores();

void displayInstructions() {
    system("cls");
    printf("\t\t\t\t\t\tGame Instructions:\n\n");
    printf("\t 1. Use the arrow keys to move the snake:\n");
    printf("\t\t- Up Arrow: Move Up\n");
    printf("\t\t- Down Arrow: Move Down\n");
    printf("\t\t- Left Arrow: Move Left\n");
    printf("\t\t- Right Arrow: Move Right\n\n");
    printf("\t 2. Eat the food (%c) to grow your snake and increase your score.\n\n", 148);
    printf("\t 3. Avoid hitting the walls and the snake's own body to prevent the game from ending.\n\n");
    printf("\t 4. Pause the game at any time by pressing any key. Press any key again to resume.\n\n");
    printf("\t 5. Select the game level at the beginning:\n");
    printf("\t- Easy: Slower speed at initial increase speed when start eat food.\n");
    printf("\t- Medium: More obstacles and moderate speed.\n");
    printf("\t- Hard: Complex obstacles and faster speed.\n\n");
    printf("\t Press any key to return to the main menu...");
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
        for (i = startX + 45; i < startX + 65; i++) {
            gotoxy(i, startY + 2);
            printf("%c", 220);
            gotoxy(i, startY + 23);
            printf("%c", 220);
        }
    }
}

int checkWallCollision(int x, int y, int level) {
    // Define wall segments for level 2 and level 3
    if (level == 2) {
        // Medium level walls
        if ((x >= 15 && x < 35 && (y == 6 || y == 21)) ||
            (x >= 35 && x < 57 && y == 14) ||
            (x >= 63 && x < 85 && y == 14) ||
            (x >= 85 && x < 105 && (y == 6 || y == 21)) ||
            (y >= 9 && y < 19 && (x == 25 || x == 95))) {
            return 1; // Collision detected
        }
    } else if (level == 3) {
        // Hard level walls
        if ((x >= 16 && x < 45 && (y == 6 || y == 21)) ||
            (x >= 75 && x < 105 && (y == 6 || y == 21)) ||
            (x >= 50 && x < 70 && (y == 3 || y == 24)) ||
            (y >= 6 && y < 12 && (x == 15 || x == 105)) ||
            (y >= 14 && y < 19 && (x == 15 || x == 105)) ||
            (y >= 9 && y < 19 && (x == 45 || x == 75))) {
            return 1; // Collision detected
        }
    }
    return 0; // No collision
}

void move(int *x, int *y, char *l, char c, int len) {
    gotoxy(x[len - 1], y[len - 1]);
    printf(" ");
    for (i = len - 1; i > 0; i--) {
        x[i] = x[i - 1];
        y[i] = y[i - 1];
    }
    *l = c;
    if (len > 1) {
        gotoxy(x[1], y[1]);
        printf("%c",254);
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

void selectLevel() {
    system("cls");
    printf("Select Game Level:\n");
    printf("1. Easy\n");
    printf("2. Medium\n");
    printf("3. Hard\n");
    printf("Enter your choice: ");
    scanf("%d", &level);
    while (level < 1 || level > 3) {
        printf("Invalid choice. Please enter a valid level (1, 2, or 3): ");
        scanf("%d", &level);
    }
}

void over(int len) {
    int score= len -4;
    gotoxy(50, 10);
    printf("Game Over!");
    gotoxy(50, 12);
    printf("Your Score: %d", score);

    // Save the high score
    saveHighScore(playerName, score);

    // Prompt to return to main menu
    gotoxy(50, 20);
    printf("Press any key to return to the main menu...");
    getch();  // Wait for user input
    system("cls");
}


void playGame() {
    system("cls");
    selectLevel();
    boundary();
    drawWalls(level);
    srand(time(NULL));
    int *x, *y, px, py, fx, fy, len = 4;
    char c = 'd', l = 'd';
    int score = len -4 ;
    int speed;   // Determine initial speed based on level
    int speed_easy = 200; // Initial speed for easy level
    int speed_medium =170; // Initial speed for medium level
    int speed_hard = 140; // Initial speed for hard level
    int food_counter = 0; // Counter to track number of foods eaten
    clock_t t;

    if (level == 1) {
        speed = speed_easy;
    } else if (level == 2) {
        speed = speed_medium;
    } else if (level == 3) {
        speed = speed_hard;
    }

    x = (int *)malloc(sizeof(int) * (len + 1));
    y = (int *)malloc(sizeof(int) * (len + 1));

    // Generate initial snake position
    do {
        px = ((rand() % 54) * 2) + 7;
        py = (rand() % 23) + 2;
    } while (checkWallCollision(px, py, level));

    x[0] = px;
    y[0] = py;

    // Print initial snake position on the board
    gotoxy(px, py);
    printf(">"); // Change the character here to represent the snake's head

    // Print initial food position
    do {
        fx = ((rand() % 54) * 2) + 7;
        fy = (rand() % 23) + 2;
    } while (checkWallCollision(fx, fy, level) || check(fx, fy, x, y, len));

    gotoxy(fx, fy);
    printf("%c", 148); // Change the character here to represent the food symbol

    while (1) {
        do {
            t = clock();
            while (clock() < t + speed && !kbhit());
            if (clock() < t + speed) {
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
                case 111:
                    break;
                case 80: // Down
                    move(x, y, &l, c, len);
                    gotoxy(x[0], ++y[0]);
                    printf("v");
                    if (y[0] >= 26 || checkWallCollision(x[0], y[0], level)) {
                        over(len);
                        return; // Return from playGame() after game over
                    }
                    break;
                case 72: // Up
                    move(x, y, &l, c, len);
                    gotoxy(x[0], --y[0]);
                    printf("^");
                    if (y[0] < 2 || checkWallCollision(x[0], y[0], level)) {
                        over(len);
                        return; // Return from playGame() after game over
                    }
                    break;
                case 75: // Left
                    move(x, y, &l, c, len);
                    gotoxy(x[0] = x[0] - 2, y[0]);
                    printf("<");
                    if (x[0] < 6 || checkWallCollision(x[0], y[0], level)) {
                        over(len);
                        return; // Return from playGame() after game over
                    }
                    break;
                case 77: // Right
                    move(x, y, &l, c, len);
                    gotoxy(x[0] = x[0] + 2, y[0]);
                    printf(">");
                    if (x[0] >= 115 || checkWallCollision(x[0], y[0], level)) {
                        over(len);
                        return; // Return from playGame() after game over
                    }
                    break;
                default:
                    break;
            }
            for (i = 4; i < len; i++) {
                if (x[0] == x[i] && y[0] == y[i])
                    over(len);
            }
        } while (x[0] != fx || y[0] != fy);

        gotoxy(x[len], y[len]);
        len++;

        x = (int *)realloc(x, sizeof(int) * (len + 1));
        y = (int *)realloc(y, sizeof(int) * (len + 1));

        // Increment the score
        score += len-4;


        // Generate new food position
        do {
            fx = ((rand() % 54) * 2) + 7;
            fy = (rand() % 23) + 2;
        } while (checkWallCollision(fx, fy, level) || check(fx, fy, x, y, len));

        // Display the new food position on the game board
        gotoxy(fx, fy);
        printf("%c", 148); // Change the character here to represent the food symbol

        // Increase speed after every 4 foods eaten for easy level
        if (level == 1) {
            food_counter++;
            if (food_counter == 4) {
                speed -= 25; // Decrease speed by 25ms (increase speed)
                food_counter = 0; // Reset food counter
            }
        }
    }
}

void checkHighScore() {
    system("cls");
    printf("View High Scores:\n");
    printf("1. Easy\n");
    printf("2. Medium\n");
    printf("3. Hard\n");
    printf("Enter your choice: ");
    scanf("%d", &level);
    while (level < 1 || level > 3) {
        printf("Invalid choice. Please enter a valid level (1, 2, or 3): ");
        scanf("%d", &level);
    }
    readHighScores();
}

void HighScoresDescending(HighScore scores[], int count) {
    HighScore temp;
    for ( i = 0; i < count - 1; i++) {
        for (j = 0; j < count - i - 1; j++) {
            if (scores[j].score < scores[j + 1].score) {
                temp = scores[j];
                scores[j] = scores[j + 1];
                scores[j + 1] = temp;
            }
        }
    }
}
void saveHighScore(char *name, int score) {
    FILE *fp;
    time_t t;
    struct tm *timestamp;
    time(&t);
    timestamp = localtime(&t);

    // Format the date and time
    char score_date[20];
    strftime(score_date, sizeof(score_date), "%Y-%m-%d %H:%M:%S", timestamp);

    // Determine the file name based on the selected level
    char filename[30];  // Adjust size based on your file names
    if (level == 1) {
        strcpy(filename, "easy_level_highscore.txt");
    } else if (level == 2) {
        strcpy(filename, "medium_level_highscore.txt");
    } else {
        strcpy(filename, "hard_level_highscore.txt");
    }

    // Open the file in append mode
    fp = fopen(filename, "a+");
    if (fp == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    // Write the score to the file
    fprintf(fp, "%s %d %s\n", name, score, score_date);
    fclose(fp);

    printf("High score saved successfully.\n");
}

void readHighScores() {
    FILE *fp;
    char line[256];
    HighScore scores[100];  // Array to store high scores
    int count = 0;

    // Determine the file name based on the selected level
    char filename[30];  // Adjust size based on your file names
    if (level == 1) {
        strcpy(filename, "easy_level_highscore.txt");
    } else if (level == 2) {
        strcpy(filename, "medium_level_highscore.txt");
    } else {
        strcpy(filename, "hard_level_highscore.txt");
    }

    // Open the file for reading
    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error opening file for reading.\n");
        return;
    }

    // Read scores from the file
    while (fgets(line, sizeof(line), fp)) {
        sscanf(line, "%s %d %[^\n]", scores[count].name, &scores[count].score, scores[count].date);
        count++;
    }
    fclose(fp);

    HighScoresDescending(scores,count);

    // Display the top scores
    system("cls");
    printf("High Scores:\n");
    printf("Rank\tName\t\tScore\tDate\n");
    for (i = 0; i < count && i < 3; i++) {
        printf("%d\t%s\t\t%d\t%s\n", i + 1, scores[i].name, scores[i].score, scores[i].date);
    }

    printf("\nPress any key to return to the main menu...");
    getch();
    system("cls");
}



int main() {
    int choice;
    system("color E2");
    printf("Enter your name: ");
    fgets(playerName, sizeof(playerName), stdin);
    playerName[strcspn(playerName, "\n")] = '\0';

    while (1) {
        system("cls");
        printf("\t\t\t\t\t\tSnake Game\n");
        printf("\t\t\t\t\t\t1. Play Game\n");
        printf("\t\t\t\t\t\t2. Game Instructions\n");
        printf("\t\t\t\t\t\t3. View High Scores\n");
        printf("\t\t\t\t\t\t4. Exit\n");
        printf("\t\t\t\t\t\tEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                playGame();
                break;
            case 2:
                displayInstructions();
                break;
            case 3:
                checkHighScore();
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
