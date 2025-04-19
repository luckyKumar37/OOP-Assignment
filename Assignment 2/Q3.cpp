#include <iostream>
using namespace std;

class Vehicle
{
protected:
    int VehicleID;
    int speed;
    int capacity;
    int energyEfficiency;
    static int totalDeliveries;

public:
    Vehicle(int id, int spd, int cap, int eff) : VehicleID(id), speed(spd), capacity(cap), energyEfficiency(eff)
    {
        totalDeliveries++;
    }

    ~Vehicle()
    {
        totalDeliveries--;
    }

    virtual void CalculateOptimalRoute()
    {
        cout << "calculating optimal route for vehicle " << VehicleID << endl;
    }

    virtual void EstimatedDeliveryTime(double distance)
    {
        double time = distance / speed;

        cout << "Estimated delivery time for vehicle with ID " << VehicleID << " is " << time << " hours" << endl;
    }

    virtual void Command(string action, string packageId)
    {
        cout << "Vehicle with ID " << VehicleID << " executing command: " << action << " for package " << packageId << endl;
    }

    virtual void Command(string action, string packageId, string urgency)
    {
        cout << "Vehicle with ID " << VehicleID << " executing command: " << action << " for package " << packageId << " with urgency: " << urgency << endl;
    }

    friend bool operator==(const Vehicle &v1, const Vehicle &v2);

    virtual void Move() = 0; // it is a pure virtual function
};

int Vehicle::totalDeliveries = 0;

class RamzanDrone : public Vehicle
{
public:
    RamzanDrone(int id, int spd, int cap, int eff) : Vehicle(id, spd, cap, eff) {}

    void CalculateOptimalRoute() override
    {
        cout << "Calculating aerial route for Drone ID: " << VehicleID << endl;
    }

    void Move() override
    {
        cout << "Drone ID " << VehicleID << " is flying at speed " << speed << " km/h." << endl;
    }

    void Command(string action, string packageId, string urgency) override
    {
        if (urgency == "Urgent")
        {
            speed = 100;
            cout << "Drone ID " << VehicleID << " is flying at speed " << speed << " km/h for urgent  iftar delivery of package " << packageId << endl;
        }
        else
        {
            cout << "Drone ID " << VehicleID << " executing command: " << action << " for package " << packageId << " with urgency: " << urgency << endl;
        }
    }
};

class RamzamTimeShip : public Vehicle
{
public:
    RamzamTimeShip(int id, int spd, int cap, int eff) : Vehicle(id, spd, cap, eff) {}

    void CalculateOptimalRoute() override
    {
        cout << "Calculating time-travel route for TimeShip ID: " << VehicleID << endl;
    }

    void Move() override
    {
        cout << "TimeShip ID " << VehicleID << " is verifying historical consistency before proceeding. "<< endl;
    }

    void Command(string action, string packageId, string urgency) override
    {
        if (urgency == "Urgent")
        {
            cout << "TimeShip ID " << VehicleID << " validating historical accuracy for package " << packageId << endl;
        }
        else
        {
            cout << "TimeShip ID " << VehicleID << " is delivering package " << packageId<< endl;
        }
    }
};

class RamzanHyperPod : public Vehicle
{
public:
    RamzanHyperPod(int id, int spd, int cap, int eff) : Vehicle(id, spd, cap, eff) {}

    void CalculateOptimalRoute() override
    {
        cout << "Calculating underground route for HyperPod ID: " << VehicleID << endl;
    }

    void Move() override
    {
        cout << "HyperPod ID " << VehicleID << " is moving at speed " << speed << " km/h and is navigates an underground tunnel network for efficient bulk delivery." << endl;
    }
};

bool operator==(const Vehicle &v1, const Vehicle &v2)
{
    return (v1.speed == v2.speed && v1.capacity == v2.capacity && v1.energyEfficiency == v2.energyEfficiency);
}

int main()
{
    RamzanDrone drone1(1, 60, 5, 10);
    RamzamTimeShip timeShip1(2, 80, 10, 15);
    RamzanHyperPod hyperPod1(3, 100, 20, 20);

    drone1.CalculateOptimalRoute();
    timeShip1.CalculateOptimalRoute();
    hyperPod1.CalculateOptimalRoute();

    drone1.EstimatedDeliveryTime(120);
    timeShip1.EstimatedDeliveryTime(200);
    hyperPod1.EstimatedDeliveryTime(300);

    drone1.Move();
    timeShip1.Move();
    hyperPod1.Move();

    drone1.Command("Deliver", "PKG001", "Urgent");
    timeShip1.Command("Deliver", "PKG002", "Normal");
    hyperPod1.Command("Deliver", "PKG003", "Urgent");

    return 0;
}