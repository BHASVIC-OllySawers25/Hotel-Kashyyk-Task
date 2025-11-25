#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>


// the gloabl arrays + variables used
int availableRooms[6] = {0,0,0,0,0,0};
int roomPrices[6] = {100,100,85,75,75,50};
int boards[6] = {0,0,0,0,0,0};
int boardPrices[3] = {5,15,20};
char mainGuestName[6][2][10];
char bookingIDs[6][15];
int numAdults[6] = {0,0,0,0,0,0};
int numChilds[6] = {0,0,0,0,0,0};
int days[6] = {0,0,0,0,0,0};
int DOBs[6][3] = {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}};
int newspaper[6] = {0,0,0,0,0,0};
int tableAvailability[6] = {0,0,0,0,0,0};
int hasTable[6] = {0,0,0,0,0,0};
int loggedInRoomIndex;
bool isLoggedIn;
bool run;

// Declaring Functions
int loggedInMenu(void);
void loggedIn(void);
void checkOut(void);
void bookTable(void);
float discount(int dateOfBirth[3]);

// makeID()
// this function generates the userID, js surname + random 3 digit number (100-999)
void makeID(char surname[], char* output) {
    int randomNum;

    // take a seed for the random number w time
    srand(time(NULL));

    // generate the random number itself
    randomNum = (rand() % 900) + 100;

    // put them together n that
    sprintf(output, "%s%d", surname, randomNum);
}


// logIn()
// ok so in my approach this basically automatically logs u in and takes u to the logged in menu
// but some checks are done before, depending on whether you logged in from main menu or after checking in
void logIn(char* id, int room) {

    // just make logged in status = 1, meaning true
    isLoggedIn = true;

    printf("\n========================================\n");
    printf("     LOGIN SUCCESSFUL!\n");
    printf("========================================\n");

    loggedIn();
}


// findRoom()
// to search for user IDs to make sure they are real
int findRoom(char bookingIDs[6][15], char id[15]) {
    for (int i = 0; i < 6; i++) {
        if (strcmp(bookingIDs[i], id) == 0) {
            return i;       // it is found so the room index is returned
        }
    }
    return -1;              // when its not found
}

// loginGateway()
// this just basically checks if they are logging in through the checkin function - where we already know their ID
// or if they are logging in directly from the main menu - where we dont know their ID so need to ask for it
void loginGateway(char bookingIDs[6][15], char *autoID) {
    char id[15];

    if (autoID == NULL) {
        // from main menu
        printf("Enter your userID: ");
        scanf("%s", id);
        fflush(stdin);
    } else {
        // automatically from checkin function
        strcpy(id, autoID);
    }

    int room = findRoom(bookingIDs, id);

    if (room == -1) {
        printf("Invalid ID. Returning to main menu.\n");
        return;
    }

    printf("Welcome back %s, in room %d.\n", id, room);

    for (int i=0;i<6;i++) {
        if (strcmp(id,bookingIDs[i])==0) {
            loggedInRoomIndex = i;
        }
    }
    printf("Index: %d",loggedInRoomIndex);

    // now the login function is run
    logIn(id, room);
}


