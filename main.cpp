//developed by syed mashaf zaidi
#include "pacman.h"
int main()
{
    Pacman pac;
    pac.Starting_interphase();

    Blinky blinky(5, 5, "red");
    Pinky pinky(10, 2, "pink");
    Inky inky(15, 7, "cyan");
    Clyde clyde(18, 8, "orange");

    Ghosts* ghostArray[] = { &blinky, &pinky, &inky, &clyde };
    int ghostCount =4;

    Board board;

    GameLoop(pac, ghostArray, ghostCount, board);

    return 0;
}
