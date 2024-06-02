#include <stdio.h>
#include <stdlib.h>



void displayInstructions() {

    printf("\t\t\t\t\tGame Instructions:\n");
    printf("-> Use arrow keys to move the snake.\n");
    printf("-> You will be provided foods at several coordinates of the screen which you have to eat. Every time you eat a food the length of the snake will be increased by 1 element and thus the score.\n");
    printf("-> You are provided with three lives. Your life will decrease as you hit the wall or snake's body.\n");
    printf("-> You can pause the game in its middle by pressing any key. To continue the paused game press any other key once again.\n");

}

void startGame() {
    printf("\t\t\t\t\tStart Game\n");
}

void checkHighScore() {
    printf("\t\t\t\t\tChecking High Score.....\n");

}

int main() {
    int option;
    char Kaushal[100];
    system("color 17");
         printf("Enter your name:");
         scanf("%s",&Kaushal);
    do {


        printf("\t\t\t\t\t\tWelcome to Demo Project\n");
        printf("\t\t\t\t\t 1. Game Instruction\n");
        printf("\t\t\t\t\t 2. Start Game\n");
        printf("\t\t\t\t\t 3. Check High Score\n");
        printf("\t\t\t\t\t4. Exit\n");
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
                printf("\t\t\t\t\tExit\n");
                break;
            default:
                printf("Invalid choice. Please enter a number between 1 and 4.\n");
                exit(0);
        }
    } while (option != 4);

    return 0;
}