// checkIn()
// the big function itself, one massive heap of switch case, basically if smth breaks in this part we r cooked
void checkIn() {
    int screen = 1;  // is in charge of deciding what scrn is visible
    int keepGoing = 1;
    int roomIndex = -1;  // will store where the user is staying via room index

    // temp vars to store stuff while checking in
    char firstName[10];
    char lastName[10];
    int day, month, year;
    int totalGuests;
    int adults, children;
    int stayDays;
    int wantNewspaper;
    int boardChoice;
    int roomChoice;
    int budget = 0;  // like a budget for rooms, acts just like a filter (0 = show all)

    // the main switch case loop for the different screens
    while(keepGoing) {
        switch(screen) {

            // scrn 1 - welcome and menu switch
            case 1:
                printf("\n========================================\n");
                printf("     KASHYYYK HOTEL - CHECK IN\n");
                printf("========================================\n");
                printf("\n1. Enter guest details\n");
                printf("2. Set room budget filter\n");
                printf("3. Back to main menu\n");
                printf("\nEnter choice: ");

                int choice1;
                scanf("%d", &choice1);
                fflush(stdin);

                if(choice1 == 1) {
                    screen = 2;  // start the never ending data entry
                } else if(choice1 == 2) {
                    screen = 8;  // go to scrn 8 (room budget)
                } else if(choice1 == 3) {
                    keepGoing = 0;  // go back to main menu
                }
                break;


            // scrn 2 - get the guests names
            case 2:



                printf("\n========================================\n");
                printf("     GUEST DETAILS - NAME\n");
                printf("========================================\n");
                printf("Enter main guest's first name: ");
                scanf("%s", firstName);
                fflush(stdin);
                printf("Enter main guest's surname: ");
                scanf("%s", lastName);
                fflush(stdin);



                screen = 3;  // got to scrn 3
                break;


            // scrn 3 - dob
            case 3:
                printf("\n========================================\n");
                printf("     GUEST DETAILS - DATE OF BIRTH\n");
                printf("========================================\n");
                printf("Enter date of birth (DD/MM/YYYY) format\n");
                printf("Day: ");
                scanf("%d", &day);
                fflush(stdin);
                printf("Month: ");
                scanf("%d", &month);
                fflush(stdin);
                printf("Year: ");
                scanf("%d", &year);
                fflush(stdin);

                screen = 4;  // go to scrn 4
                break;


            // scrn 4 - guest amount (4 max)
            case 4:
                printf("\n========================================\n");
                printf("     GUEST DETAILS - PARTY SIZE\n");
                printf("========================================\n");
                printf("Enter total number of guests (max 4): ");
                scanf("%d", &totalGuests);
                fflush(stdin);

                // make sure its acc a max of 4
                if(totalGuests > 4 || totalGuests < 1) {
                    printf("\nERROR: Must have 1-4 guests.\n");
                    printf("Press Enter to try again...");
                    getchar();

                    break;  // stay on this scrn
                }

                printf("How many adults? ");
                scanf("%d", &adults);
                fflush(stdin);
                printf("How many children (16 or under)? ");
                scanf("%d", &children);
                fflush(stdin);

                // make sure the numbers acc add up the total they said were staying
                if(adults + children != totalGuests) {
                    printf("\nERROR: Adults + Children must equal total guests!\n");
                    printf("Press Enter to try again...");
                    getchar();
                    break;  // stay on this scrn
                }

                screen = 5;  // got to scrn 5
                break;


            // scrn 5 - length of stay
            case 5:
                printf("\n========================================\n");
                printf("     GUEST DETAILS - LENGTH OF STAY\n");
                printf("========================================\n");
                printf("How many days will you be staying? ");
                scanf("%d", &stayDays);
                fflush(stdin);

                if(stayDays < 1) {
                    printf("\nERROR: Must stay at least 1 day.\n");
                    printf("Press Enter to try again...");
                    getchar();
                    break;
                }

                screen = 6;  // go to scrn 6
                break;


            // scrn 6 - newspaper
            case 6:
                printf("\n========================================\n");
                printf("     GUEST DETAILS - NEWSPAPER\n");
                printf("========================================\n");
                printf("Would you like a daily newspaper?\n");
                printf("(One-off charge of $5.50)\n");
                printf("1. Yes\n");
                printf("2. No\n");
                printf("\nEnter choice: ");
                scanf("%d", &wantNewspaper);
                fflush(stdin);

                if(wantNewspaper == 1) {
                    wantNewspaper = 1;
                } else {
                    wantNewspaper = 0;
                }

                screen = 7;  // go to scrn 7
                break;


            // scrn 7 - board details
            case 7:
                printf("\n========================================\n");
                printf("     GUEST DETAILS - BOARD TYPE\n");
                printf("========================================\n");
                printf("Select your board type:\n");
                printf("1. Bed & Breakfast ($5 per person per day)\n");
                printf("2. Half Board ($15 per person per day)\n");
                printf("3. Full Board ($20 per person per day)\n");
                printf("\nEnter choice: ");
                scanf("%d", &boardChoice);
                fflush(stdin);

                if(boardChoice < 1 || boardChoice > 3) {
                    printf("\nERROR: Invalid choice. Please select 1, 2, or 3.\n");
                    printf("Press Enter to try again...");
                    getchar();
                    break;
                }

                screen = 9;  // go to room display
                break;


            // scrn 8 - room budget
            case 8:
                printf("\n========================================\n");
                printf("     SET ROOM BUDGET FILTER\n");
                printf("========================================\n");
                printf("Enter maximum room price per night (0 for all rooms): $");
                scanf("%d", &budget);
                fflush(stdin);

                screen = 1;  // back to main checkin scrn after resetting budget (idk why this is the only way that works but it is)
                break;


            // scrn 9 - show all available rooms
        case 9:
            printf("\n========================================\n");
            printf("     AVAILABLE ROOMS\n");
            printf("========================================\n");

            // room prices
            roomPrices[0] = 100;
            roomPrices[1] = 100;
            roomPrices[2] = 85;
            roomPrices[3] = 75;
            roomPrices[4] = 75;
            roomPrices[5] = 50;

            printf("Room\tPrice/Night\tStatus\n");
            printf("----\t-----------\t------\n");

            for(int i = 0; i < 6; i++) {
                if(budget > 0 && roomPrices[i] > budget) {
                    continue;
                }

                printf("%d\t$%d\t\t", i+1, roomPrices[i]);

                if(availableRooms[i] == 0) {
                    printf("AVAILABLE\n");
                } else {
                    printf("OCCUPIED\n");
                }
            }

            printf("\n1. Select a room\n");
            printf("2. Change budget filter\n");
            printf("3. Back to details entry\n");
            printf("\nEnter choice: ");

            int choice9;
            scanf("%d", &choice9);
            fflush(stdin);

            if(choice9 == 1) {
                screen = 10;
            } else if(choice9 == 2) {
                screen = 8;
            } else if(choice9 == 3) {
                screen = 1;
            }
            break;


            // scrn 10 - room select
            case 10:
                printf("\n========================================\n");
                printf("     ROOM SELECTION\n");
                printf("========================================\n");
                printf("Enter room number (1-6): ");
                scanf("%d", &roomChoice);
                fflush(stdin);

                // quickly validate the room choice
                if(roomChoice < 1 || roomChoice > 6) {
                    printf("\nERROR: Invalid room number.\n");
                    printf("Press Enter to try again...");
                    getchar();
                    screen = 9;  // back to main display or the rooms
                    break;
                }

                // room available ?
                if(availableRooms[roomChoice - 1] == 1) {
                    printf("\nERROR: Room %d is already occupied!\n", roomChoice);
                    printf("Press Enter to try again...");
                    getchar();
                    screen = 9;  // back to main display or the rooms
                    break;
                }

                // room is available so store the index of the room
                roomIndex = roomChoice - 1;

                screen = 11;  // to scrn 11
                break;


            // scrn 11 - final admin stuff and making the actual user ID
            case 11:
                // get the data that was taken in and stored in temp vars into the acc global ones
                strcpy(mainGuestName[roomIndex][0], firstName);
                strcpy(mainGuestName[roomIndex][1], lastName);
                DOBs[roomIndex][0] = day;
                DOBs[roomIndex][1] = month;
                DOBs[roomIndex][2] = year;
                numAdults[roomIndex] = adults;
                numChilds[roomIndex] = children;
                days[roomIndex] = stayDays;
                newspaper[roomIndex] = wantNewspaper;
                boards[roomIndex] = boardChoice;
                availableRooms[roomIndex] = 1;  // make sure the room is noted as currently unavailable

                // get ID
                char newID[15];
                makeID(lastName, newID);
                strcpy(bookingIDs[roomIndex], newID);

                // display confromation
                printf("\n========================================\n");
                printf("     CHECK-IN COMPLETE!\n");
                printf("========================================\n");
                printf("Guest: %s %s\n", firstName, lastName);
                printf("Room: %d\n", roomChoice);
                printf("Length of stay: %d days\n", stayDays);
                printf("\nYour Booking ID is: %s\n", newID);
                printf("\nPlease remember this ID for booking tables\n");
                printf("and checking out.\n");
                printf("========================================\n");

                printf("\nPress Enter to continue to your account...");
                getchar();

                // automatically log them in via gateway using new ID
                loginGateway(bookingIDs, newID);


                keepGoing = 0;  // exit the checkin
                break;
        }
    }
}

