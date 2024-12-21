#include <iostream>
#include <string>
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

// Compile-Time Polymorphism: Function Overloading
class Booking {
public:
    void searchBooking(const string& destination) {
        cout << "Searching for bookings to " << destination << ".\n";
    }

    void searchBooking(const string& destination, const string& date) {
        cout << "Searching for bookings to " << destination << " on " << date << ".\n";
    }

    void searchBooking(const string& destination, const string& date, const string& transportType) {
        cout << "Searching for " << transportType << " bookings to " << destination << " on " << date << ".\n";
    }
};

int main() {
    // Input from user
    string userName, userEmail, destination, date;
    int userId, loyaltyPoints;

    cout << "Enter your name: ";
    getline(cin, userName);
    cout << "Enter your ID: ";
    cin >> userId;
    cin.ignore();
    cout << "Enter your email: ";
    getline(cin, userEmail);
    cout << "Enter loyalty points: ";
    cin >> loyaltyPoints;
    cin.ignore();

    cout << "Enter your destination: ";
    getline(cin, destination);
    cout << "Enter travel date (YYYY-MM-DD): ";
    getline(cin, date);

    // Core Feature 1: Demonstrating Inheritance
    cout << "\n=== Inheritance Demonstration ===\n";
    FrequentTraveler traveler(userName, userId, userEmail, loyaltyPoints);
    traveler.displayInfo();

    // Core Feature 2: Demonstrating Polymorphism
    cout << "\n=== Polymorphism Demonstration ===\n";
    Transport* transport;
    Flight flight;
    Train train;
    Bus bus;

    transport = &flight;
    transport->displayDetails();

    transport = &train;
    transport->displayDetails();

    transport = &bus;
    transport->displayDetails();

    // Compile-Time Polymorphism
    cout << "\n=== Compile-Time Polymorphism ===\n";
    Booking booking;
    booking.searchBooking(destination);
    booking.searchBooking(destination, date);
    booking.searchBooking(destination, date, "Flight");

    return 0;
}
