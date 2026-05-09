#include <iostream>
#include <string>

using namespace std;

// 1. Passenger Class
class Passenger {
public:
    string name;
    string currentLocation;
    string destination;

    Passenger(string pName, string pLoc, string pDest) {
        name = pName;
        currentLocation = pLoc;
        destination = pDest;
    }

    void requestRide() {
        cout << "\nPassenger " << name << " is requesting a ride from " 
             << currentLocation << " to " << destination << "..." << endl;
    }
};

// 2. Driver Class
class Driver {
public:
    string name;
    string carModel;
    bool isAvailable;

    Driver(string dName, string dCar) {
        name = dName;
        carModel = dCar;
        isAvailable = true;
    }

    void acceptRide(string passengerName) {
        if (isAvailable) {
            cout << "Driver " << name << " (driving a " << carModel 
                 << ") has accepted the ride for " << passengerName << "." << endl;
            isAvailable = false;
        }
    }
};

// 3. Ride Class
class Ride {
private:
    // Making these private demonstrates Encapsulation. 
    // They can only be modified via the setter method.
    double distanceKm;
    double fare;

public:
    Passenger passenger;
    Driver driver;

    // Constructor no longer requires distance upfront
    Ride(Passenger p, Driver d) : passenger(p), driver(d) {
        distanceKm = 0.0;
        fare = 0.0;
    }

    // SETTER METHOD: Sets the distance and determines the fare
    void setDistance(double dist) {
        distanceKm = dist;
        
        // Calculate the fare based on the newly set distance
        double baseFare = 150.0; 
        double ratePerKm = 40.0;
        fare = baseFare + (distanceKm * ratePerKm);
    }

    // Getter-style method to safely display the private fare variable
    void displayFare() {
        cout << "Calculated fare for the " << distanceKm << "km trip: Ksh " << fare << endl;
    }

    void completeRide() {
        cout << "Ride completed successfully. " << passenger.name 
             << " has arrived safely at " << passenger.destination << ".\n" << endl;
        driver.isAvailable = true;
    }
};

int main() {
    string userName, pickupLoc, dropoffLoc;
    double tripDistance;

    cout << "--- WELCOME TO THE RIDE HAILING APP ---" << endl;

    // 1. Collect String Inputs
    cout << "Enter your name: ";
    getline(cin, userName);

    cout << "Enter your pick-up location: ";
    getline(cin, pickupLoc);

    cout << "Enter your drop-off location: ";
    getline(cin, dropoffLoc);

    // 2. Collect Numeric Input for Distance
    cout << "Enter the estimated distance for this trip (in km): ";
    cin >> tripDistance;

    // 3. Initialize Objects
    Passenger currentPassenger(userName, pickupLoc, dropoffLoc);
    Driver availableDriver("Nelson", "Nissan Note");

    currentPassenger.requestRide();
    availableDriver.acceptRide(currentPassenger.name);
    
    cout << "---------------------------------------" << endl;

    // 4. Create the ride without knowing the distance yet
    Ride currentTrip(currentPassenger, availableDriver); 
    
    // 5. Use the SETTER METHOD to input the dynamic distance and calculate fare
    currentTrip.setDistance(tripDistance);
    
    // 6. Display the results
    currentTrip.displayFare();
    currentTrip.completeRide();
    
    cout << "---------------------------------------" << endl;

    return 0;
}
