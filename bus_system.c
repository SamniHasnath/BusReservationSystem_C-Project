#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Bus {
    int bus_no;
    char driver[30];
    char from[20];
    char to[20];
    char arrival[10];
    char departure[10];
    char seat[32][30];   // 32 seats
};

struct Bus buses[10];
int total_buses = 0;

// Function Declarations
void install();
void display();
void allotment();
void show();
void cancel();
int findBus(int);

// Main Function
int main() {
    int choice;

    while(1) {
        printf("\n----------------------------------\n");
        printf("     BUS RESERVATION SYSTEM\n");
        printf("----------------------------------\n");
        printf("1. Install Bus\n");
        printf("2. Book Seat\n");
        printf("3. Show Seat Status\n");
        printf("4. View All Buses\n");
        printf("5. Cancel Booking\n");
        printf("6. Exit\n");
        printf("----------------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: install(); break;
            case 2: allotment(); break;
            case 3: show(); break;
            case 4: display(); break;
            case 5: cancel(); break;
            case 6: exit(0);
            default: printf("Invalid choice!\n");
        }
    }
    return 0;
}

// Find Bus Index
int findBus(int bus_no) {
    int i;
    for(i = 0; i < total_buses; i++) {
        if(buses[i].bus_no == bus_no)
            return i;
    }
    return -1;
}

// Install New Bus
void install() {
    int i;
    struct Bus b;

    printf("Enter Bus Number: ");
    scanf("%d", &b.bus_no);

    if(findBus(b.bus_no) != -1) {
        printf("Bus already exists!\n");
        return;
    }

    printf("Enter Driver Name: ");
    scanf("%s", b.driver);
    printf("From: ");
    scanf("%s", b.from);
    printf("To: ");
    scanf("%s", b.to);
    printf("Arrival Time: ");
    scanf("%s", b.arrival);
    printf("Departure Time: ");
    scanf("%s", b.departure);

    for(i = 0; i < 32; i++) {
        strcpy(b.seat[i], "Empty");
    }

    buses[total_buses] = b;
    total_buses++;

    printf("Bus Installed Successfully!\n");
}
// Display All Buses
void display() {
    int i;
    printf("\nBus No\tDriver\tFrom\tTo\tArr\tDep\n");
    printf("---------------------------------------------\n");

    for(i = 0; i < total_buses; i++) {
        printf("%d\t%s\t%s\t%s\t%s\t%s\n",
               buses[i].bus_no,
               buses[i].driver,
               buses[i].from,
               buses[i].to,
               buses[i].arrival,
               buses[i].departure);
    }
}

// Book Seat
void allotment() {
    int bus_no, seat_no, index;

    printf("Enter Bus Number: ");
    scanf("%d", &bus_no);

    index = findBus(bus_no);
    if(index == -1) {
        printf("Bus not found!\n");
        return;
    }

    printf("Enter Seat Number (1-32): ");
    scanf("%d", &seat_no);

    if(seat_no < 1 || seat_no > 32) {
        printf("Invalid seat number!\n");
        return;
    }

    if(strcmp(buses[index].seat[seat_no - 1], "Empty") != 0) {
        printf("Seat already booked!\n");
    } else {
        printf("Enter Passenger Name: ");
        scanf("%s", buses[index].seat[seat_no - 1]);
        printf("Seat Booked Successfully!\n");
    }
}
// Show Seat Status
void show() {
    int bus_no, i, index;

    printf("Enter Bus Number: ");
    scanf("%d", &bus_no);

    index = findBus(bus_no);
    if(index == -1) {
        printf("Bus not found!\n");
        return;
    }

    printf("\nSeat Status for Bus %d\n", bus_no);
    printf("--------------------------\n");

    for(i = 0; i < 32; i++) {
        printf("Seat %2d : %s\t", i+1, buses[index].seat[i]);
        if((i+1) % 4 == 0)
            printf("\n");
    }
}

// Cancel Booking
void cancel() {
    int bus_no, seat_no, index;

    printf("Enter Bus Number: ");
    scanf("%d", &bus_no);

    index = findBus(bus_no);
    if(index == -1) {
        printf("Bus not found!\n");
        return;
    }

    printf("Enter Seat Number to Cancel: ");
    scanf("%d", &seat_no);

    if(seat_no < 1 || seat_no > 32) {
        printf("Invalid seat number!\n");
        return;
    }

    if(strcmp(buses[index].seat[seat_no - 1], "Empty") == 0) {
        printf("Seat already empty!\n");
    } else {
        strcpy(buses[index].seat[seat_no - 1], "Empty");
        printf("Booking Cancelled Successfully!\n");
    }
}
