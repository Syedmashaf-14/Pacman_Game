
//developed by syed mashaf zaidi

#include "pacman.h"
#include<cassert>
#include<chrono>
Pacman::Pacman() : x(1), y(1), score(0) {}

direction getdirection()   //this is being responsible for setting up the value of user control of pacman.
//basically these are function that get input from user for movement.
{
	if (_kbhit())
	{
		char input = _getch();
		switch (input)
		{
		case 'w':
		case 'W':
			return UP;
		case 's':
		case 'S':
			return DOWN;
		case 'a':
		case 'A':
			return LEFT;
		case 'd':
		case 'D':
			return RIGHT;
		}
	}
	return NONE;
}
void Pacman::Credit()	//THE GAME CREATERS
{
	system("cls");
	cout << "GAME CREATED BY \n";
	cout << "23F-0536 AHMAD WASEEM \n";
	cout << "23F-0529 MASHAF ZAIDI \n";
}


void Pacman::Instruction()	//the instruction of the game
{
	system("cls");
	cout << "........................INSTRUCTION.............................." << endl;
	cout << "The Game started with the Scatter mode \n";
	cout << "The Game continues with the Chase mode \n";
	cout << "The 4 Ghosts are there INKY, PINKY, CLYDY, BINKY \n";
	cout << "The Binky has RED color \n";
	cout << "The Pinky has PINK color \n";
	cout << "The Clyde has ORANGE color \n";
	cout << "The Inky has CYAN color \n";
	cout << "PRESS W FOR UP \n";
	cout << "PRESS S FOR DOWN \n";
	cout << "PRESS A FOR LEFT \n";
	cout << "PRESS A FOR RIGHT\n";
	cout << "You are given only one chance \n";
	Sleep(4000);
}

void Pacman::Starting_interphase()
//It is the starting interphase of the game when the game started the menue will pop up

{
	system("cls");	//clear the screen
	cout << "..........................." << "PACMAN GAME" << "............................" << endl;
	cout << std::left << "1.START GAME \n";
	cout << std::left << "2.VIEW INSTRUCTIONS \n";
	cout << std::left << "3.CREDIT \n";
	cout << std::left << "4.EXIT GAME \n";
	int choice = 0;
	cout << "Enter your choice \n";
	cin >> choice;	//getting user input from the menue up
	assert(choice == 1 || choice == 2 || choice == 3 || choice == 4);

	switch (choice)
	{
	case 1:
		cout << "The game is starting" << " ............................\n";
		break;
	case 2:
		Instruction();
		system("pause");
		Starting_interphase(); //basically calling the func again
		break;
	case 3:

		Credit();
		system("pause");
		Starting_interphase();

		break;

	case 4:
		cout << "You have choosen to exit \n";
		exit(0);
		break;
	default:
		cout << "Invalid \n";
		break;
	}
}

void Pacman::Move(direction dir)	//this will set the movement of pacman
{
	switch (dir)
	{
	case UP:	//so when  w is press then pacman will move upper so y will be decremented
		y++;
		break;
	case DOWN:	//so when s is pressed the pacman will come down
		y--;
		break;
	case LEFT:    //similarly when a is pressed it comes at left pos
		x--;
		break;
	case RIGHT:   //when d is pressed then the pacman will comes at the right side
		x++;
		break;
	default:
		break;
	}
}



void Pacman::Condition()
{
	if (terminating_State == true)//here it is being used in the frightened mode when the pacman eats the power pallet  then if pacman==ghost then game will not terminate
	{
		exit(0);	//to exit directly
	}
	else
	{
		cout << "\nPacman is safe! Continue playing.\n";
	}
}

