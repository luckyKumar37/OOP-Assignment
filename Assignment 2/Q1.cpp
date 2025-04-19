#include <iostream>
using namespace std;

class Person
{
protected:
    const string id;
    string name;
    string cardId;
    string Stop;
    bool isFeePaid;

public:
    Person(string id, string cardId, string n, string stop, bool paid = false) : id(id), Stop(stop), name(n), cardId(cardId), isFeePaid(paid) {}

    virtual void payFee() = 0; // Pure virtual function

    virtual string getStop() const
    {
        return Stop;
    }

    virtual string checkIsFeepaid() const
    {
        return (isFeePaid ? "Yes" : "No");
    }

    virtual string getID() const
    {
        return id;
    }

    friend void operator<<(ostream &os, const Person &p)
    {
        cout << "ID: " << p.id << ", Name: " << p.name << ", Card ID: " << p.cardId << ", Stop: " << p.Stop << ", Fee Paid: " << (p.isFeePaid ? "Yes" : "No") << endl;
    }
};

class Student : public Person
{

public:
    Student(string id, string cardId, string n, string stop, bool paid = false) : Person(id, cardId, n, stop, paid) {}

    void payFee() override
    {
        isFeePaid = true;
        cout << "Fee paid by student " << name << endl;
    }
};

class Teacher : public Person
{
public:
    Teacher(string id, string carId, string n, string stop, bool paid = false) : Person(id, carId, n, stop, paid) {}

    void payFee() override
    {
        isFeePaid = true;
        cout << "Fee paid by teacher " << name << endl;
    }
};

class Staff : public Person
{
public:
    Staff(string id, string carId, string n, string stop, bool paid = false) : Person(id, carId, n, stop, paid) {}

    void payFee() override
    {
        isFeePaid = true;
        cout << "Fee paid by staff " << name << endl;
    }
};

class Stop
{
private:
    string stopName;
    Person **assignedPerson;
    int PersonCount;
    int PersonCapacity;

public:
    Stop(string n) : stopName(n)
    {
        PersonCount = 0;
        PersonCapacity = 1;

        assignedPerson = new Person *[PersonCapacity];
    }

    ~Stop()
    {
        for (int i = 0; i < PersonCount; i++)
        {
            delete assignedPerson[i];
        }
        delete[] assignedPerson;
    }
    void ExpandPerson()
    {
        PersonCapacity *= 2;

        Person **Persons = new Person *[PersonCapacity];

        for (int i = 0; i < PersonCount; i++)
        {
            Persons[i] = assignedPerson[i];
        }
        delete[] assignedPerson;
        assignedPerson = Persons;
    }

    void AssignPerson(Person *p)
    {
        if (PersonCount == PersonCapacity)
        {
            ExpandPerson();
        }
        assignedPerson[PersonCount++] = p;
    }

    string getStopName() const
    {
        return stopName;
    }
};

class Route
{
private:
    string routeId;
    Stop **stops;
    int stopCount;
    int StopCapacity;

public:
    Route(string id) : routeId(id)
    {
        stopCount = 0;
        StopCapacity = 1;

        stops = new Stop *[StopCapacity];
    }

    ~Route()
    {
        for (int i = 0; i < stopCount; i++)
        {
            delete stops[i];
        }
        delete[] stops;
    }

    void expandRoute()
    {
        StopCapacity *= 2;

        Stop **newStops = new Stop *[StopCapacity];
        for (int i = 0; i < stopCount; i++)
        {
            newStops[i] = stops[i];
        }
        delete[] stops;

        stops = newStops;
    }
    void addStop(Stop *s)
    {
        if (stopCount == StopCapacity)
        {
            expandRoute();
        }

        stops[stopCount++] = s;
    }

    Stop **getStops()
    {
        return stops;
    }

    int getStopCount()
    {
        return stopCount;
    }

    bool operator==(const Route &other) const
    {
        return routeId == other.routeId;
    }
};

class Bus
{
private:
    string busID;
    Route &route;
    Person **assignedPerson;
    int PersonCount;
    int PersonCapacity;

public:
    Bus(string id, Route &r) : busID(id), route(r)
    {
        PersonCount = 0;
        PersonCapacity = 1;

        assignedPerson = new Person *[PersonCapacity];
    }

    ~Bus()
    {
        for (int i = 0; i < PersonCount; i++)
        {
            delete assignedPerson[i];
        }
        delete[] assignedPerson;
    }

    void ExpandPerson()
    {
        PersonCapacity *= 2;

        Person **Persons = new Person *[PersonCapacity];

        for (int i = 0; i < PersonCount; i++)
        {
            Persons[i] = assignedPerson[i];
        }
        delete[] assignedPerson;
        assignedPerson = Persons;
    }

    void assignPersonToBus(Person *p)
    {
        for (int i = 0; i < route.getStopCount(); i++)
        {
            if (route.getStops()[i]->getStopName() == p->getStop())
            {
                if (PersonCount == PersonCapacity)
                {
                    ExpandPerson();
                }
                assignedPerson[PersonCount++] = p;
                cout << "Person " << p->getID() << " assigned to Bus " << busID << " at Stop " << p->getStop() << "\n";
                return;
            }
        }
        cout << "No matching student found\n";
    }
    void displayPersonAssignedTOBus()
    {
        for (int i = 0; i < PersonCount; i++)
        {
            cout << *assignedPerson[i];
        }
    }

    bool operator==(const Bus &other) const
    {
        return busID == other.busID;
    }
};

int main()
{
    Stop *stop1 = new Stop("Stop A");
    Stop *stop2 = new Stop("Stop B");
    Stop *stop3 = new Stop("Stop C");

    Route route1("Route 101");
    route1.addStop(stop1);
    route1.addStop(stop2);
    route1.addStop(stop3);

    Bus bus1("Bus 001", route1);

    Student *student1 = new Student("S1", "C101", "Alice", "Stop A");
    Teacher *teacher1 = new Teacher("T1", "C201", "Mr. Smith", "Stop B");
    Staff *staff1 = new Staff("ST1", "C301", "John Doe", "Stop C");

    stop1->AssignPerson(student1);
    stop2->AssignPerson(teacher1);
    stop3->AssignPerson(staff1);

    bus1.assignPersonToBus(student1);
    bus1.assignPersonToBus(teacher1);
    bus1.assignPersonToBus(staff1);

    cout << "\n--- Persons Assigned to Bus ---\n";
    bus1.displayPersonAssignedTOBus();

    cout << "\n--- Fee Payment ---\n";
    student1->payFee();
    teacher1->payFee();
    staff1->payFee();

    cout << "\n--- Person Details ---\n";
    cout << *student1;
    cout << *teacher1;
    cout << *staff1;

    Stop *stop4 = new Stop("Stop D");
    Stop *stop5 = new Stop("Stop E");

    Route route2("Route 102");
    route2.addStop(stop4);
    route2.addStop(stop5);

    Bus bus2("Bus 002", route2);

    if (route1 == route2)
    {
        cout << "\nRoute 1 and Route 2 are the same.\n";
    }
    else
    {
        cout << "\nRoute 1 and Route 2 are different.\n";
    }

    if (bus1 == bus2)
    {
        cout << "Bus 1 and Bus 2 are the same.\n";
    }
    else
    {
        cout << "Bus 1 and Bus 2 are different.\n";
    }

    delete stop1;
    delete stop2;
    delete stop3;
    delete stop4;
    delete stop5;

    return 0;
}