void loggedIn(void) {
    isLoggedIn = true;
    while(isLoggedIn==true) {
        switch (loggedInMenu()) {
            case 1:
                checkOut();
            break;
            case 2:
                bookTable();
            break;
            case 3:
                isLoggedIn = false;
            break;
            default:
                printf("Invalid Choice.\n");
        }
    }
}

int loggedInMenu(void) {
    int choice;
    printf("\n========================================\n");
    printf("            KASHYYYK HOTEL\n");
    printf("========================================\n");
    printf("1. Check Out\n");
    printf("2. Book Table\n");
    printf("3. Log Out\n");
    printf("Enter choice: ");
    scanf("%d",&choice);
    fflush(stdin);
    return choice;
}

float discount(int dateOfBirth[3]) {
    float discount = 1;
    int year=2025, month, day;
    if (year-dateOfBirth[3] >= 65) {
        discount = 0.9;
    }
    return discount;
}

void bookTable()
{
    if (boards[loggedInRoomIndex] != 1) {

        printf("\n========================================\n");
        printf("     AVAILABLE TABLES\n");
        printf("========================================\n");

        int bookedTable = 0;
        printf("Please select a table to use for the duration of your stay\t");
        printf("\n1. Endor 7pm\n");
        printf("2. Tatooine 7pm\n");
        printf("3. Naboo 7pm\n");
        printf("4. Endor 9pm\n");
        printf("5. Tatooine 9pm\n");
        printf("6. Naboo 9pm\n");

        printf("Enter the number for the table you want");
        scanf("%d", &bookedTable);
        if (tableAvailability[bookedTable-1] == 0 && bookedTable > 0 && bookedTable < 7 && hasTable[loggedInRoomIndex] > 0) {
            printf("Table %d is now booked!\nCheck out to unbook table.", bookedTable);
            tableAvailability[bookedTable-1] = 1;
            hasTable[loggedInRoomIndex] = bookedTable;
        }
        else {
            printf("Invalid Table or Table already booked or you already have a table.");
        }


    }

    else {

    printf("Cannot book table with b&b board.");

    }

}

