#include <iostream>
#include <ctime>
#include <Windows.h>
#include <conio.h>
#include <mmsystem.h>

#include "World.h"
#include "Console.h"

int main()
{
    bool running = true;

    while (running)
    {
        // PlaySound(TEXT("background.wav"), NULL, SND_FILENAME | SND_ASYNC);

        int seed = time(0);

        World myWorld(seed);

        console::showCursor(false);

        myWorld.display();

        while (true)
        {
            console::gotoxy(0, 0);

            myWorld.simulateOneStep();

            myWorld.display();
            std::cout << "Press 'a' to add an ant." << std::endl;
            std::cout << "Press 'b' to add a bug." << std::endl;
            std::cout << "Press 't' to add a twin bug." << std::endl;
            std::cout << "Press 'r' to restart simulation." << std::endl;
            std::cout << "Press 'q' to exit the simulation." << std::endl;

            if (_kbhit())
            {
                char keyPressed = _getch();

                if (keyPressed == 'a')
                {
                    // add an ant to the world
                    myWorld.createOrganisms(ANT, 1);
                }
                else if (keyPressed == 'b')
                {
                    // add a bug to the world
                    myWorld.createOrganisms(BUG, 1);
                }
                else if (keyPressed == 't')
                {
                    // add a twin bug to the world
                    myWorld.createOrganisms(TWINBUG, 1);
                }
                else if (keyPressed == 'r')
                {
                    // restart simulation
                    console::clearScreen();
                    break;
                }
                else if (keyPressed == 'q')
                {
                    // exit simulation
                    running = false;
                    break;
                }
            }

            Sleep(1000 / WORLD_SPEED);
        }
    }

    console::clearScreen();
    std::cout << "Thank you for playing!" << std::endl;

    std::cin.get();
    return 0;
}