void Pacman::Collide(Collideobj obj)  //this function is reposible for setting up the object with whom pacman will collide down
{
	if (obj == ghost)
	{
		auto now = high_resolution_clock::now();
		auto duration = duration_cast<seconds>(now - frightenedStartTime);
		bool isFrightenedExpired = duration.count() >= 5;

		if (isfrightenedmode && !isFrightenedExpired)
		{
			score += 15; //if obj==ghost then u will get increment of 15 in the score
			terminating_State = false;
		}
		else
		{

			terminating_State = true;
		}

		Condition();
	}

	else if (obj == food)
	{
		score += 1; //updating the score will 1 increment
		cout << "\nFood collected! Score: " << score << endl;
	}
	else if (obj == powerpallet)
	{
		score += 10;  //power pallet inc the scoe upto 10 
		isfrightenedmode = true;
		frightenedStartTime = high_resolution_clock::now();
		cout << "\nPower Pellet collected! Ghosts are vulnerable!\n";
		cout << "The FRIGHTEN mode has started! \n";
		Sleep(800);
	}

}
void Pacman::look(direction dir)
{
	switch (dir) //basically telling where the pacman is looking to
	{
	case UP:
		cout << "the pacman is looking up \n";
		break;
	case DOWN:
		cout << "the pacman is looking down \n";
		break;

	case LEFT:
		cout << "the pacman is looking left \n";
		break;

	case RIGHT:
		cout << "the pacman is looking right \n";
		break;
	default:
		cout << "the pacman is looking none \n";
		break;
	}


}

void Pacman::Frighten_collision(Collideobj obj)

{
	//separate condition for frightened collision used in the game loop
	if (isfrightenedmode == true)
	{
		if (obj == ghost)
		{
			terminating_State = false;
			score += 15;
			Condition();

		}
	}


}




Board::Board()
{
	//The board of the game
	for (int i = 0; i < HEIGHT; ++i)
	{
		for (int j = 0; j < WIDTH; ++j)
		{
			grid[i][j].hasFood = true;	//bool var has food,powerpallet,hasghosts
			grid[i][j].hasPowerPallet = false;
			grid[i][j].hasGhost = false;
		}
	}
	grid[0][0].hasPowerPallet = true;	//the power pallet is at the extreme pos of board
	grid[0][WIDTH - 1].hasPowerPallet = true;	
	grid[HEIGHT - 1][0].hasPowerPallet = true;
	grid[HEIGHT - 1][WIDTH - 1].hasPowerPallet = true;
}



void Board::display(Pacman& pac, Ghosts* ghostArray[], int ghostCount) {
	system("CLS");  // Clear the screen

	auto now = high_resolution_clock::now();	//this is responsoible for starting the time measure of specific task
	auto duration = duration_cast<seconds>(now - pac.frightenedStartTime);
	bool isFrightenedExpired = duration.count() >= 5; //here setted the condition for retaining the color

	for (int j = 0; j < WIDTH + 32; ++j) {
		cout << red << "#" << reset;	//setting up the boundry of red upper one
	}
	cout << endl;

	for (int i = 0; i < HEIGHT; ++i)
	{

		cout << blue << "#" << reset;

		for (int j = 0; j < WIDTH; ++j)
		{
			bool occupied = false;

			// Display Pacman (P)	
			if (pac.x == j && pac.y == iw)
			{
				cout << yellow << "P " << reset;
				occupied = true;
			}

			// Display Ghosts (G)
			//ghostcount is 4
			for (int k = 0; k < ghostCount; ++k)
			{
				if (ghostArray[k]->xpos == j && ghostArray[k]->ypos == i)
				{
					if (pac.isfrightenedmode && !isFrightenedExpired)
					{
						cout << blue << "G " << reset;  //frightened mode is on
					}
					else
					{
						// Display ghosts in their original colors once the frightened mode expires
						switch (k)
						{
							//these are the colour excepy of the frightened mode
						case 0:
							cout << red << "G " << reset;   // Red Ghost (Blinky)
							break;
						case 1:
							cout << orange << "G " << reset; // Orange Ghost (Clyde)
							break;
						case 2:
							cout << cyan << "G " << reset;  // Cyan Ghost (Inky)
							break;
						case 3:
							cout << pink << "G " << reset;  // Pink Ghost (Pinky)
							break;
						default:
							cout << "\033[37m" << "G " << reset; // Default Ghost color (white)
							break;
						}
					}
					occupied = true;
					break;  // Once the ghost is displayed, move on to the next position
				}
			}

			// Display Power Pellets (O)

			if (!occupied && grid[i][j].hasPowerPallet)
			{
				cout << blue << "O " << reset;
				occupied = true;
			}

			// Display Food (. )
			if (!occupied && grid[i][j].hasFood)
			{
				cout << ". ";
				occupied = true;
			}

			// Empty space
			if (!occupied)
			{
				cout << "  ";
			}
		}

		// Right boundary
		cout << blue << "#" << reset << endl;
	}

	// Bottom boundary
	for (int j = 0; j < WIDTH + 32; ++j)
	{
		cout << red << "#" << reset;
	}
	cout << endl;

	// Display the score with green color
	cout << green << "\nScore: " << pac.score << reset << endl;
}

