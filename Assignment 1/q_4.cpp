#include<iostream>
using namespace std;
class Student
{
    private:
        const string studentId;
        string cardId;
        string name;
        string Stop;
        bool isFeePaid;
    public:
        Student(string id,string carId,string n,string stop,bool paid=false):studentId(id),Stop(stop),name(n),cardId(carId),isFeePaid(paid){}


        void payFee(){
            isFeePaid=true;
        }

        string getStop() const{
            return Stop;
        }

        bool checkIsFeepaid() const{
            return isFeePaid;
        }

        string getStudentID() const{
            return studentId;
        }

        void diplayStudent() const{
            cout<<"Student ID:"<<studentId<<endl;
            cout<<"Name:"<<name<<endl;
            cout<<"Card Id:"<<cardId<<endl;
            cout<<"Stop:"<<Stop<<endl;
        }
};

class Stop{
    private:
        string stopName;
        Student **assignedStudent;
        int studentCount;
        int studentCapacity;

    public:
        Stop(string n):stopName(n){
            studentCount=0;
            studentCapacity=1;

            assignedStudent=new Student*[studentCapacity];
        }

        ~Stop(){
            delete[] assignedStudent;
        }
        void ExpandStudent()
        {
            studentCapacity*=2;

            Student **students=new Student*[studentCapacity];

            for(int i=0;i<studentCount;i++){
                students[i]=assignedStudent[i];
            }
            delete[] assignedStudent;
            assignedStudent=students;
        
        }

        void AssignStudent(Student *s)
        {
            if(studentCount==studentCapacity){
                ExpandStudent();
            }
            assignedStudent[studentCount++]=s;
        }

        string getStopName() const{
            return stopName;
        }
};

class Route{
    private:
        string routeId;
        Stop **stops;
        int stopCount;
        int StopCapacity;

    public:
        Route(string id):routeId(id){
            stopCount=0;
            StopCapacity=1;

            stops=new Stop*[StopCapacity];
        }

        ~Route(){
            delete[] stops;
        }

        void expandRoute(){
            StopCapacity*=2;

            Stop **newStops=new Stop*[StopCapacity];
            for(int i=0;i<stopCount;i++){
                newStops[i]=stops[i];
            }
            delete[] stops;

            stops=newStops;
        }
        void addStop(Stop *s){
            if(stopCount==StopCapacity){
                    expandRoute();
            }

            stops[stopCount++]=s;
        }

        Stop** getStops(){
            return stops;
        }

        int getStopCount(){
            return stopCount;
        }
};

class Bus{
    private:
        string busID;
        Route &route;
        Student **assignedStudent;
        int studentCount;
        int studentCapacity;

    public:
        Bus(string id,Route &r):busID(id),route(r){
            studentCount=0;
            studentCapacity=1;

            assignedStudent=new Student*[studentCapacity];
        }

        ~Bus(){
            delete[] assignedStudent;
        }

        void ExpandStudent()
        {
            studentCapacity*=2;

            Student **students=new Student*[studentCapacity];

            for(int i=0;i<studentCount;i++){
                students[i]=assignedStudent[i];
            }
            delete[] assignedStudent;
            assignedStudent=students;
        
        }

        void assignStudentToBus(Student *s){
            for(int i=0;i<route.getStopCount();i++){
                if(route.getStops()[i]->getStopName()==s->getStop()){
                    if(studentCount==studentCapacity){
                        ExpandStudent();
                    }
                    assignedStudent[studentCount++]=s;
                    cout << "Student " << s->getStudentID() << " assigned to Bus " << busID << " at Stop " << s->getStop() << "\n";
                    return;
                }
            }
            cout<<"No matching student found\n";
        }
        void displayStudentAssignedTOBus(){
            for(int i=0;i<studentCount;i++){
                assignedStudent[i]->diplayStudent();
            }
        }
};

int main() {
    Stop *stop1 = new Stop("Stop A");
    Stop *stop2 = new Stop("Stop B");
    Stop *stop3 = new Stop("Stop C");

    Route route1("Route 101");
    route1.addStop(stop1);
    route1.addStop(stop2);
    route1.addStop(stop3);

    Bus bus1("Bus 001", route1);

    Student *student1 = new Student("S1", "C101", "Alice", "Stop A");
    Student *student2 = new Student("S2", "C102", "Bob", "Stop B");
    Student *student3 = new Student("S3", "C103", "Charlie", "Stop C");
    Student *student4 = new Student("S4", "C104", "David", "Stop A");

    stop1->AssignStudent(student1);
    stop2->AssignStudent(student2);
    stop3->AssignStudent(student3);
    stop1->AssignStudent(student4);

    bus1.assignStudentToBus(student1);
    bus1.assignStudentToBus(student2);
    bus1.assignStudentToBus(student3);
    bus1.assignStudentToBus(student4);

    bus1.displayStudentAssignedTOBus();

    delete student1;
    delete student2;
    delete student3;
    delete student4;
    delete stop1;
    delete stop2;
    delete stop3;

    return 0;
}

