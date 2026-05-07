#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

// ====================== RIDER CLASS ======================
class Rider {
private:
    int id;
    string name;
    string phone;
    double currentLat;
    double currentLon;
    bool isInRide;

public:
    // Constructor
    Rider(int id, string name, string phone, double lat, double lon) {
        this->id = id;
        this->name = name;
        this->phone = phone;
        this->currentLat = lat;
        this->currentLon = lon;
        this->isInRide = false;
    }

    // Getters (Encapsulation)
    int getId() const { return id; }
    string getName() const { return name; }
    string getPhone() const { return phone; }
    bool getRideStatus() const { return isInRide; }

    // Setters
    void setRideStatus(bool status) { isInRide = status; }
    void updateLocation(double lat, double lon) {
        currentLat = lat;
        currentLon = lon;
    }

    // Behavior (Abstraction)
    void display() const {
        cout << left << setw(6) << id
             << setw(20) << name
             << setw(15) << phone
             << (isInRide ? "In Ride" : "Available") << endl;
    }
};

// ====================== DRIVER CLASS ======================
class Driver {
private:
    int id;
    string name;
    string phone;
    string vehicle;
    string plate;
    bool isAvailable;

public:
    Driver(int id, string name, string phone, string vehicle, string plate) {
        this->id = id;
        this->name = name;
        this->phone = phone;
        this->vehicle = vehicle;
        this->plate = plate;
        this->isAvailable = true;
    }

    // Getters
    int getId() const { return id; }
    string getName() const { return name; }
    bool getAvailability() const { return isAvailable; }

    // Behavior
    void setAvailability(bool status) { isAvailable = status; }

    void display() const {
        cout << left << setw(6) << id
             << setw(20) << name
             << setw(15) << phone
             << setw(15) << vehicle
             << setw(12) << plate
             << (isAvailable ? "Available" : "Busy") << endl;
    }
};

// ====================== RIDE CLASS ======================
class Ride {
private:
    static int rideCounter;
    int rideId;
    Rider* rider;
    Driver* driver;
    string pickupLocation;
    string dropoffLocation;
    double distance;     // in km
    double fare;
    string status;       // Requested, Ongoing, Completed

public:
    Ride(Rider* r, Driver* d, string pickup, string dropoff, double dist) {
        rideId = ++rideCounter;
        rider = r;
        driver = d;
        pickupLocation = pickup;
        dropoffLocation = dropoff;
        distance = dist;
        fare = dist * 120 + 150;        // Simple fare calculation: KES
        status = "Requested";
    }

    void startRide() {
        if (status == "Requested") {
            status = "Ongoing";
            rider->setRideStatus(true);
            driver->setAvailability(false);
            cout << "\nRide #" << rideId << " has STARTED!\n";
        }
    }

    void completeRide() {
        if (status == "Ongoing") {
            status = "Completed";
            rider->setRideStatus(false);
            driver->setAvailability(true);
            cout << "Ride #" << rideId << " COMPLETED. Total Fare: KES "
                 << fixed << setprecision(0) << fare << endl;
        }
    }

    void display() const {
        cout << "\n--- Ride #" << rideId << " ---\n";
        cout << "Rider   : " << rider->getName() << endl;
        cout << "Driver  : " << driver->getName() << endl;
        cout << "From    : " << pickupLocation << endl;
        cout << "To      : " << dropoffLocation << endl;
        cout << "Distance: " << distance << " km" << endl;
        cout << "Fare    : KES " << fare << endl;
        cout << "Status  : " << status << endl;
    }
};

int Ride::rideCounter = 0;

// ====================== MAIN SYSTEM CLASS ======================
class RideHailingSystem {
private:
    vector<Rider> riders;
    vector<Driver> drivers;
    vector<Ride*> rides;
    int nextRiderId = 1001;
    int nextDriverId = 2001;

public:
    void registerRider() {
        string name, phone;
        double lat, lon;

        cout << "\n--- Register Rider ---\n";
        cout << "Enter Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter Phone: ";
        getline(cin, phone);
        cout << "Current Latitude: ";  cin >> lat;
        cout << "Current Longitude: "; cin >> lon;

        Rider newRider(nextRiderId++, name, phone, lat, lon);
        riders.push_back(newRider);

        cout << "Rider registered successfully! ID = " << (nextRiderId - 1) << endl;
    }

    void registerDriver() {
        string name, phone, vehicle, plate;

        cout << "\n--- Register Driver ---\n";
        cout << "Enter Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter Phone: ";
        getline(cin, phone);
        cout << "Vehicle (e.g. Toyota Camry): ";
        getline(cin, vehicle);
        cout << "Plate Number: ";
        getline(cin, plate);

        Driver newDriver(nextDriverId++, name, phone, vehicle, plate);
        drivers.push_back(newDriver);

        cout << "Driver registered successfully! ID = " << (nextDriverId - 1) << endl;
    }

    void requestRide() {
        if (riders.empty() || drivers.empty()) {
            cout << "Not enough users registered!\n";
            return;
        }

        int riderId, driverId;
        string pickup, dropoff;
        double distance;

        cout << "\nEnter Rider ID: "; cin >> riderId;
        cout << "Enter Driver ID: "; cin >> driverId;
        cin.ignore();
        cout << "Pickup Location: "; getline(cin, pickup);
        cout << "Dropoff Location: "; getline(cin, dropoff);
        cout << "Estimated Distance (km): "; cin >> distance;

        Rider* selectedRider = nullptr;
        Driver* selectedDriver = nullptr;

        for (auto &r : riders) {
            if (r.getId() == riderId) selectedRider = &r;
        }
        for (auto &d : drivers) {
            if (d.getId() == driverId && d.getAvailability())
                selectedDriver = &d;
        }

        if (selectedRider == nullptr || selectedDriver == nullptr) {
            cout << "Invalid Rider or Driver not available!\n";
            return;
        }

        Ride* newRide = new Ride(selectedRider, selectedDriver, pickup, dropoff, distance);
        rides.push_back(newRide);

        cout << "\nRide requested successfully!\n";
        newRide->display();
    }

    void showRiders() const {
        cout << "\n=== Registered Riders ===\n";
        cout << left << setw(6) << "ID" << setw(20) << "Name"
             << setw(15) << "Phone" << "Status\n";
        for (const auto& r : riders) r.display();
    }

    void showDrivers() const {
        cout << "\n=== Registered Drivers ===\n";
        cout << left << setw(6) << "ID" << setw(20) << "Name"
             << setw(15) << "Phone" << setw(15) << "Vehicle"
             << setw(12) << "Plate" << "Status\n";
        for (const auto& d : drivers) d.display();
    }
};

// ====================== MAIN ======================
int main() {
    RideHailingSystem system;
    int choice;

    cout << "=== Simple Ride Hailing System ===\n";

    do {
        cout << "\n1. Register Rider\n";
        cout << "2. Register Driver\n";
        cout << "3. Request Ride\n";
        cout << "4. Show Riders\n";
        cout << "5. Show Drivers\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: system.registerRider(); break;
            case 2: system.registerDriver(); break;
            case 3: system.requestRide(); break;
            case 4: system.showRiders(); break;
            case 5: system.showDrivers(); break;
            case 6: cout << "Goodbye!\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 6);

    return 0;
}
