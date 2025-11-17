#include <ctype.h>
#include <stdio.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int availableRooms[6] = {0,0,0,0,0,0};
int roomPrices[6] = {100,100,85,75,75,50};
int boards[6] = {0,0,0,0,0,0};
int boardPrices[3] = {5,15,20};
char mainGuestName[6][2][10];
char bookingIDs[6][15] = {"TempID1234"};
int numAdults[6] = {0,0,0,0,0,0};
int numChilds[6] = {0,0,0,0,0,0};
int days[6] = {0,0,0,0,0,0};
int DOBs[6][3] = {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}};
int newspaper[6] = {0,0,0,0,0,0};
int tableAvailability[3][1] = {0,0,0};
bool isLoggedIn = false;
bool run = true;

char mainMenu(void);
void checkIn(void);
void logIn(void);
void loggedIn(void);

int main(void){
    while(run==true) {
        switch (mainMenu()) {
            case '1':
                checkIn();
                break;
            case '2':
                logIn();
                break;
            case '3':
                run = 0;
                break;
            default:
                printf("Invalid Choice.\n");
        }
    }

    return 0;
}

char mainMenu(void) {
    char choice;
    printf("\n1. Check-In\n2. Log-In\n3. End Program\nEnter Choice: ");
    scanf("%c",&choice);
    fflush(stdin);

    return choice;
}

void checkIn(void) {
    printf("Checking In");
}

void logIn(void) {
    char enteredID[15];
    char choice;
    bool attempt = true;
    bool validID = false;
    puts(bookingIDs[0]);
    while (validID == false && attempt == true) {
        printf("Enter bookingID: ");
        gets(enteredID);
        for (int i=0;i<6;i++) {
            if (strcmp(enteredID,bookingIDs[i])==0) {
                validID = true;
            }
        }
        if (validID == false) {
            printf("Invalid ID entered.\n");
            do {
                printf("Would you like to return to main menu? (y/n): ");
                scanf("%c",&choice);
                switch (toupper(choice)) {
                    case 'Y':
                        attempt = false;
                        break;
                    default:
                        printf("Invalid Choice.\n");
                }
            }while (toupper(choice)!= 'Y' || toupper(choice)!='N');
        }
    }
    if (validID == true) {
        loggedIn();
    }
}

void loggedIn(void) {
    isLoggedIn = true;
    printf("Logged In.");
}