Ghosts::Ghosts() { }	//ghost constructor
Ghosts::Ghosts(int startX, int startY, string col) : xpos(startX), ypos(startY), color(col) { }

void Ghosts::Move(Pacman pac)
{
	//ghost movement 
	//the rand()function is here for movement
	if (rand() % 2 == 0)
	{
		xpos += 1;
	}
	else {
		xpos -= 1;
	}

	if (rand() % 2 == 0) {
		ypos += 1;
	}
	else {
		ypos -= 1;
	}
}

void Ghosts::Look(direction dir)
{
	//thes tell that the ghost is looking where
	switch (dir)
	{
	case UP:
		cout << "the ghost is looking up \n";
		break;
	case DOWN:
		cout << "the ghost is looking down \n";
		break;

	case LEFT:
		cout << "the ghost is looking left \n";
		break;

	case RIGHT:
		cout << "the ghost is looking right \n";
		break;
	default:
		cout << "the ghost is looking none \n";
		break;
	}


}

// In the Ghost class, implement a function that moves the ghost towards its scatter corner
void Ghosts::MoveToCorner()	//move to corner is being used in the scatter mode...mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm n 
{
	int targetX = 0, targetY = 0;

	if (color == "Red") { // Blinky (Top-right corner)
		targetX = Board::WIDTH - 2;
		targetY = 0; 
	}
	else if (color == "Pink") { // Pinky (Top-left corner)
		targetX = 1;
		targetY = 0;
	}
	else if (color == "Cyan") { // Inky (Bottom-left corner)
		targetX = 0;
		targetY = Board::HEIGHT -1;
	}
	else if (color == "Orange") { // Clyde (Bottom-right corner)
		targetX = Board::WIDTH - 1;
		targetY = Board::HEIGHT - 1;
	}

	// Move towards the target corner
	if (xpos < targetX) xpos++;
	else if (xpos > targetX) xpos--;

	if (ypos < targetY) ypos++;
	else if (ypos > targetY) ypos--;
}



void Ghosts::Collide(Collideobj collide)
{
	if (collide == ghost)
	{
		cout << "the game is over! \n";
		exit(0);
	}


}

//behavviour of the ghost in the diff mode 
Chasebehaviour::Chasebehaviour() :Ghosts() {}
void Chasebehaviour::Chase()
{
	cout << "The ghost is chasing the PACMAN \n";
}
void Chasebehaviour::Target(string mode) {}



Chaseaggressive::Chaseaggressive() :Chasebehaviour() {}
void Chaseaggressive::Chase()
{
	cout << "The Blinky is chasing the PACMAN aggresively \n";
}
void Chaseaggressive::Target(string mode) {}


Chaserandom::Chaserandom() :Chasebehaviour() {}
void Chaserandom::Chase()
{
	cout << "The Clyde is chasing the PACMAN randomly \n";
}
void Chaserandom::Target(string mode) {}

Chaseambush::Chaseambush() :Chasebehaviour() {}
void Chaseambush::Chase()
{
	cout << "The Pinky is chasing the PACMAN with ambush behaviour" << endl;
}
void Chaseambush::Target(string mode) {}


