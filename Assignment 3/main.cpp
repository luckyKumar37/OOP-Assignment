#include <iostream>
#include <stdexcept>
#include <fstream>
using namespace std;

class User {
private:
    string name;
    int age;
    int userID;
    string phoneNumber;
    string UserType;
    bool ispaymentDone = false;

public:
    User(string n, int a, int id, string pn,string t) : name(n), age(a), userID(id), phoneNumber(pn) , UserType(t) {}

    virtual void displayInfo() {
        cout << "User Name: " << name << endl;
        cout<< "User Type: "  << UserType << endl;
        cout << "Age: " << age << endl;
        cout << "User ID: " << userID << endl;
        cout << "Phone Number: " << phoneNumber << endl;
    }

    void makePayment() {
        ispaymentDone = true;
        cout << "Payment done successfully!" << endl;
    }

    bool isPaymentDone() {
        return ispaymentDone;
    }

    int getUserID() {
        return userID;
    }

    string getName() {
        return name;
    }

    string getPhoneNumber() {
        return phoneNumber;
    }

    int getAge() {
        return age;
    }

    string getUserType() {
        return UserType;
    }
};
class Driver
{
private:
    string name;
    int age;
    string licenseNumber;

public:
    Driver(string n, int a, string ln) : name(n), age(a), licenseNumber(ln) {}

    void displayInfo()
    {
        cout << "Driver Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "License Number: " << licenseNumber << endl;
    }
};

class Route
{
private:
    string startPoint;
    string endPoint;
    int distance;

public:
    Route(string sp, string ep, int d) : startPoint(sp), endPoint(ep), distance(d) {}

    void displayRoute()
    {
        cout << "Start Point: " << startPoint << endl;
        cout << "End Point: " << endPoint << endl;
        cout << "Distance: " << distance << " km" << endl;
    }
};

class Vehicle
{
protected:
    int fare;
    bool isAirConditioned;
    Driver driver;
    Route route;
    User **user;

public:
    Vehicle(int f, bool ac, Driver d, Route r) : fare(f), isAirConditioned(ac), driver(d), route(r) {}

    void displayDetails()
    {
        cout << "Fare: " << fare << endl;
        cout << "Air Conditioned: " << (isAirConditioned ? "Yes" : "No") << endl;
        driver.displayInfo();
        route.displayRoute();
    }
};

class Booking
{
private:
    User *user;
    Vehicle *vehicle;
    int seatNumber;

public:
    Booking(User *u, Vehicle *v, int seat) : user(u), vehicle(v), seatNumber(seat)
    {
        if (!u->isPaymentDone())
        {
            throw runtime_error("Payment not completed. Booking cannot be made.");
        }
    }

    void displayBooking()
    {
        cout << "Booking Details:" << endl;
        user->displayInfo();
        vehicle->displayDetails();
        cout << "Seat Number: " << seatNumber << endl;
    }

    User *getUser()
    {
        return user;
    }

    int getSeatNumber()
    {
        return seatNumber;
    }
};

class Point : public Vehicle
{
private:
    Booking *bookings[52];

public:
    Point(int f, bool ac, Driver d, Route r) : Vehicle(f, ac, d, r)
    {
        user = new User *[52];
        for (int i = 0; i < 52; i++)
        {
            user[i] = nullptr;
            bookings[i] = nullptr;
        }
        if(ac)
        {
            fare += 2000; 
        }
    }

    ~Point()
    {
        for (int i = 0; i < 52; i++)
        {
            delete user[i];
            delete bookings[i];
        }
        delete[] user;
    }

    void addUser(User *u)
    {
        if (u->isPaymentDone())
        {
            for (int i = 0; i < 52; i++)
            {
                if (user[i] == nullptr)
                {
                    user[i] = u;
                    cout << "User added successfully to Point!" << endl;
                    return;
                }
            }
            cout << "No more users can be added to the Point!" << endl;
        }
        else
        {
            cout << "Payment not done!" << endl;
        }
    }

    void bookSeat(User *u, int seatNumber)
    {
        if (seatNumber < 1 || seatNumber > 52)
        {
            throw out_of_range("Invalid seat number.");
        }
        if (user[seatNumber - 1] != nullptr)
        {
            throw runtime_error("Seat already booked.");
        }
        if (!u->isPaymentDone())
        {
            throw runtime_error("Payment not completed. Cannot book seat.");
        }

        user[seatNumber - 1] = u;
        bookings[seatNumber - 1] = new Booking(u, this, seatNumber);
        cout << "Seat booked successfully for User ID: " << u->getUserID() << endl;
    }

    void displayBookings()
    {
        cout << "All Bookings in Point:" << endl;
        for (int i = 0; i < 52; i++)
        {
            if (bookings[i] != nullptr)
            {
                bookings[i]->displayBooking();
            }
        }
    }

    void saveToFile(const string &filename)
    {
        ofstream file(filename);
        if (!file)
        {
            cerr << "Error opening file for saving!" << endl;
            return;
        }

        for (int i = 0; i < 52; i++)
        {
            if (bookings[i] != nullptr)
            {
                file << bookings[i]->getUser()->getName() << ","
                     << bookings[i]->getUser()->getUserType() << ","
                     << bookings[i]->getUser()->getAge() << ","
                     << bookings[i]->getUser()->getUserID() << ","
                     << bookings[i]->getUser()->getPhoneNumber() << ","
                     << bookings[i]->getSeatNumber() << endl;
            }
        }

        file.close();
        cout << "Bookings saved to file: " << filename << endl;
    }

