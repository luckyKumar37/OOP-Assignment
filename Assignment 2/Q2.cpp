#include"iostream"
using namespace std;

class HauntedHouse;
class Visitor;
class Ghost
{
protected:
    string playerName;
    int scareLevel;

public:
    Ghost(string name, int level) : playerName(name), scareLevel(level) {}

    virtual void  haunt()
    {
        cout << "Boo! I'm haunting you!" << endl;
    }

    friend void operator<<(ostream& os, const Ghost& g)
    {
        cout << "Ghost Name: " << g.playerName << endl;
        cout << "Scare Level: " << g.scareLevel << endl;
    }

    int getScareLevel() const
    { 
        return scareLevel;
    }

    string getPlayerName() const
    {
        return playerName;
    }
    
    Ghost  operator+(const Ghost& g)
    {
        return Ghost(playerName + " & " + g.playerName, scareLevel + g.scareLevel);
    } 

    friend void visit(HauntedHouse& h, Visitor v[],int noOfvisitors);

};

class poltergeist : virtual public Ghost
{
public:
    poltergeist(string name, int level) : Ghost(name, level) {}

    void haunt() override
    {
        cout << "I'm a poltergeist! I'm moving objects!" << endl;
    }

};
class banshees :virtual public Ghost
{
public:
    banshees(string name, int level) : Ghost(name, level) {}

    void haunt() override
    {
        cout << "I'm a banshee! I'm screaming!" << endl;
    }
};

class Shadowghost :virtual public Ghost
{
public:
    Shadowghost(string name, int level) : Ghost(name, level) {}

    void haunt() override
    {
        cout << "I'm a shadow ghost! I'm lurking in the shadows and whispering!" << endl;
    }
};

class Shadowpoltergeist : public poltergeist ,public Shadowghost    
{
public:
    Shadowpoltergeist(string name, int level) : Ghost(name, level), poltergeist(name, level), Shadowghost(name, level) {}

    void haunt() override
    {
        cout << "I'm a shadow poltergeist! I'm moving objects in the shadows!" << endl;
    }
};

class Visitor
{
public:
    string name;
    int braveryLevel;
    Visitor(string n, int b) : name(n), braveryLevel(b) {}

    void laugh()
    {
        cout << name << " is laughing!" << endl;
    }
    void scream()
    {
        cout << name << " is screaming!" << endl;
    }
    void run()
    {
        cout << name << " is running away!" << endl;
    }
    void shakyvoice()
    {
        cout << name << " has a shaky voice!" << endl;
    }

};

class HauntedHouse
{
private:
    string name;
    Ghost** ghost;
    int ghostCount = 0;

public:
    HauntedHouse(string n) : name(n) {
        ghost = new Ghost*[3]; 
        for (int i = 0; i < 3; ++i)
        {
            ghost[i] = nullptr;
        }
    }

    void addGhost(Ghost* g)
    {
        if(ghostCount<3)
        {
            ghost[ghostCount++] = g;
        }
        else
        {
            cout<<"ghost limit reached\n";
        }
        
    }

    friend void operator<<(ostream& os, const HauntedHouse& h)
    {
        cout << "Haunted House: " << h.name << endl;
        for (int i = 0; i < h.ghostCount; ++i)
        {
            cout << *(h.ghost[i]);
        }
    }

    friend void visit(HauntedHouse& h, Visitor v[],int noOfvisitors);

    ~HauntedHouse()
    {
        for (int i = 0; i < ghostCount; ++i)
        {
            delete ghost[i];
        }
        delete[] ghost;
    }

};

void visit(HauntedHouse& h, Visitor v[],int noOfvisitors)
{
    cout<<"In the haunted house: "<<h.name<<endl;
    cout<<"Visitors: "<<endl;
    for(int i=0;i<noOfvisitors;i++)
    {
        cout<<v[i].name<<endl;
    }
    cout<<"Have Entered\n";

    for(int i=0;i<noOfvisitors;i++)
    {
        int index = rand() % h.ghostCount;
        cout<<v[i].name<<" is being haunted by "<<h.ghost[index]->getPlayerName()<<endl;
        cout<<v[i].name<<" has bravery level "<<v[i].braveryLevel<<endl;
        cout<<h.ghost[index]->getPlayerName()<<" has scare level "<<h.ghost[index]->getScareLevel()<<endl;

        if(v[i].braveryLevel>=1 && v[i].braveryLevel<=4) // Cowardly
        {
            if(h.ghost[index]->getScareLevel()>v[i].braveryLevel)
            {
                v[i].scream();
                v[i].run();
            }else if(h.ghost[index]->getScareLevel()>=1 && h.ghost[index]->getScareLevel()<=4)
            {
                v[i].shakyvoice();
            }else{
                v[i].laugh();
            }
        }
        else if(v[i].braveryLevel>=5 && v[i].braveryLevel<=7)// Averge
        {
            if(h.ghost[index]->getScareLevel()>v[i].braveryLevel)
            {
                v[i].scream();
                v[i].run();
            }else if(h.ghost[index]->getScareLevel()>=5 && h.ghost[index]->getScareLevel()<=7)
            {
                v[i].shakyvoice();
            }else{
                v[i].laugh();
            }
        }
        else if(v[i].braveryLevel>=8 && v[i].braveryLevel<=10)// Fearless
        {
            if(h.ghost[index]->getScareLevel()>v[i].braveryLevel)
            {
                v[i].scream();
                v[i].run();
            }else if(h.ghost[index]->getScareLevel()>=8 && h.ghost[index]->getScareLevel()<=10)
            {
                v[i].shakyvoice();
            }else{
                v[i].laugh();
            }
        }
    }
}

int main()
{

    HauntedHouse house1("Spooky Mansion");
    HauntedHouse house2("Creepy Castle");

    house1.addGhost(new poltergeist("Polty", 3));
    house1.addGhost(new banshees("Banshee Bella", 6));
    house1.addGhost(new Shadowghost("Shadow Steve", 8));

    house2.addGhost(new Shadowpoltergeist("Shadow Polty", 7));
    house2.addGhost(new banshees("Screaming Sally", 5));
    house2.addGhost(new poltergeist("Object Mover", 4));

    Visitor visitors[] = {
        Visitor("Alice", 2),  // Cowardly
        Visitor("Bob", 6),    // Average
        Visitor("Charlie", 9) // Fearless
    };

    // Visit to the haunted houses
    cout << "Visiting " << endl;
    visit(house1, visitors, 3);
    cout << endl;
    visit(house2, visitors, 3);

    return 0;
}