ChasePatrol::ChasePatrol() :Chasebehaviour() {}
void ChasePatrol::Chase()
{
	cout << "The Inky is chasing the PACMAN with ambush behaviour" << endl;
}
void ChasePatrol::Target(string mode) {}


Scatterbehaviour::Scatterbehaviour() :Ghosts() {}
void Scatterbehaviour::Scatter() { cout << "The Ghost are heading towards their repsective corner of home \n"; }
void Scatterbehaviour::Target(string mode) {}


Scatterbottomleftcorner::Scatterbottomleftcorner() :Scatterbehaviour() {}
void Scatterbottomleftcorner::Scatter()
{
	cout << "The Ghost are heading towards bottom left corner corner  \n";
}
void Scatterbottomleftcorner::Target(string mode) {}


Scatterbottomrightcorner::Scatterbottomrightcorner() :Scatterbehaviour() {}
void Scatterbottomrightcorner::Scatter()
{
	cout << "The Ghost are heading towards bottom right corner corner  \n";
}
void Scatterbottomrightcorner::Target(string mode) {}


Scattertopleftcorner::Scattertopleftcorner() :Scatterbehaviour() {}
void Scattertopleftcorner::Scatter()
{
	cout << "The Ghost are heading towards Top left corner .  \n";
}
void Scattertopleftcorner::Target(string mode) {}


Scattertoprightcorner::Scattertoprightcorner() :Scatterbehaviour() {}
void Scattertoprightcorner::Scatter()
{
	cout << "The Ghost are heading towards top right corner .  \n";
}
void Scattertoprightcorner::Target(string mode) {}




Frightenedbehaviour::Frightenedbehaviour() :Ghosts() {}
void Frightenedbehaviour::Frightened()
{
	cout << "The game enetered in frightened mode. The ghost will turn Blue.";
}
void Frightenedbehaviour::Target(string mode) {}



Frightenedwandering::Frightenedwandering() :Frightenedbehaviour() {}
void Frightenedwandering::Frightened()
{
	cout << "The game enetered in frightened mode. The ghost will turn Blue.";
}
void Frightenedwandering::Target(string mode) {}




// Blinky - Inherits from ghosts

Blinky::Blinky(int startX, int startY, string color) : Ghosts(startX, startY, "Red") {}
string Blinky::getcolor()
{
	return this->color;
}

void Blinky::Target(string mode)
{
	if (mode == "chase")
	{
		cout << "The Binky will chase Pacman aggressively \n";

	}
	else if (mode == "frighten")
	{
		cout << "The Pacman will chase the Binky \n";
	}
	else if (mode == "scatter")
	{
		cout << "The Binky will return to its base \n";

	}
}

//blinky movemnet as it is aggressive it is continuosly looking of pacamn everywhere he goes
void Blinky::Move(Pacman pac)
{

	if (xpos < pac.x) xpos++;
	else if (xpos > pac.x) xpos--;

	if (ypos < pac.y) ypos++;
	else if (ypos > pac.y) ypos--;



}



// Pinky - Inherits from ghosts
Pinky::Pinky(int startX, int startY, string color) : Ghosts(startX, startY, "Pink") {}
void Pinky::Target(string mode)
{
	if (mode == "chase")
	{
		cout << "The Binky will chase Pacman aggressively \n";

	}
	else if (mode == "frighten")
	{
		cout << "The Pacman will chase the Binky \n";
	}
	else if (mode == "scatter")
	{
		cout << "The Binky will return to its base \n";

	}
}

//pinky movement it also follow the pacamn
void Pinky::Move(Pacman pac) 
{
	if (pac.x < xpos) xpos--;
	else if (pac.x > xpos) xpos++;

	if (pac.y < ypos) ypos--;
	else if (pac.y > ypos) ypos++;
}


// Inky - Inherits from ghosts.

Inky::Inky(int startX, int startY, string color) : Ghosts(startX, startY, "Cyan") {}
void Inky::Target(string mode)
{
	if (mode == "chase")
	{
		cout << "The Binky will chase Pacman aggressively \n";

	}
	else if (mode == "frighten")
	{
		cout << "The Pacman will chase the Binky \n";
	}
	else if (mode == "scatter")
	{
		cout << "The Binky will return to its base \n";

	}
}