    void loadFromFile(const string &filename)
    {
        ifstream file(filename);
        if (!file)
        {
            cerr << "Error opening file for loading!" << endl;
            return;
        }

        string name, phoneNumber, userType;
        int age, userID, seatNumber;
        char comma;

        while (file >> name >> comma >> userType >> comma >> age >> comma >> userID >> comma >> phoneNumber >> comma >> seatNumber)
        {
            User *u = new User(name, age, userID, phoneNumber,userType);
            u->makePayment();
            try
            {
                bookSeat(u, seatNumber);
            }
            catch (const exception &e)
            {
                cerr << "Error booking seat from file: " << e.what() << endl;
                delete u;
            }
        }

        file.close();
        cout << "Bookings loaded from file: " << filename << endl;
    }
};

class Coaster : public Vehicle
{
private:
    Booking *bookings[32];

public:
    Coaster(int f, bool ac, Driver d, Route r) : Vehicle(f, ac, d, r)
    {
        user = new User *[32];
        for (int i = 0; i < 32; i++)
        {
            user[i] = nullptr;
            bookings[i] = nullptr;
        }
        if(ac)
        {
            fare += 2000; 
        }
    }

    ~Coaster()
    {
        for (int i = 0; i < 32; i++)
        {
            delete user[i];
            delete bookings[i];
        }
        delete[] user;
    }

    void addUser(User *u)
    {
        if (u->isPaymentDone())
        {
            for (int i = 0; i < 32; i++)
            {
                if (user[i] == nullptr)
                {
                    user[i] = u;
                    cout << "User added successfully to Coaster!" << endl;
                    return;
                }
            }
            cout << "No more users can be added to the Coaster!" << endl;
        }
        else
        {
            cout << "Payment not done!" << endl;
        }
    }

    void bookSeat(User *u, int seatNumber)
    {
        if (seatNumber < 1 || seatNumber > 32)
        {
            throw out_of_range("Invalid seat number.");
        }
        if (user[seatNumber - 1] != nullptr)
        {
            throw runtime_error("Seat already booked.");
        }
        if (!u->isPaymentDone())
        {
            throw runtime_error("Payment not completed. Cannot book seat.");
        }

        user[seatNumber - 1] = u;
        bookings[seatNumber - 1] = new Booking(u, this, seatNumber);
        cout << "Seat booked successfully for User ID: " << u->getUserID() << endl;
    }

    void displayBookings()
    {
        cout << "All Bookings in Coaster:" << endl;
        for (int i = 0; i < 32; i++)
        {
            if (bookings[i] != nullptr)
            {
                bookings[i]->displayBooking();
            }
        }
    }

    void saveToFile(const string &filename)
    {
        ofstream file(filename);
        if (!file)
        {
            cerr << "Error opening file for saving!" << endl;
            return;
        }

        for (int i = 0; i < 32; i++)
        {
            if (bookings[i] != nullptr)
            {
                file << bookings[i]->getUser()->getName() << ","
                     << bookings[i]->getUser()->getUserType() << ","
                     << bookings[i]->getUser()->getAge() << ","
                     << bookings[i]->getUser()->getUserID() << ","
                     << bookings[i]->getUser()->getPhoneNumber() << ","
                     << bookings[i]->getSeatNumber() << endl;
            }
        }

        file.close();
        cout << "Bookings saved to file: " << filename << endl;
    }

    void loadFromFile(const string &filename)
    {
        ifstream file(filename);
        if (!file)
        {
            cerr << "Error opening file for loading!" << endl;
            return;
        }

        string name, phoneNumber, userType;
        int age, userID, seatNumber;
        char comma;

        while (file >> name >> comma >> userType >> comma >> age >> comma >> userID >> comma >> phoneNumber >> comma >> seatNumber)
        {
            User *u = new User(name, age, userID, phoneNumber, userType);
            u->makePayment();
            try
            {
                bookSeat(u, seatNumber);
            }
            catch (const exception &e)
            {
                cerr << "Error booking seat from file: " << e.what() << endl;
                delete u; 
            }
        }

        file.close();
        cout << "Bookings loaded from file: " << filename << endl;
    }
};


int main()
{
    Driver driver1("John Doe", 35, "DL1234567890");
    Route route1("City A", "City B", 100);
    Driver driver2("Jane Smith", 40, "DL9876543210");
    Route route2("City C", "City D", 150);
    Point point(5000, true, driver1, route1);
    Coaster coaster(3000, false, driver2, route2);

    User user1("Alice", 20, 101, "1234567890","Student");
    user1.makePayment();
    point.addUser(&user1);
    point.bookSeat(&user1, 10);

    User user2("Bob", 30, 102, "0987654321","Faculty");
    user2.makePayment();
    coaster.addUser(&user2);
    coaster.bookSeat(&user2, 5);

    point.displayBookings();
    coaster.displayBookings();

    point.saveToFile("point_bookings.txt");
    coaster.saveToFile("coaster_bookings.txt");

    Point newPoint(0, false, driver1, route1);
    newPoint.loadFromFile("point_bookings.txt");

    Coaster newCoaster(0, false, driver1, route1);
    newCoaster.loadFromFile("coaster_bookings.txt");

    return 0;
}
