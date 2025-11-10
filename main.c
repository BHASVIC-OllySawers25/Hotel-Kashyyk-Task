#include <stdio.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int availableRooms[6] = {0,0,0,0,0,0};
int roomPrices[6] = {100,100,85,75,75,50};
int boards[6] = {0,0,0,0,0,0};
int boardPrices[3] = {20,15,5};
char mainGuestName[6][2][10];
char bookingIDs[6][15];
int numAdults[6] = {0,0,0,0,0,0};
int numChilds[6] = {0,0,0,0,0,0};
int days[6] = {0,0,0,0,0,0};
int DOBs[6][3] = {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}};
int newspaper[6] = {0,0,0,0,0,0};
int tableAvailability[3][1] = {0,0,0};
bool loggdeIn = 0;
bool run = 1;

int mainMenu(void);
void checkIn(void);
void logIn(void);

int main(void){
    do {
        switch (mainMenu()) {
            case 1:
                checkIn();
                break;
            case 2:
                logIn();
                break;
            case 3:
                run = 0;
                break;
            default:
                printf("Invalid Input.\n");
        }
    }while(run==1);

    return 0;
}

int mainMenu(void) {
    int choice;
    printf("\n1. Check-In\n2. Log-In\n3. End Program\nEnter Choice: ");
    scanf("%d",&choice);
    return choice;
}

void checkIn(void) {

}

void logIn(void) {


}