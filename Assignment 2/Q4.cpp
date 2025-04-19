#include<iostream>
using namespace std;

long  HashedGenerator(string password)
{
    long  hash = 5381;
    for(int i=0;i<password.length();i++)
    {
        hash = hash*33+password[i];
    }
    return hash;
}

class User
{
protected:
    string name;
    int ID;
    string email;
    long hashedPassword;
    string listOfPermissions[3];

public:
    User(string name, int ID, string email, string password)
    {
        this->name = name;
        this->ID = ID;
        this->email = email;
        this->hashedPassword = HashedGenerator(password);

        for(int i=0;i<3;i++)
        {
            listOfPermissions[i] = "";
        }
    }

    bool Authenticate(string password)
    {
        return HashedGenerator(password) == hashedPassword;
    }

    bool HasPermission(string action)
    {
        for(int i=0;i<3;i++)
        {
            if(listOfPermissions[i] == action)
            {
                return true;
            }
        }
        return false;
    }

    string getName()
    {
        return name;
    }


    virtual void display()
    {
        cout << "Name: " << name << endl;
        cout << "ID: " << ID << endl;
        cout << "Email: " << email << endl;
    }
    
    
};

class Student : public User
{
protected:
    int Assignments[10];

public:
    Student(string name, int ID, string email, string password) : User(name, ID, email, password)
    {
        for(int i=0;i<10;i++)
        {
            Assignments[i] = 0;

            listOfPermissions[0]="submitAssignment";
            listOfPermissions[1]="";
            listOfPermissions[2]="";
        }

    }

    void submitAssignment(int index)
    {
        if(index >= 0 && index < 10)
        {
            Assignments[index] = 1;
            cout << "Assignment " << index << " submitted." << endl;
        }
        else
        {
            cout << "Invalid assignment index." << endl;
        }
    }

    void display() override
    {
        cout << "Student Name: " << name << endl;
        cout << "Student ID: " << ID << endl;
        cout << "student Email: " << email << endl;
        cout << "Assignments: ";
        for(int i=0;i<10;i++)
        {
            cout << Assignments[i] << " ";
        }
    }
};

class TA : public Student
{
private:
    string StudentList[10];
    string project[2];
public: 
    TA(string name, int ID, string email, string password) : Student(name, ID, email, password)
    {
        listOfPermissions[0]="view Projects";
        listOfPermissions[1]="Manage Students";
        listOfPermissions[2]="";
    }

    void addStudent(string studentName)
    {
        for(int i=0;i<10;i++)
        {
            if(StudentList[i] == "")
            {
                StudentList[i] = studentName;
                cout << "Student " << studentName << " added." << endl;
                return;
            }
        }
        cout << "Student list is full." << endl;
    }

    void startproject(string projectName)
    {
        for(int i=0;i<2;i++)
        {
            if(project[i] == "")
            {
                project[i] = projectName;
                cout << "TA " << name << " has started working on project: " << projectName << "\n";
                return;
            }
        }
        cout << "Project list is full." << endl;
    }

    void display() override
    {
        cout << "TA Name: " << name << endl;
        cout << "TA ID: " << ID << endl;
        cout << "TA Email: " << email << endl;
        cout << "Students: ";
        for(int i=0;i<10;i++)
        {
            cout << StudentList[i] << " ";
        }
        cout << "\nProjects: ";
        for(int i=0;i<2;i++)
        {
            cout << project[i] << " ";
        }
    }
};

class professor : public User
{
    public:
    professor(string name, int ID, string email, string password) : User(name, ID, email, password) 
    {
        listOfPermissions[0]="assignProject";
        listOfPermissions[1]="full lab access";
        listOfPermissions[2]="";
    }

    void assignProject(TA &ta, string projectName)
    {
        ta.startproject(projectName);
        cout << "Professor " << name << " has assigned project: " << projectName << " to TA: " << ta.getName() << "\n";
    }

    void display() override
    {
        cout << "Professor Name: " << name << endl;
        cout << "Professor ID: " << ID << endl;
        cout << "Professor Email: " << email << endl;
    }
};

void authenticateAndperformAction(User &user, string password, string action)
{
    if(user.Authenticate(password))
    {
        if(user.HasPermission(action))
        {
            cout << "Authentication successful. Performing action: " << action << endl;
        }
        else
        {
            cout << "Permission denied for action: " << action << endl;
        }
    }
    else
    {
        cout << "Authentication failed." << endl;
    }
}

int main()
{
    Student student("John Doe", 101, "john.doe@example.com", "password123");
    student.submitAssignment(2);
    student.display();
    cout << endl;


    TA ta("Jane Smith", 102, "jane.smith@example.com", "securepass");
    ta.addStudent("Alice");
    ta.addStudent("Bob");
    ta.startproject("AI Research");
    ta.display();
    cout << endl;


    professor prof("Dr. Brown", 103, "dr.brown@example.com", "profpass");
    prof.assignProject(ta, "Machine Learning");
    prof.display();
    cout << endl;

    cout << "Testing authentication and permissions:" << endl;
    authenticateAndperformAction(student, "password123", "submitAssignment");
    authenticateAndperformAction(ta, "securepass", "view Projects");
    authenticateAndperformAction(prof, "profpass", "assignProject");
    authenticateAndperformAction(prof, "wrongpass", "assignProject");

    return 0;
}


