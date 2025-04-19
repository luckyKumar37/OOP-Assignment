#include<iostream>
using namespace std;

class Skill{
    private:
        int skillID;
        string name;
        string description;
    
    public:
        Skill(){
            skillID=0;
            name="Unknown Skill";
            description="none";
        }
        Skill(int id,string n,string des){
            skillID=id;
            name=n;
            description=des;
        }

        int getSkillId(){
            return skillID;
        }

        void SkillDetails(){
            cout<<"Skill Details\n";
            cout<<"Skill ID: "<<skillID<<endl;
            cout<<"Name: "<<name<<endl;
            cout<<"Description: "<<description<<endl;
        }

        void updateSkillDescription(string s){
            description=s;
        }
};
class Sports{
    private:
        int sportID;
        string name;
        string description;
        Skill requiredSkills[2];
        int noOfSkills=0;

    public:
        Sports(){
            sportID=0;
            name="unknown sports";
            description="none";
        }

        Sports(int id,string n,string d){
            sportID=id;
            name=n;
            description=d;
        }

        void addSkill(Skill s){
            if(noOfSkills<2){
                requiredSkills[noOfSkills++]=s;
            }else{
                cout<<"Max number of required skills already achieved!\n";
            }
        }

        void removeSkill(Skill s){
            bool found=0;
            for(int i=0;i<noOfSkills;i++){
                if(requiredSkills[i].getSkillId()==s.getSkillId()){
                    found=true;
                    for(int j=i;j<noOfSkills-1;j++){
                        requiredSkills[j]=requiredSkills[j+1];
                    }
                    cout<<"Skill was removed\n";
                    noOfSkills--;
                    break;
                }
            }
            if(!found){
                cout<<"This Skill is not present here\n";
            }
        }

        void Details(){
            cout<<"Sports Details\n";
            cout<<"Sports ID: "<<sportID<<endl;
            cout<<"Sports Name: "<<name<<endl;
            cout<<"Sports Description: "<<description<<endl;
        }

};
class Mentor;
class Student{
    private:
        int studentID;
        string name;
        int age;
        Sports sportsinterest[2];
        Mentor *mentorAssigned;
        int noOfsports=0;

    public:
        Student(){
            studentID=0;
            name="Unknown Student";
            mentorAssigned=nullptr;

        }

        Student(int id,string n,int a){
            studentID=id;
            name=n;
            age=a;
            mentorAssigned=nullptr;
        }

        void updateInterest(Sports s){
            if(noOfsports<2){
                sportsinterest[noOfsports++]=s;
            }else{
                cout<<"Maximum number of sports have been added already!\n";
            }
        }


        void viewSports(){
            cout<<"Sports interests\n";
            for(int i=0;i<noOfsports;i++){
                sportsinterest[i].Details();
            }
        }

        void registerForMentor(Mentor &m);


        int getStudentid(){
            return studentID;
        }



        void veiwMentorDetails();

        void details(){
            cout<<"Learner Details\n";
            cout<<"Learner ID: "<<studentID<<endl;
            cout<<"Learner Name: "<<name<<endl;
            cout<<"Learner Age: "<<age<<endl;
            viewSports();
        }


};

class Mentor{
    private:
        int mentorID;
        string name;
        Sports sportsExpertise[2];
        int maxleaner;
        Student *assignedLearners;
        int noOfLearner=0;
        int noOfsports=0;
    
        public:
            Mentor(){
                mentorID=0;
                name="Unknown Mentor";
                maxleaner=3;
                assignedLearners=new Student[maxleaner];
            }

            Mentor(int id,string n,int max){
                mentorID=id;
                name=n;
                maxleaner=max;
                assignedLearners=new Student[max];
            }

            void assignLearner(Student &s){
                if(noOfLearner<maxleaner){
                    assignedLearners[noOfLearner++]=s;
                }else{
                    cout<<"Maximum number of learners are already assigned\n";
                }
            }
            void removeLearner(Student s){
                bool found=false;
                for(int i=0;i<noOfLearner;i++){
                    if(assignedLearners[i].getStudentid()==s.getStudentid()){
                        found=true;
                        for(int j=i;j<noOfLearner-1;j++){
                            assignedLearners[j]=assignedLearners[j+1];
                        }
                        cout<<"Learner has been removed\n";
                        noOfLearner--;
                        break;
                    }
                }
                if(!found){
                    cout<<"This Learner is not assigned here\n";
                }
            }

            void Details(){
                cout<<"Mentor's Details\n";
                cout<<"Mentor ID: "<<mentorID<<endl;
                cout<<"Mentor's Name: "<<name<<endl;
            }

            void Viewlearners(){
                cout<<"Mentor's Name: "<<name<<endl;
                cout<<"Learners:\n";
                for(int i=0;i<noOfLearner;i++){
                    assignedLearners[i].details();
                }
            }

            void addsportExpertise(Sports s){
                if(noOfsports<2){
                    sportsExpertise[noOfsports++]=s;
                }else{
                    cout<<"maximum number of sports Expertise has been added\n";
                }
            }

            ~Mentor() { 
                delete[] assignedLearners;
            }

};

void Student::registerForMentor(Mentor &m){
    mentorAssigned=&m;
    m.assignLearner(*this);
}

void Student::veiwMentorDetails(){
        if(mentorAssigned){
            mentorAssigned->Details();
        }else{
            cout<<"No mentor assigned yet!\n";
        }
        
}


int main() {
    Skill skill1(1, "Dribbling", "Ability to control the ball while running.");
    Skill skill2(2, "Shooting", "Ability to shoot the ball accurately.");
    
    Sports basketball(101, "Basketball", "A team sport played with a ball and hoop.");
    basketball.addSkill(skill1);
    basketball.addSkill(skill2);
    
    cout << "=== Basketball Details ===" << endl;
    basketball.Details();
    
    Student student1(201, "Alice", 18);
    Student student2(202, "Bob", 20);
    
    student1.updateInterest(basketball);
    student2.updateInterest(basketball);
    
    cout << "\n=== Student Details ===" << endl;
    student1.details();
    student2.details();

    Mentor mentor1(301, "Coach Carter", 3);
    
    student1.registerForMentor(mentor1);
    student2.registerForMentor(mentor1);
    
    cout << "\n=== Mentor Details ===" << endl;
    mentor1.Details();
    mentor1.Viewlearners();

    cout << "\nRemoving Student Bob from Mentor..." << endl;
    mentor1.removeLearner(student2);
    mentor1.Viewlearners();

    return 0;
}