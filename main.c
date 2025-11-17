#include <stdio.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

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
        choice = 'a';
        printf("Enter bookingID: ");
        gets(enteredID);

        for (int i=0;i<6;i++) {
            if (strcmp(enteredID,bookingIDs[i])==0) {
                validID = true;
            }
        }
        if (validID == false) {
            printf("Invalid ID entered.\n");
            while (tolower(choice)!= 'y' && tolower(choice)!='n') {
                printf("Would you like to return to main menu? (y/n): ");
                scanf("%c",&choice);
                fflush(stdin);
                switch (tolower(choice)) {
                    case 'y':
                        attempt = false;
                        break;
                    case 'n':
                        break;
                    default:
                        printf("Invalid Choice.\n");
                }
            }
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