//inky looks down the movementof both pacamn and blinky and stay in bewteen of them
void Inky::Move(Pacman pac, const Blinky& blinky)
{
	// Calculate midpoint between Pac-Man and Blinky
	int targetX = (pac.x + blinky.xpos) / 2;   //midpoint of x pos
	int targetY = (pac.y + blinky.ypos) / 2;   //midpoint of y pos

	if (xpos < targetX) xpos++;
	else if (xpos > targetX) xpos--;

	if (ypos < targetY) ypos++;
	else if (ypos > targetY) ypos--;
}




// Clyde - Inherits from ghosts

Clyde::Clyde(int startX, int startY, string color) : Ghosts(startX, startY, "Orange") {}
void Clyde::Target(string mode)
{
	if (mode == "chase")
	{
		cout << "The Binky will chase Pacman aggressively \n";

	}
	else if (mode == "frighten")
	{
		cout << "The Pacman will chase the Binky \n";
	}
	else if (mode == "scatter")
	{
		cout << "The Binky will return to its base \n";

	}
}

void Clyde::Move(Pacman pac) 
{
	int distance = abs(xpos - pac.x) + abs(ypos - pac.y);

	if (distance < 8) { // Chase mode
		if (xpos < pac.x) xpos++;
		else if (xpos > pac.x) xpos--;

		if (ypos < pac.y) ypos++;
		else if (ypos > pac.y) ypos--;
	}
	//else { // Scatter mode (random movement)
	//	xpos += (rand() % 2 == 0) ? 1 : -1;
	//	ypos += (rand() % 2 == 0) ? 1 : -1;
	//}
}



enum GameMode { SCATTER, CHASE };
GameMode currentMode = SCATTER;
auto modeStartTime = high_resolution_clock::now();
const int SCATTER_DURATION = 8;  
const int CHASE_DURATION = 10000;   


void GameLoop(Pacman& pac, Ghosts* ghostArray[], int ghostCount, Board& board)
{
	while (true) {
		auto now = high_resolution_clock::now();
		auto duration = duration_cast<seconds>(now - modeStartTime);

		if (currentMode == SCATTER && duration.count() >= SCATTER_DURATION) 
		{
			currentMode = CHASE;  
			modeStartTime = now;  
		}
		else if (currentMode == CHASE && duration.count() >= CHASE_DURATION) 
		{
			currentMode = SCATTER; 
			modeStartTime = now;  
		}

		direction dir = getdirection();
		pac.Move(dir);

		if (pac.x < 0) pac.x = Board::WIDTH - 1;
		if (pac.x >= Board::WIDTH) pac.x = 0;
		if (pac.y < 0) pac.y = Board::HEIGHT - 1;
		if (pac.y >= Board::HEIGHT) pac.y = 0;

		// Handle food and power pallet
		if (board.grid[pac.y][pac.x].hasFood) {
			pac.Collide(food);
			board.grid[pac.y][pac.x].hasFood = false;
		}
		else if (board.grid[pac.y][pac.x].hasPowerPallet) {
			pac.Collide(powerpallet);
			board.grid[pac.y][pac.x].hasPowerPallet = false;
		}

		// Check for collisions with ghosts
		for (int i = 0; i < ghostCount; ++i) {
			if (pac.x == ghostArray[i]->xpos && pac.y == ghostArray[i]->ypos) {
				pac.Collide(ghost);
			}
		}

		// Move ghosts based on mode
		for (int i = 0; i < ghostCount; ++i) 
		{
			// Move the ghosts depending on the mode
			if (currentMode == SCATTER) 
			{
				ghostArray[i]->MoveToCorner(); // Implement the corner movement logic here
			}
			else if (currentMode == CHASE) {
				ghostArray[i]->Move(pac);  // Regular chase movement
			}
		}

		// Display the game board
		board.display(pac, ghostArray, ghostCount);

		Sleep(100);
	}
}
