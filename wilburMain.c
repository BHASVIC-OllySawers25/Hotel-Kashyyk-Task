#include <stdio.h>
double calcRoomTotal(double roomRate[6],double nights[6], int mainGuestAge[6]);
double calcBoardTotal(double boardRate[4][6], double nights[6], int guestAges[3][6], int guestCount[6]);
double calcNewspaper(int Newspaper[6]);
void billCost(char bookingID[6], char mainGuestFirstName[6],char mainGuestSecondName[6], double roomTotal[6], double boardTotal[6], double newspaperCost);
// All that needs doing is intergration as variables need defining from check in
int i =0;
int roomRate[6] = {100,100,85,75,75,50};
int nights[6]= {1, 3, 2, 5, 4, 0};
int mainGuestAge[6] = {36, 27, 0, 0, 0, 0};
double boardRate[6] = {20.0, 10.0 ,5.0, 0.0, 0.0, 5.0};
int Newspaper[6] = {1, 0, 0, 1, 1, 0};
int guestAges[3][6] = {12, 18, 26};
int guestCount[6] = {2, 0, 1, 3, 0, 0};


int main() {
    double roomTotal = calcRoomTotal(roomRate, nights[6], mainGuestAge[6]);
    double boardTotal = calcBoardTotal(boardRate[6], nights[6], guestAges[3][6], guestCount[6]);
    double newspaperCost = calcNewspaper(Newspaper[6]);
    billCost(bookingID[6], mainGuestFirstName[6],mainGuestSecondName[6], roomTotal, boardTotal, newspaperCost);
    return 0;
}


double calcRoomTotal(roomRate[4][6], nights[6], mainGuestAge[6]) {
    double total[i] = roomRate[i] * nights[i];
    if (mainGuestAge[i] >= 65) {
        total[i] = total[i] * 0.90;
    return total[i];
}


double calcBoardTotal(double boardRate[4][6], double nights[6], int guestAges[3][6], int guestCount[6]) {
    double total[i] = 0.0;

    for (int n = 0; n <= guestCount[i]; n++) {
        double cost[n] = boardRate[n][6] * nights;

        if (guestAges[n][6] <= 16) {
            cost[i] = cost[i] * 0.5;

        total[i] = total[i] + cost[i];
    }

    return total;
}
double calcNewspaper(int Newspaper[6]) {
    if (Newspaper[i] == 1) {
        return 5.50;
    } else {
        return 0.0;
    }
}
void billCost(char bookingID[], char mainFirstGuestName[6],mainSecondGuestName[6], double roomTotal[6], double boardTotal[6], double newspaperCost[6]) {
    double overallCost = roomTotal[i] + boardTotal[i] + newspaperCost[i];
    printf("Total cost");
    printf("Booking ID: %s\n", bookingID[i]);
    printf("Main Guest: %s %s\n\n", mainFirstGuestName[i],mainGuestSecondName[i]);

    if (roomTotal[i] > 0)
        printf("Room Cost: £%.2f\n", roomTotal[i]);

    if (boardTotal[i] > 0)
        printf("Board Total: £%.2f\n", boardTotal[i]);

    if (newspaperCost[i] > 0)
        printf("Newspapers: £%.2f\n", newspaperCost[i]);

    printf("\n");
    printf("Total Bill: £%.2f\n", overallCost[i]);
}
