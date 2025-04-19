#include<iostream>
#include<tuple>
using namespace std;


class Robot
{
    private:
        string name;
        int hits;

    public:

    Robot()
    {
        name="unknown";
        hits=0;
    }

    Robot(string n):name(n),hits(0){}

    void hitBall(int &ballX,int &ballY,const string &direction)
    {
        if(direction=="up")
        {
            ballY++;
        }else if(direction=="down"){
            ballY--;
        }else if(direction=="right"){
            ballX++;
        }else if(direction=="left"){
            ballX--;
        }
        hits++;
    }

    int getHits(){
        return hits;
    }
    
};

class Ball
{
    private:
        int x;
        int y;

    public:
        Ball()
        {
            x=0;
            y=0;
        }

        Ball(int a,int b){
            x=a;
            y=b;
        }

        int  getX()
        {
            return x;
        }

        int getY()
        {
            return y;
        }

        void Move(int dx,int dy)
        {
            x+=dx;
            y+=dy;
        }

        tuple<int ,int> getPosition()
        {
            return make_tuple(x,y);
        }
};

class Goal
{
    private:
        int x;
        int y;

    public:
        Goal()
        {
            x=3;
            y=3;
        }

        bool isGoalReached(int ballX,int ballY){
            if(ballX==x && ballY==y)
            {
                return true;
            }else
            {
                return false;
            }
        }
};

class Team
{
    private:
        string teamName;
        Robot *r1;

    public:
        Team(string n,Robot *r):teamName(n),r1(r){}


        Robot* getRobot()
        {
            return r1;
        }

        string getTeamName(){
            return teamName;
        }


};

class Game
{
    private:
        Team* team1;
        Team* team2;
        Ball ball;
        Goal goal;

    public:
        Game(Team *t1,Team *t2):team1(t1),team2(t2){}

        void resetball(){
            ball=Ball(0,0);
        }

        void Play(Team *t1)
        {
            Robot* robot=t1->getRobot();

            cout<<"Team "<<t1->getTeamName()<<" will play now!\n";

            while(!goal.isGoalReached(ball.getX(),ball.getY())){
                string dir;
                cout<<"Enter the direction you want to hit ball(up/down/right/left):";
                cin>>dir;
                if(dir=="up" || dir=="down" || dir=="right" || dir=="left"){
                
                }else{
                    cout<<"Invalid direction!\n";
                    continue;
                }
                int ballX = ball.getX();
                int ballY = ball.getY();
                robot->hitBall(ballX, ballY, dir);
                ball.Move(ballX - ball.getX(), ballY - ball.getY());
                cout << "Ball position: (" << ball.getX() << ", " << ball.getY() << ")" << endl;
            }
            cout<<"Team "<<t1->getTeamName()<<" has reached the goal in "<<robot->getHits()<<" hits\n";
        }

        void decalreWinner(){
            int hits1=team1->getRobot()->getHits();
            int hits2=team2->getRobot()->getHits();

            cout << team1->getTeamName() << " hits: " << hits1<< endl;
            cout << team2->getTeamName() << " hits: " << hits2 << endl;

            if(hits1<hits2){
                cout<<"Team "<<team1->getTeamName()<<" is the winner of the game\n";
            }else if(hits1>hits2){
                cout<<"Team "<<team2->getTeamName()<<" is the winner of the game\n";
            }else{
                cout<<"Its a tie!\n";
            }
        }
        void StartGame()
        {
            cout<<"The game has started\n";
            Play(team1);
            resetball();
            Play(team2);
            decalreWinner();
        }
};
int main()
{
    Robot robot1("Robo1");
    Robot robot2("Robo2");

    Team team1("Alpha", &robot1);
    Team team2("Delta", &robot2);

    Game game(&team1, &team2);
    game.StartGame();
    return 0;
}