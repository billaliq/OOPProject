#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

void printTitleInRed() {
    cout << "\033[31m";
    cout << " _____                                  _   _____     _         __  __                                              _     ____            _                 \n";
    cout << "|_   |_  _   _ _ __    __ _ _ __   _| | |   | __()_ __   |  \\/  | __ _ _ __   __ _  __ _ _ __ ___   ___ _ __ | |_  / __| _   _ ___| | ___ _ __ ___  \n";
    cout << "  | |/ _ \\| | | | '|  / ` | ' \\ / ` |   | || '| | ' \\  | |\\/| |/ ` | ' \\ / ` |/ _` | ' ` _ \\ / _ \\ '_ \\| _| \\__ \\| | | / _| __/ _ \\ ' ` _ \\ \n";
    cout << "  | | () | || | |    | (| | | | | (| |   | || |  | | |) | | |  | | (| | | | | (| | (| | | | | | |  _/ | | | |   __) | || \\__ \\ ||  __/ | | | | |\n";
    cout << "  ||\\/ \\,||     \\,|| ||\\,|   ||||  || ./  ||  ||\\,|| ||\\,|\\, || || ||\\|| ||\\| |/ \\, |/\\\\|| || ||\n";
    cout << "                                                       ||                               |/                                  |_/                      \n";
    cout << "\033[0m";
}

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

    const string bookingsFile = "bookings.txt";

public:
    vector<Booking> bookings;
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

// Booking Management Module
class BookingManagement {
public:
    void modifyBooking(Booking& booking, const string& newDest, const string& newDate, const string& newTransport) {
        booking = Booking(newDest, newDate, newTransport);
        cout << "Booking modified successfully!\n";
    }

    void cancelBooking(vector<Booking>& bookings, size_t index) {
        if (index < bookings.size()) {
            bookings.erase(bookings.begin() + index);
            cout << "Booking canceled successfully!\n";
        }
        else {
            cout << "Invalid booking index!\n";
        }
    }

    double calculateDynamicPrice(double basePrice, double multiplier) const {
        return basePrice * multiplier;
    }
};

// Travel Itinerary Management Module
class TravelItineraryManagement {
public:
    void combineBookings(const vector<Booking>& bookings) {
        cout << "\n=== Combined Travel Itinerary ===\n";
        for (const auto& booking : bookings) {
            booking.displayBooking();
        }
    }

    void shareItinerary(const string& email, const vector<Booking>& bookings) {
        cout << "\nSharing the following itinerary to " << email << "\n";
        for (const auto& booking : bookings) {
            booking.displayBooking();
        }
    }
};

void signUp(vector<FrequentTraveler>& travelers, const string& usersFile) {
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

    ofstream file(usersFile, ios::app);
    if (file) {
        file << name << "," << id << "," << email << "," << loyaltyPoints << "\n";
        cout << "Sign-up successful!\n";
    }
    else {
        cout << "Error saving user data.\n";
    }
}

void signIn(const string& usersFile) {
    string name, email, line;
    int id, loyaltyPoints;
    string inputName;

    cout << "Enter your name to sign in: ";
    getline(cin, inputName);

    ifstream file(usersFile);
    if (file) {
        bool found = false;
        while (getline(file, line)) {
            stringstream ss(line);
            getline(ss, name, ',');
            ss >> id;
            ss.ignore();
            getline(ss, email, ',');
            ss >> loyaltyPoints;

            if (name == inputName) {
                found = true;
                cout << "Welcome, " << name << "!\n";
                break;
            }
        }
        if (!found) {
            cout << "User not found. Please sign up first.\n";
        }
    }
    else {
        cout << "Error reading user data.\n";
    }
}

// Main Function
int main() {
    printTitleInRed();

    Admin admin;
    admin.loadBookings();

    vector<FrequentTraveler> travelers;
    TravelAgent travelAgent;
    CustomerModule customerModule;
    BookingManagement bookingManager;
    TravelItineraryManagement itineraryManager;

    const string usersFile = "users.txt";

    while (true) {
        cout << "\n=== Travel Booking System Menu ===\n";
        cout << "1. Sign Up\n2. Sign In\n3. View Profile\n4. Create Booking\n5. View Bookings\n6. Generate Reports\n";
        cout << "7. Plan Multi-Modal Travel\n8. Offer Discounts\n9. View Travel History\n10. Personalized Recommendations\n";
        cout << "11. Modify Booking\n12. Cancel Booking\n13. Combine Itineraries\n14. Share Itinerary\n15. Exit\nChoose an option: ";

        int choice;
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            signUp(travelers, usersFile);
        }
        else if (choice == 2) {
            signIn(usersFile);
        }
        else if (choice == 3) {
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
        else if (choice == 4) {
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
        else if (choice == 5) {
            admin.generateReports();

        }
        else if (choice == 6) {
            admin.saveBookings();

        }
        else if (choice == 7) {
            travelAgent.planMultiModalTravel();

        }
        else if (choice == 8) {
            travelAgent.offerDiscounts(travelers);

        }
        else if (choice == 9) {
            customerModule.viewTravelHistory();

        }
        else if (choice == 10) {
            customerModule.personalizedRecommendations();

        }
        else if (choice == 11) {
            size_t index;
            string newDest, newDate, newTransport;

            cout << "Enter booking index to modify: ";
            cin >> index;
            cin.ignore();

            cout << "Enter new destination: ";
            getline(cin, newDest);
            cout << "Enter new date (YYYY-MM-DD): ";
            getline(cin, newDate);
            cout << "Enter new transport type (Flight/Train/Bus): ";
            getline(cin, newTransport);

            if (index - 1 < admin.bookings.size()) {
                bookingManager.modifyBooking(admin.bookings[index - 1], newDest, newDate, newTransport);
            }
            else {
                cout << "Invalid booking index!\n";
            }

        }
        else if (choice == 12) {
            size_t index;
            cout << "Enter booking index to cancel: ";
            cin >> index;
            cin.ignore();
            bookingManager.cancelBooking(admin.bookings, index - 1);

        }
        else if (choice == 13) {
            itineraryManager.combineBookings(admin.bookings);

        }
        else if (choice == 14) {
            string email;
            cout << "Enter email to share itinerary: ";
            getline(cin, email);
            itineraryManager.shareItinerary(email, admin.bookings);

        }
        else if (choice == 15) {
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
