#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

// Base Class: Person
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

// Derived Class: Customer
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

// Derived Class: FrequentTraveler
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

    int getLoyaltyPoints() const {
        return loyaltyPoints;
    }
};

// Abstract Class: Transport
class Transport {
public:
    virtual void displayDetails() const = 0; // Pure virtual function
    virtual ~Transport() {}
};

// Derived Classes: Flight, Train, Bus
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

// Booking Class
class Booking {
private:
    string destination;
    string date;
    string transportType;

public:
    Booking(const string& dest, const string& dt, const string& transport)
        : destination(dest), date(dt), transportType(transport) {
    }

    void displayBooking() const {
        cout << "Booking Details:\n";
        cout << "Destination: " << destination << "\n";
        cout << "Date: " << date << "\n";
        cout << "Transport Type: " << transportType << "\n";
    }

    string serialize() const {
        return destination + "," + date + "," + transportType + "\n";
    }

    static Booking deserialize(const string& line) {
        size_t pos1 = line.find(',');
        size_t pos2 = line.find(',', pos1 + 1);

        string dest = line.substr(0, pos1);
        string dt = line.substr(pos1 + 1, pos2 - pos1 - 1);
        string transport = line.substr(pos2 + 1);

        return Booking(dest, dt, transport);
    }
};

// Admin Module
class Admin {
private:
    vector<Booking> bookings;
    const string bookingsFile = "bookings.txt";

public:
    void loadBookings() {
        ifstream file(bookingsFile);
        if (!file) {
            cout << "No previous bookings found.\n";
            return;
        }

        string line;
        while (getline(file, line)) {
            bookings.push_back(Booking::deserialize(line));
        }

        file.close();
        cout << "Bookings loaded successfully.\n";
    }

    void saveBookings() {
        ofstream file(bookingsFile);
        for (const Booking& booking : bookings) {
            file << booking.serialize();
        }
        file.close();
        cout << "Bookings saved successfully.\n";
    }

    void addBooking(const Booking& booking) {
        bookings.push_back(booking);
        cout << "Booking added successfully.\n";
    }

    void generateReports() const {
        cout << "\n=== Booking Reports ===\n";
        for (size_t i = 0; i < bookings.size(); ++i) {
            cout << "Booking " << i + 1 << ":\n";
            bookings[i].displayBooking();
            cout << "\n";
        }
    }
};

// Travel Agent Module
class TravelAgent {
public:
    void planMultiModalTravel() {
        cout << "Planning multi-modal travel...\n";
        cout << "Suggested Itinerary: Flight to City A, Train to City B, Bus to City C.\n";
    }

    void offerDiscounts(const vector<FrequentTraveler>& travelers) {
        cout << "Offering discounts to frequent travelers...\n";
        for (const FrequentTraveler& traveler : travelers) {
            if (traveler.getLoyaltyPoints() > 100) {
                cout << "Discount offered to: \n";
                traveler.displayInfo();
                cout << "\n";
            }
        }
    }
};




// Customer Module
class CustomerModule {
private:
    vector<Booking> customerBookings;

public:
    void bookItinerary(const Booking& booking) {
        customerBookings.push_back(booking);
        cout << "Itinerary booked successfully!\n";
    }

    void viewTravelHistory() const {
        if (customerBookings.empty()) {
            cout << "No travel history found.\n";
        }
        else {
            cout << "\n=== Travel History ===\n";
            for (size_t i = 0; i < customerBookings.size(); ++i) {
                cout << "Itinerary " << i + 1 << ":\n";
                customerBookings[i].displayBooking();
                cout << "\n";
            }
        }
    }

    void personalizedRecommendations() const {
        cout << "\n=== Personalized Recommendations ===\n";
        if (!customerBookings.empty()) {
            cout << "Based on your travel history, consider these destinations:\n";
            cout << "- Destination A (popular choice for travelers like you)\n";
            cout << "- Destination B (scenic and relaxing)\n";
            cout << "- Destination C (adventurous and exciting)\n";
        }
        else {
            cout << "No recommendations available. Please book an itinerary first.\n";
        }
    }
};

// Integrate the Customer Module into the Main Function
int main() {
    Admin admin;
    admin.loadBookings();

    vector<FrequentTraveler> travelers;
    TravelAgent travelAgent;
    CustomerModule customerModule;

    while (true) {
        cout << "\n=== Travel Booking System Menu ===\n";
        cout << "1. Sign Up\n2. View Profile\n3. Create Booking\n4. View Bookings\n";
        cout << "5. Generate Reports\n6. Plan Multi-Modal Travel\n7. Offer Discounts\n";
        cout << "8. View Travel History\n9. Personalized Recommendations\n10. Exit\n";
        cout << "Choose an option: ";

        int choice;
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
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
            string destination, date, transportType;

            cout << "Enter your destination: ";
            getline(cin, destination);
            cout << "Enter travel date (YYYY-MM-DD): ";
            getline(cin, date);
            cout << "Enter transport type (Flight/Train/Bus): ";
            getline(cin, transportType);

            Booking newBooking(destination, date, transportType);
            admin.addBooking(newBooking);
            customerModule.bookItinerary(newBooking);

        }
        else if (choice == 4) {
            admin.generateReports();

        }
        else if (choice == 5) {
            admin.saveBookings();

        }
        else if (choice == 6) {
            travelAgent.planMultiModalTravel();

        }
        else if (choice == 7) {
            travelAgent.offerDiscounts(travelers);

        }
        else if (choice == 8) {
            customerModule.viewTravelHistory();

        }
        else if (choice == 9) {
            customerModule.personalizedRecommendations();

        }
        else if (choice == 10) {
            admin.saveBookings();
            cout << "Exiting the program. Goodbye!\n";
            break;

        }
        else {
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}

