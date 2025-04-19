#include<iostream>
using namespace std;

class Vehicle
{
    private:
        string Brand;
        string Model;
        float rentalprice;
        string reqLicence;

        public:
            Vehicle():Brand("Unknown Brand"),Model("Unknown Model"),rentalprice(0.0),reqLicence("not provided"){}


            Vehicle(string b,string m,float price,string req):Brand(b),Model(m),rentalprice(price),reqLicence(req){}

            bool isEligible(string userLicence){
                if(userLicence=="Full") return true;
                if(userLicence=="Intermediate" && reqLicence!="Full") return true;
                if(userLicence=="Learner" && reqLicence=="Learner") return true;
                return false;
            }

            string getModel(){
                return Model;
            }

            float getRentalPrice(){
                return rentalprice;
            }

            void DisplayVehicle(){
                cout<<"Brand: "<<Brand<<endl;
                cout<<"Model: "<<Model<<endl;
                cout<<"Rental price for a day: "<<rentalprice<<"$"<<endl;
                cout<<"required licence: "<<reqLicence<<endl;
            }
};

class User
{
    private:
        int UserID;
        string Name;
        int age;
        string contactNumber;
        string LicenseType;

        public:
            User():UserID(0),Name("unknown"),contactNumber("Not provided"),LicenseType("not given"){}

            User(int id,string n,int a,string number,string licence):UserID(id),Name(n),age(a),contactNumber(number),LicenseType(licence){}

            void UpdateLicenceType(string l)
            {
                LicenseType=l;
            }
            void updateName(string n)
            {
                Name=n;
            }
            
            void updateAge(int a)
            {
                age=a;
            }

            void updateContactNumber(string number)
            {
                contactNumber=number;
            }

            int getUserId(){
                return UserID;
            }

            string getLicenceType(){
                return LicenseType;
            }

            string getName(){
                return Name;
            }

            void Displayuser(){
                cout<<"User Id:  "<<UserID<<endl;
                cout<<"Name: "<<Name<<endl;
                cout<<"Age: "<<age<<endl;
                cout<<"Contact no: "<<contactNumber<<endl;
                cout<<"Licence type: "<<LicenseType<<endl;
            }
};

class RentalSystem
{
    private:
        User **users;
        Vehicle **vehicles;
        int userCount;
        int vehicleCount;
        int userCapacity;
        int vehicleCapacity;

    public:
        RentalSystem()
        {
            userCount=0;
            vehicleCount=0;
            userCapacity=1;
            userCapacity=1;

            users=new User*[userCapacity];
            vehicles=new Vehicle*[vehicleCapacity];
        }

        void Expenduser()
        {
            userCapacity*=2;
            User **newusers=new User*[userCapacity];

            for(int i=0;i<userCount;i++){
                newusers[i]=users[i];
            }
            delete[] users;
            users=newusers;
        }

        void Expandvehicle()
        {
            vehicleCapacity*=2;
            Vehicle **newvehicles=new Vehicle*[vehicleCapacity];

            for(int i=0;i<vehicleCount;i++){
                newvehicles[i]=vehicles[i];
            }

            delete[] vehicles;
            vehicles=newvehicles;
        }

        void registeruser(int id,string n,int a,string number,string licence)
        {
            if(userCount==userCapacity)
            {
                Expenduser();
            }

            users[userCount++]= new User(id,n,a,number,licence);
            cout<<"User registered successfully\n";
        }

        void addVehicle(string b,string m,float price,string req)
        {
            if(vehicleCount==vehicleCapacity)
            {
                Expandvehicle();
            }

            vehicles[vehicleCount++]=new Vehicle(b,m,price,req);
            cout<<"Vehicle added successfully\n";
        }

        void rentVehicle(int userId,string vehiclemodel)
        {
            User *user=nullptr;
            Vehicle *selectedVehicle=nullptr;

            for(int i=0;i<userCount;i++){
                if(users[i]->getUserId()==userId){
                    user=users[i];
                    break;
                }
            }

            if(!user){
                cout<<"User not found!\n";
                return;
            }

            for(int i=0;i<vehicleCount;i++){
                if(vehicles[i]->getModel()==vehiclemodel){
                    selectedVehicle=vehicles[i];
                    break;
                }
            }
            if(!selectedVehicle){
                cout<<"Vehicle not found!\n";
                return;
            }

            if(selectedVehicle->isEligible(user->getLicenceType())){
                cout << "Rental Successful! " << user->getName() << " rented " << selectedVehicle->getModel() 
                << " for $" << selectedVehicle->getRentalPrice() << " per day.\n";
            }else{
                 cout << "Rental Failed! You are not eligible to rent this vehicle.\n";
            }
        } 
        
        ~RentalSystem(){
            for(int i=0;i<userCount;i++){
                delete users[i];
            }
            for(int i=0;i<vehicleCount;i++){
                delete vehicles[i];
            }
            delete[] users;
            delete[] vehicles;
        }
        void DIsplayusers(){
            for(int i=0;i<userCount;i++){
                cout<<"User "<<i+1<<":"<<endl;
                users[i]->Displayuser();
            }
        }

        void Displayvehicles(){
            for(int i=0;i<vehicleCount;i++){
                cout<<"Vehicle "<<i+1<<":"<<endl;
                vehicles[i]->DisplayVehicle();
            }
        }
        
};

int main() {
    RentalSystem rentalSystem;

    rentalSystem.registeruser(1, "Alice", 25, "123-456", "Full");
    rentalSystem.registeruser(2, "Bob", 18, "789-101", "Learner");
    rentalSystem.registeruser(3, "Charlie", 21, "555-888", "Intermediate");
    rentalSystem.DIsplayusers();


    rentalSystem.addVehicle("Toyota", "Camry", 50.0, "Full");
    rentalSystem.addVehicle("Honda", "Civic", 45.0, "Intermediate");
    rentalSystem.addVehicle("Yamaha", "Scooter", 20.0, "Learner");
    rentalSystem.Displayvehicles();



    rentalSystem.rentVehicle(1, "Camry");       
    rentalSystem.rentVehicle(2, "Camry");       
    rentalSystem.rentVehicle(3, "Civic");       
    rentalSystem.rentVehicle(2, "Scooter");     
    rentalSystem.rentVehicle(3, "Camry");       
    
    return 0;
}
