//developed by syed mashaf zaidi
#include <iostream>
#include <cstdlib>      //used for generating random values
#include <ctime>        //for rand()function
#include <conio.h>      //for setting up time duration
#include <chrono>       
#include <windows.h>    //for setting up console based color

#define red "\033[31m"  //used for setting up blinky red
#define green "\033[32m" //used in score var
#define blue "\033[34m"  //used for ghost when they are in frighten mode
#define cyan "\033[36m"   //color of inky
#define pink  "\033[35m"  //color of pinky
#define orange "\033[33m"  //color of cyldy
#define yellow "\033[93m"
#define Dark_blue "\033[48;5;18m"   
#define reset "\033[0m"

using namespace std;
using namespace std::chrono;

enum direction { UP, DOWN, LEFT, RIGHT, NONE }; //the position of PACMAN and ghosts
enum Collideobj { ghost, powerpallet, food };  //the collision object of pacman



direction getdirection();   //used for getting input from user and perform the direction task with user specified keys

struct BoardItem     //pacman baord item
{
    bool hasFood;
    bool hasPowerPallet;
    bool hasGhost;
};

class Pacman   //The PACMAN class
{
public:
    int x, y, score;
    bool isfrightenedmode = false;
    bool terminating_State = false;
    high_resolution_clock::time_point frightenedStartTime;

    Pacman();  //the default constructor of pacman
    void Instruction();  //the game instruction
    void Credit(); 
    void Starting_interphase();//starting menue
    void Move(direction dir);  //for moving the pacman by user input kbhit-h
    void Condition();
    void Collide(Collideobj obj);
    void look(direction dir);  //the pacman is looking at which dir
    void Frighten_collision(Collideobj obj);  
};

class Ghosts   //the abstract class ghosts
{
protected:  //protected member function of class ghosts
    virtual void Target(string mode) = 0;

public:
    int xpos, ypos;
    string color;
    Ghosts();
    Ghosts(int startX, int startY, string col);
    void MoveToCorner();
    virtual void Move(Pacman pac);    //virtual function move used for movement of ghosts
    virtual void Look(direction dir); //tells the ghosts is looking ar which position
    virtual void Collide(Collideobj collide);  //check the collision of pacman and ghosts
};

class Chasebehaviour : public Ghosts  //the behaviour of ghosts
{
public:
    Chasebehaviour();
    virtual void Chase();
    void Target(string mode) override;
};

class Chaseaggressive : public Chasebehaviour //blinky nature
{
public:
    Chaseaggressive();
    void Chase() override;
    void Target(string mode) override;
};

class Chaserandom : public Chasebehaviour 
{
public:
    Chaserandom();
    void Chase() override;
    void Target(string mode) override;
};

class Chaseambush : public Chasebehaviour 
{
public:
    Chaseambush();
    void Chase() override;
    void Target(string mode) override;
};

class ChasePatrol : public Chasebehaviour 
{
public:
    ChasePatrol();
    void Chase() override;
    void Target(string mode) override;
};

class Scatterbehaviour : public Ghosts
{
public:
    Scatterbehaviour();
    virtual void Scatter();
    void Target(string mode) override;
};

class Scatterbottomleftcorner : public Scatterbehaviour
{
public:
    Scatterbottomleftcorner();
    void Scatter() override;
    void Target(string mode) override;
};

class Scatterbottomrightcorner : public Scatterbehaviour 
{
public:
    Scatterbottomrightcorner();
    void Scatter() override;
    void Target(string mode) override;
};

class Scattertopleftcorner : public Scatterbehaviour 
{
public:
    Scattertopleftcorner();
    void Scatter() override;
    void Target(string mode) override;
};

class Scattertoprightcorner : public Scatterbehaviour
{
public:
    Scattertoprightcorner();
    void Scatter() override;
    void Target(string mode) override;
};

class Frightenedbehaviour : public Ghosts  //when pacman eats the power pallet then frighten behaviour od
{
public:
    Frightenedbehaviour();
    virtual void Frightened();
    void Target(string mode) override;
};

class Frightenedwandering : public Frightenedbehaviour 
{
public:
    Frightenedwandering();
    void Frightened() override;
    void Target(string mode) override;
};

class Blinky : public Ghosts 
{
    string color;

public:
    Blinky(int startX, int startY, string color);
    string getcolor();
    void Target(string mode) override;
    void Move(Pacman pac) override;
};

class Pinky : public Ghosts 
{
    string color;

public:
    Pinky(int startX, int startY, string color);
    void Target(string mode) override;
    void Move(Pacman pac) override;
};

class Inky : public Ghosts 
{
    string color;

public:
    Inky(int startX, int startY, string color);
    void Target(string mode) override;
    void Move(Pacman pac, const Blinky& blinky) ;
};

class Clyde : public Ghosts
{
    string color;

public:
    Clyde(int startX, int startY, string color);
    void Target(string mode) override;
    void Move(Pacman pac) override;
};

class Board
{
public:
    static const int WIDTH = 30;
    static const int HEIGHT = 10;
    BoardItem grid[HEIGHT][WIDTH];

    Board();
    void display(Pacman& pac, Ghosts* ghostArray[], int ghostCount);
};

void GameLoop(Pacman& pac, Ghosts* ghostArray[], int ghostCount, Board& board);

