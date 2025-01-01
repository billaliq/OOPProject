#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
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
        : Person(customerName, customerId), email(customerEmail) {}

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
        : Customer(travelerName, travelerId, travelerEmail), loyaltyPoints(points) {}

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
    double price;

public:
    Booking(const string& dest, const string& dt, const string& transport, double bookingPrice)
        : destination(dest), date(dt), transportType(transport), price(bookingPrice) {}

    void displayBooking() const {
        cout << "Booking Details:\n";
        cout << "Destination: " << destination << "\nDate: " << date << "\nTransport Type: " << transportType << "\nPrice: " << price << "\n";
    }

    void modifyBooking(const string& newDest, const string& newDate, const string& newTransport, double newPrice) {
        destination = newDest;
        date = newDate;
        transportType = newTransport;
        price = newPrice;
    }

    string serialize() const {
        return destination + "," + date + "," + transportType + "," + to_string(price) + "\n";
    }

    static Booking deserialize(const string& line) {
        size_t pos1 = line.find(',');
        size_t pos2 = line.find(',', pos1 + 1);
        size_t pos3 = line.find(',', pos2 + 1);

        string dest = line.substr(0, pos1);
        string dt = line.substr(pos1 + 1, pos2 - pos1 - 1);
        string transport = line.substr(pos2 + 1, pos3 - pos2 - 1);
        double price = stod(line.substr(pos3 + 1));

        return Booking(dest, dt, transport, price);
    }
};

// Admin Module
class Admin {
private:
    vector<Booking> bookings;
    map<string, double> dynamicPricing;
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

    void modifyBooking(size_t index, const Booking& newBooking) {
        if (index < bookings.size()) {
            bookings[index] = newBooking;
            cout << "Booking modified successfully.\n";
        } else {
            cout << "Invalid booking index.\n";
        }
    }

    void cancelBooking(size_t index) {
        if (index < bookings.size()) {
            bookings.erase(bookings.begin() + index);
            cout << "Booking canceled successfully.\n";
        } else {
            cout << "Invalid booking index.\n";
        }
    }

    void generateReports() const {
        cout << "\n=== Booking Reports ===\n";
        for (size_t i = 0; i < bookings.size(); ++i) {
            cout << "Booking " << i + 1 << ":\n";
            bookings[i].displayBooking();
            cout << "\n";
        }
    }

    void setDynamicPricing(const string& season, double multiplier) {
        dynamicPricing[season] = multiplier;
    }

    double getDynamicPrice(const string& season, double basePrice) const {
        if (dynamicPricing.count(season)) {
            return basePrice * dynamicPricing.at(season);
        }
        return basePrice;
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

// Travel Itinerary Management
class TravelItinerary {
private:
    vector<Booking> combinedBookings;

public:
    void addBooking(const Booking& booking) {
        combinedBookings.push_back(booking);
    }

    void generateItinerary() const {
        cout << "\n=== Detailed Travel Itinerary ===\n";
        for (size_t i = 0; i < combinedBookings.size(); ++i) {
            cout << "Booking " << i + 1 << ":\n";
            combinedBookings[i].displayBooking();
            cout << "\n";
        }
    }

    void shareItinerary(const string& email) const {
        cout << "Itinerary sent to: " << email << "\n";
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
        } else {
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
        } else {
            cout << "No recommendations available. Please book an itinerary first.\n";
        }
    }
};

// Main Function
int main() {
    Admin admin;
    admin.loadBookings();

    TravelItinerary itinerary;
    CustomerModule customerModule;
    TravelAgent travelAgent;
    vector<FrequentTraveler> travelers;

    while (true) {
        cout << "\n=== Travel Booking System Menu ===\n";
        cout << "1. Create Booking\n2. Modify Booking\n3. Cancel Booking\n4. Generate Reports\n5. Plan Multi-Modal Travel\n6. Offer Discounts\n7. Generate Itinerary\n8. View Travel History\n9. Personalized Recommendations\n10. Exit\nChoose an option: ";

        int choice;
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            string destination, date, transportType;
            double price;

            cout << "Enter destination: ";
            getline(cin, destination);
            cout << "Enter travel date (YYYY-MM-DD): ";
            getline(cin, date);
            cout << "Enter transport type (Flight/Train/Bus): ";
            getline(cin, transportType);
            cout << "Enter price: ";
            cin >> price;
            cin.ignore();

            Booking newBooking(destination, date, transportType, price);
            admin.addBooking(newBooking);
            customerModule.bookItinerary(newBooking);
            itinerary.addBooking(newBooking);

        } else if (choice == 2) {
            size_t index;
            cout << "Enter booking index to modify: ";
            cin >> index;
            cin.ignore();

            string destination, date, transportType;
            double price;

            cout << "Enter new destination: ";
            getline(cin, destination);
            cout << "Enter new travel date (YYYY-MM-DD): ";
            getline(cin, date);
            cout << "Enter new transport type (Flight/Train/Bus): ";
            getline(cin, transportType);
            cout << "Enter new price: ";
            cin >> price;
            cin.ignore();

            Booking modifiedBooking(destination, date, transportType, price);
            admin.modifyBooking(index - 1, modifiedBooking);

        } else if (choice == 3) {
            size_t index;
            cout << "Enter booking index to cancel: ";
            cin >> index;
            cin.ignore();

            admin.cancelBooking(index - 1);

        } else if (choice == 4) {
            admin.generateReports();

        } else if (choice == 5) {
            travelAgent.planMultiModalTravel();

        } else if (choice == 6) {
            travelAgent.offerDiscounts(travelers);

        } else if (choice == 7) {
            itinerary.generateItinerary();

        } else if (choice == 8) {
            customerModule.viewTravelHistory();

        } else if (choice == 9) {
            customerModule.personalizedRecommendations();

        } else if (choice == 10) {
            admin.saveBookings();
            cout << "Exiting the program. Goodbye!\n";
            break;

        } else {
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