void checkOut(void) {
    float roomCost, adultBoardCost,childBoardCost,newspaperCost = 0,totalBoardCost, totalBill;
    int confirm = 0;
    printf("Are you sure you want to check out?\n1. Yes\n2. No\nEnter Choice: ");
    scanf("%d",&confirm);
    if (confirm == 1) {
        roomCost = roomPrices[loggedInRoomIndex] * days[loggedInRoomIndex] * discount(DOBs[loggedInRoomIndex]);
        adultBoardCost = boardPrices[boards[loggedInRoomIndex]-1] * numAdults[loggedInRoomIndex] * days[loggedInRoomIndex];
        if (newspaper[loggedInRoomIndex]==1) {newspaperCost =5.5;}
        childBoardCost = 0.5 * boardPrices[boards[loggedInRoomIndex]-1] * numChilds[loggedInRoomIndex] * days[loggedInRoomIndex];
        totalBoardCost = childBoardCost + adultBoardCost;
        totalBill = totalBoardCost + roomCost + newspaperCost;

        printf("Thanks for stating %s %s.\nBookingID: %s", mainGuestName[loggedInRoomIndex][0],mainGuestName[loggedInRoomIndex][1], bookingIDs[loggedInRoomIndex]);
        printf("\n\nBill:\nRoom Cost: $%f\nBoard Cost: $%f\nNewspaper Cost: $%f\nTotal: $%f", roomCost,totalBoardCost,newspaperCost,totalBill);
        printf("\nPress Enter to continue...");
        getchar();

        if (hasTable[loggedInRoomIndex]>0) {
            tableAvailability[hasTable[loggedInRoomIndex]-1] = 0;
        }

        hasTable[loggedInRoomIndex] = 0;
        availableRooms[loggedInRoomIndex] = 0;
        DOBs[loggedInRoomIndex][0] = 0;
        DOBs[loggedInRoomIndex][1] = 0;
        DOBs[loggedInRoomIndex][2] = 0;
        boards[loggedInRoomIndex] = 0;
        numAdults[loggedInRoomIndex] = 0;
        numChilds[loggedInRoomIndex] = 0;
        days[loggedInRoomIndex] = 0;
        newspaper[loggedInRoomIndex] = 0;


        isLoggedIn = false;
    }
    else if (confirm==2){
        printf("\nReturning to Menu.");
    }
    else {
        printf("\nInvalid Choice. Reutrning to Menu.");
    }

}



int main(void) {
    // reset the variables to appropriate starting values js incase program ended
    for (int i = 0; i < 6; i++) {
        availableRooms[i] = 0;
        numAdults[i] = 0;
        numChilds[i] = 0;
        days[i] = 0;
        newspaper[i] = 0;
        boards[i] = 0;
        roomPrices[i] = 0;
        strcpy(bookingIDs[i], "");
        strcpy(mainGuestName[i][0], "");
        strcpy(mainGuestName[i][1], "");
        for (int j = 0; j < 3; j++) {
            DOBs[i][j] = 0;
        }
    }

    // the state of program via bools (global)
    run = true;
    isLoggedIn = false;


    //this is just a quick little menu used for testing the program
    int choice = 0;

    while (run) {
        printf("\n========================================\n");
        printf("            KASHYYYK HOTEL\n");
        printf("========================================\n");
        printf("1. Check In\n");
        printf("2. Log In\n");
        printf("3. Quit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        fflush(stdin);

        if (choice == 1) {
            checkIn();      //type shi ive been workin on
        }
        else if (choice == 2) {
            loginGateway(bookingIDs, NULL); //also more shi ive been workin on - this makes them enter ID if logging in without checking in
        }
        else if (choice == 3) { //this basically ends the program so DONT PRESS IT
            printf("Exiting program...\n");
            run = false;
        }
        else {
            printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}
