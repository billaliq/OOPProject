#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Base Class: Person (Core Feature 1: Inheritance)
class Person {
protected:
    string name;
    int id;

public:
    Person(const string& personName, int personId) : name(personName), id(personId) {}

    virtual void displayInfo() const {
        cout << "Name: " << name << "\nID: " << id << "\n";
    }

    virtual ~Person() {}
};

// Derived Class: Customer (Inheritance)
class Customer : public Person {
protected:
    string email;

public:
    Customer(const string& customerName, int customerId, const string& customerEmail)
        : Person(customerName, customerId), email(customerEmail) {
    }

    void displayInfo() const override {
        Person::displayInfo();
        cout << "Email: " << email << "\n";
    }
};

// Derived Class: FrequentTraveler (Multilevel Inheritance)
class FrequentTraveler : public Customer {
private:
    int loyaltyPoints;

public:
    FrequentTraveler(const string& travelerName, int travelerId, const string& travelerEmail, int points)
        : Customer(travelerName, travelerId, travelerEmail), loyaltyPoints(points) {
    }

    void displayInfo() const override {
        Customer::displayInfo();
        cout << "Loyalty Points: " << loyaltyPoints << "\n";
    }
};

// Abstract Class: Transport (Core Feature 2: Polymorphism)
class Transport {
public:
    virtual void displayDetails() const = 0; // Pure virtual function
    virtual ~Transport() {}
};

// Derived Classes: Flight, Train, and Bus (Polymorphism)
class Flight : public Transport {
public:
    void displayDetails() const override {
        cout << "Flight: Flight Number - FL123, Departure - 10:00 AM.\n";
    }
};

class Train : public Transport {
public:
    void displayDetails() const override {
        cout << "Train: Train Number - TR456, Departure - 9:30 AM.\n";
    }
};

class Bus : public Transport {
public:
    void displayDetails() const override {
        cout << "Bus: Route Number - B123, Departure - 8:00 AM.\n";
    }
};

// Dynamic Memory Management for Bookings
class Booking {
private:
    string* destination;
    string* date;
    string* transportType;

public:
    Booking(const string& dest, const string& dt, const string& transport) {
        destination = new string(dest);
        date = new string(dt);
        transportType = new string(transport);
    }

    void displayBooking() const {
        cout << "Booking Details:\n";
        cout << "Destination: " << *destination << "\n";
        cout << "Date: " << *date << "\n";
        cout << "Transport Type: " << *transportType << "\n";
    }

    ~Booking() {
        delete destination;
        delete date;
        delete transportType;
        cout << "Booking memory released.\n";
    }

    // Copy constructor to handle dynamic memory
    Booking(const Booking& other) {
        destination = new string(*other.destination);
        date = new string(*other.date);
        transportType = new string(*other.transportType);
    }

    // Assignment operator to handle dynamic memory
    Booking& operator=(const Booking& other) {
        if (this != &other) {
            delete destination;
            delete date;
            delete transportType;

            destination = new string(*other.destination);
            date = new string(*other.date);
            transportType = new string(*other.transportType);
        }
        return *this;
    }
};

// Main Function
int main() {
    vector<FrequentTraveler> travelers; // Store registered travelers
    vector<Booking*> bookings; // Store dynamic bookings

    while (true) {
        cout << "\n=== Travel Booking System Menu ===\n";
        cout << "1. Sign Up\n2. View Profile\n3. Create Booking\n4. View Bookings\n5. View Transport Options\n6. Exit\n";
        cout << "Choose an option: ";

        int choice;
        cin >> choice;
        cin.ignore(); // To ignore the newline character after entering the choice

        if (choice == 1) {
            // Sign-Up Feature
            string name, email;
            int id, loyaltyPoints;

            cout << "Enter your name: ";
            getline(cin, name);
            cout << "Enter your ID: ";
            cin >> id;
            cin.ignore();
            cout << "Enter your email: ";
            getline(cin, email);
            cout << "Enter your loyalty points: ";
            cin >> loyaltyPoints;
            cin.ignore();

            travelers.emplace_back(name, id, email, loyaltyPoints);
            cout << "Sign-up successful!\n";

        }
        else if (choice == 2) {
            // View Profile
            if (travelers.empty()) {
                cout << "No profiles found. Please sign up first.\n";
            }
            else {
                cout << "\n=== Registered Travelers ===\n";
                for (size_t i = 0; i < travelers.size(); ++i) {
                    cout << "Traveler " << i + 1 << ":\n";
                    travelers[i].displayInfo();
                    cout << "\n";
                }
            }

        }
        else if (choice == 3) {
            // Create Booking
            string destination, date, transportType;

            cout << "Enter your destination: ";
            getline(cin, destination);
            cout << "Enter travel date (YYYY-MM-DD): ";
            getline(cin, date);
            cout << "Enter transport type (Flight/Train/Bus): ";
            getline(cin, transportType);

            Booking* newBooking = new Booking(destination, date, transportType);
            bookings.push_back(newBooking);
            cout << "Booking created successfully!\n";

        }
        else if (choice == 4) {
            // View Bookings
            if (bookings.empty()) {
                cout << "No bookings found.\n";
            }
            else {
                cout << "\n=== Existing Bookings ===\n";
                for (size_t i = 0; i < bookings.size(); ++i) {
                    cout << "Booking " << i + 1 << ":\n";
                    bookings[i]->displayBooking();
                    cout << "\n";
                }
            }

        }
        else if (choice == 5) {
            // View Transport Options
            cout << "\n=== Available Transport Options ===\n";
            Flight flight;
            Train train;
            Bus bus;

            Transport* transport;
            transport = &flight;
            transport->displayDetails();

            transport = &train;
            transport->displayDetails();

            transport = &bus;
            transport->displayDetails();

        }
        else if (choice == 6) {
            // Exit
            cout << "Exiting the program. Goodbye!\n";
            break;

        }
        else {
            cout << "Invalid choice. Please try again.\n";
        }
    }

    // Clean up dynamic bookings
    for (Booking* booking : bookings) {
        delete booking;
    }

    return 0;
}
