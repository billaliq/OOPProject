#include <iostream>
#include <string>
using namespace std;

// Base Class: Booking
class Booking {
protected:
    string bookingID;
    string customerName;

public:
    // Constructor to initialize Booking details
    Booking() {}

    void inputBookingDetails() {
        cout << "Enter Booking ID: ";
        cin >> bookingID;
        cin.ignore(); // Clear input buffer
        cout << "Enter Customer Name: ";
        getline(cin, customerName);
    }

    void displayBookingDetails() {
        cout << "Booking ID: " << bookingID << endl;
        cout << "Customer Name: " << customerName << endl;
    }
};

// Derived Class: FlightBooking
class FlightBooking : public Booking {
private:
    string flightNumber;
    string departureTime;

public:
    // Constructor
    FlightBooking() {}

    void inputFlightDetails() {
        inputBookingDetails();
        cout << "Enter Flight Number: ";
        cin >> flightNumber;
        cin.ignore();
        cout << "Enter Departure Time: ";
        getline(cin, departureTime);
    }

    void displayFlightDetails() {
        displayBookingDetails();
        cout << "Flight Number: " << flightNumber << endl;
        cout << "Departure Time: " << departureTime << endl;
    }
};

// Main Function
int main() {
    FlightBooking fb;

    cout << "---- Flight Booking System ----" << endl;
    fb.inputFlightDetails();

    cout << "\n---- Booking Details ----" << endl;
    fb.displayFlightDetails();

    return 0;
}
