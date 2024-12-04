#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Abstract Transport Class (Base for Hierarchical Inheritance)
class Transport {
protected:
    string type;
    double price;

public:
    Transport(string t = "Generic Transport", double p = 0.0) : type(t), price(p) {}
    virtual void displayDetails() = 0; // Pure virtual function
    virtual ~Transport() {}
};

// Derived Classes for Transport (Hierarchical Inheritance)
class Flight : public Transport {
    string airline;

public:
    Flight(string air, double p) : Transport("Flight", p), airline(air) {}
    void displayDetails() override {
        cout << "Type: " << type << ", Airline: " << airline << ", Price: " << price << " PKR\n";
    }
};

class Bus : public Transport {
    string company;

public:
    Bus(string comp, double p) : Transport("Bus", p), company(comp) {}
    void displayDetails() override {
        cout << "Type: " << type << ", Company: " << company << ", Price: " << price << " PKR\n";
    }
};

class Train : public Transport {
    string route;

public:
    Train(string r, double p) : Transport("Train", p), route(r) {}
    void displayDetails() override {
        cout << "Type: " << type << ", Route: " << route << ", Price: " << price << " PKR\n";
    }
};

// Admin Module to Manage Transport and Generate Reports
class Admin {
    vector<Transport*> schedules;

public:
    void addSchedule() {
        int choice;
        cout << "\nSelect Transport Type to Add:\n";
        cout << "1. Flight\n2. Bus\n3. Train\n";
        cout << "Enter choice: ";
        cin >> choice;

        string name;
        double price;
        cin.ignore();
        switch (choice) {
        case 1:
            cout << "Enter Airline Name: ";
            getline(cin, name);
            cout << "Enter Price: ";
            cin >> price;
            schedules.push_back(new Flight(name, price));
            break;
        case 2:
            cout << "Enter Bus Company Name: ";
            getline(cin, name);
            cout << "Enter Price: ";
            cin >> price;
            schedules.push_back(new Bus(name, price));
            break;
        case 3:
            cout << "Enter Train Route: ";
            getline(cin, name);
            cout << "Enter Price: ";
            cin >> price;
            schedules.push_back(new Train(name, price));
            break;
        default:
            cout << "Invalid choice!\n";
            return;
        }
        cout << "Schedule added successfully!\n";
    }

    void viewSchedules() {
        if (schedules.empty()) {
            cout << "\nNo schedules available.\n";
            return;
        }

        cout << "\nTransport Schedules:\n";
        for (size_t i = 0; i < schedules.size(); ++i) {
            cout << i + 1 << ". ";
            schedules[i]->displayDetails();
        }
    }

    ~Admin() {
        for (auto t : schedules)
            delete t; // Free memory
    }
};

// Booking Module with Compile-Time Polymorphism (Function Overloading)
class Booking {
public:
    void bookTransport(string destination) {
        cout << "Booking transport to " << destination << ".\n";
    }

    void bookTransport(string destination, string date) {
        cout << "Booking transport to " << destination << " on " << date << ".\n";
    }

    void bookTransport(string destination, string date, string type) {
        cout << "Booking a " << type << " to " << destination << " on " << date << ".\n";
    }
};

// Main Menu Function
void displayMenu() {
    cout << "\n=== Admin and Booking System ===\n";
    cout << "1. Add Transport Schedule\n";
    cout << "2. View Transport Schedules\n";
    cout << "3. Book Transport\n";
    cout << "4. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    Admin admin;
    Booking booking;
    int choice;

    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
        case 1:
            admin.addSchedule();
            break;
        case 2:
            admin.viewSchedules();
            break;
        case 3: {
            int bookingChoice;
            cout << "\nSelect Booking Option:\n";
            cout << "1. Book by Destination\n";
            cout << "2. Book by Destination and Date\n";
            cout << "3. Book by Destination, Date, and Type\n";
            cout << "Enter your choice: ";
            cin >> bookingChoice;

            string destination, date, type;
            cin.ignore();
            switch (bookingChoice) {
            case 1:
                cout << "Enter Destination: ";
                getline(cin, destination);
                booking.bookTransport(destination);
                break;
            case 2:
                cout << "Enter Destination: ";
                getline(cin, destination);
                cout << "Enter Date: ";
                getline(cin, date);
                booking.bookTransport(destination, date);
                break;
            case 3:
                cout << "Enter Destination: ";
                getline(cin, destination);
                cout << "Enter Date: ";
                getline(cin, date);
                cout << "Enter Type (Flight/Bus/Train): ";
                getline(cin, type);
                booking.bookTransport(destination, date, type);
                break;
            default:
                cout << "Invalid choice!\n";
            }
            break;
        }
        case 4:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}
