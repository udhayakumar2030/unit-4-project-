/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/


#include <stdio.h>
#include <string.h>

#define MAX 100

// Enumeration for vehicle type
enum VehicleType {
    CAR = 1,
    BIKE = 2
};

// Enumeration for rental status
enum RentalStatus {
    AVAILABLE = 1,
    RENTED = 2
};

// Union for vehicle-specific details
union VehicleDetails {
    int seats;
    int engineCapacity;
};

// Structure for vehicle information
struct Vehicle {
    int id;
    char name[50];
    char brand[50];

    enum VehicleType type;
    enum RentalStatus status;

    union VehicleDetails details;
};

// Global array
struct Vehicle vehicles[MAX];
int count = 0;

// Function declarations
void addVehicle();
void displayVehicles();
void searchVehicle();
void rentVehicle();
void returnVehicle();
void displayAvailableVehicles();
int findVehicle(int id);

// Find vehicle using ID
int findVehicle(int id) {
    int i;

    for (i = 0; i < count; i++) {
        if (vehicles[i].id == id) {
            return i;
        }
    }

    return -1;
}

// Add a new vehicle
void addVehicle() {
    if (count >= MAX) {
        printf("\nVehicle limit reached!\n");
        return;
    }

    struct Vehicle v;

    printf("\nEnter Vehicle ID: ");
    scanf("%d", &v.id);

    if (findVehicle(v.id) != -1) {
        printf("\nVehicle ID already exists!\n");
        return;
    }

    printf("Enter Vehicle Name: ");
    scanf(" %49[^\n]", v.name);

    printf("Enter Brand: ");
    scanf(" %49[^\n]", v.brand);

    printf("\nSelect Vehicle Type:\n");
    printf("1. Car\n");
    printf("2. Bike\n");
    printf("Enter choice: ");
    scanf("%d", (int *)&v.type);

    if (v.type == CAR) {
        printf("Enter Number of Seats: ");
        scanf("%d", &v.details.seats);
    }
    else if (v.type == BIKE) {
        printf("Enter Engine Capacity (CC): ");
        scanf("%d", &v.details.engineCapacity);
    }
    else {
        printf("\nInvalid Vehicle Type!\n");
        return;
    }

    v.status = AVAILABLE;

    vehicles[count] = v;
    count++;

    printf("\nVehicle Added Successfully!\n");
}

// Display all vehicles
void displayVehicles() {
    int i;

    if (count == 0) {
        printf("\nNo vehicles registered!\n");
        return;
    }

    printf("\n========== ALL VEHICLES ==========\n");

    for (i = 0; i < count; i++) {
        printf("\nVehicle ID: %d", vehicles[i].id);
        printf("\nName: %s", vehicles[i].name);
        printf("\nBrand: %s", vehicles[i].brand);

        if (vehicles[i].type == CAR) {
            printf("\nType: Car");
            printf("\nNumber of Seats: %d",
                   vehicles[i].details.seats);
        }
        else {
            printf("\nType: Bike");
            printf("\nEngine Capacity: %d CC",
                   vehicles[i].details.engineCapacity);
        }

        if (vehicles[i].status == AVAILABLE) {
            printf("\nStatus: Available\n");
        }
        else {
            printf("\nStatus: Rented\n");
        }
    }
}

// Search vehicle
void searchVehicle() {
    int id, index;

    printf("\nEnter Vehicle ID to Search: ");
    scanf("%d", &id);

    index = findVehicle(id);

    if (index == -1) {
        printf("\nVehicle Not Found!\n");
    }
    else {
        printf("\nVehicle Found!\n");
        printf("Vehicle ID: %d\n", vehicles[index].id);
        printf("Name: %s\n", vehicles[index].name);
        printf("Brand: %s\n", vehicles[index].brand);

        if (vehicles[index].type == CAR) {
            printf("Type: Car\n");
            printf("Seats: %d\n",
                   vehicles[index].details.seats);
        }
        else {
            printf("Type: Bike\n");
            printf("Engine Capacity: %d CC\n",
                   vehicles[index].details.engineCapacity);
        }

        printf("Status: %s\n",
            vehicles[index].status == AVAILABLE ?
            "Available" : "Rented");
    }
}

// Rent vehicle
void rentVehicle() {
    int id, index;

    printf("\nEnter Vehicle ID to Rent: ");
    scanf("%d", &id);

    index = findVehicle(id);

    if (index == -1) {
        printf("\nVehicle Not Found!\n");
    }
    else if (vehicles[index].status == RENTED) {
        printf("\nVehicle is Already Rented!\n");
    }
    else {
        vehicles[index].status = RENTED;
        printf("\nVehicle Rented Successfully!\n");
    }
}

// Return vehicle
void returnVehicle() {
    int id, index;

    printf("\nEnter Vehicle ID to Return: ");
    scanf("%d", &id);

    index = findVehicle(id);

    if (index == -1) {
        printf("\nVehicle Not Found!\n");
    }
    else if (vehicles[index].status == AVAILABLE) {
        printf("\nVehicle is Already Available!\n");
    }
    else {
        vehicles[index].status = AVAILABLE;
        printf("\nVehicle Returned Successfully!\n");
    }
}

// Display available vehicles
void displayAvailableVehicles() {
    int i, found = 0;

    printf("\n======= AVAILABLE VEHICLES =======\n");

    for (i = 0; i < count; i++) {
        if (vehicles[i].status == AVAILABLE) {
            found = 1;

            printf("\nID: %d", vehicles[i].id);
            printf("\nName: %s", vehicles[i].name);
            printf("\nBrand: %s", vehicles[i].brand);

            if (vehicles[i].type == CAR) {
                printf("\nType: Car");
                printf("\nSeats: %d\n",
                       vehicles[i].details.seats);
            }
            else {
                printf("\nType: Bike");
                printf("\nEngine Capacity: %d CC\n",
                       vehicles[i].details.engineCapacity);
            }
        }
    }

    if (found == 0) {
        printf("\nNo Vehicles Available!\n");
    }
}

// Main function
int main() {
    int choice;

    do {
        printf("\n\n===== VEHICLE RENTAL MANAGEMENT SYSTEM =====\n");
        printf("1. Add Vehicle\n");
        printf("2. Display All Vehicles\n");
        printf("3. Search Vehicle\n");
        printf("4. Rent Vehicle\n");
        printf("5. Return Vehicle\n");
        printf("6. Display Available Vehicles\n");
        printf("7. Exit\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addVehicle();
                break;

            case 2:
                displayVehicles();
                break;

            case 3:
                searchVehicle();
                break;

            case 4:
                rentVehicle();
                break;

            case 5:
                returnVehicle();
                break;

            case 6:
                displayAvailableVehicles();
                break;

            case 7:
                printf("\nThank You! Exiting Program...\n");
                break;

            default:
                printf("\nInvalid Choice! Try Again.\n");
        }

    } while (choice != 7);

    return 0;
}
