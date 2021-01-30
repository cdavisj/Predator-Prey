#include <iostream>
#include <ctime>
#include <Windows.h>
#include <conio.h>
#include <mmsystem.h>

#include "World.h"
#include "Console.h"

int main()
{
    char choice = 'y';

    // PlaySound(TEXT("background.wav"), NULL, SND_FILENAME | SND_ASYNC);

    while (choice == 'y' || choice == 'Y')
    {
        int seed = time(0);

        World myWorld(seed);

        console::showCursor(false);

        myWorld.display();

        while (true)
        {
            console::gotoxy(0, 0);

            myWorld.simulateOneStep();

            myWorld.display();
            std::cout << "Press any key to exit simulation.." << std::endl;

            if (_kbhit())
                break;

            Sleep(1000 / WORLD_SPEED);
        }

        console::showCursor(true);
        std::cout << std::endl;
        std::cout << "Rerun simulation? (enter 'y' or 'n'): ";
        std::cin >> choice;

        console::clearScreen();
    }

    std::cout << "Thank you for playing!" << std::endl;

    std::cin.ignore();
    std::cin.get();
    return 0;
}
