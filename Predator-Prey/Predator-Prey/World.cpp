#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <Windows.h>

#include "World.h"
#include "Ant.h"
#include "Bug.h"
#include "TwinBug.h"
#include "Console.h"

///////////////////
// Public functions
///////////////////

// Default constructor: creates and initializes the world
// the seed is used for seeding the random behaviour.
World::World(unsigned int seed) 
{
    // seed the random generator
    srand(seed);

    // Create an empty world
    for (int i = 0; i < WORLDSIZE; i++) 
    {
        for (int j = 0; j < WORLDSIZE; j++) 
        {
            grid[i][j] = NULL;
        }
    }

    // creates the ants
    createOrganisms(ANT, INITIAL_ANTS);

    // creates the bugs
    createOrganisms(BUG, INITIAL_BUGS);

    // creates the twin bugs
    createOrganisms(TWINBUG, INITIAL_TWIN_BUGS);
}

// Deallocate memory allocated to organisms in this world.
World::~World() 
{
    for (int i = 0; i < WORLDSIZE; i++) 
    {
        for (int j = 0; j < WORLDSIZE; j++) 
        {
            if (grid[i][j] != NULL) 
            {
                delete grid[i][j];
            }
        }
    }
}

// Return the organism at the given coordinates
// If the coordinates are not valid, returns NULL
Organism* World::getAt(int x, int y) const 
{
    if ((x >= 0) && (x < WORLDSIZE) && (y >= 0) && (y < WORLDSIZE)) 
    {
        return grid[x][y];
    } 
    else 
    {
        return NULL;
    }
}

// Sets the entry at x,y to the value passed in.
void World::setAt(int x, int y, Organism* org) 
{
    if ((x >= 0) && (x < WORLDSIZE) && (y >= 0) && (y < WORLDSIZE)) 
    {
        grid[x][y] = org;
    }
}

// Displays the world in ASCII.
void World::display() const 
{
    int numAnts = 0;
    int numBugs = 0;
    int numTwinBugs = 0;

    // DRAW TOP BORDER
    std::cout << (char)218; // top left corner

    for (int j = 0; j < WORLDSIZE * 2 + 1; j++)
        std::cout << (char)196; // top walls

    std::cout << (char)191; // top right corner 
    std::cout << std::endl;

    for (int j = 0; j < WORLDSIZE; j++) 
    {
        console::setTextColor(white);

        std::cout << (char)179 << " "; // left wall

        for (int i = 0; i < WORLDSIZE; i++) 
        {
            if (grid[i][j] == NULL) 
            {
                console::setTextColor(white);
                std::cout << "  ";
            } 
            else 
            {
                if (grid[i][j]->getType() == ANT) 
                {
                    console::setTextColor(yellow);
                    numAnts++;
                }
                else if (grid[i][j]->getType() == BUG) 
                {
                    console::setTextColor(green);
                    numBugs++;
                }
                else if (grid[i][j]->getType() == TWINBUG)
                {
                    console::setTextColor(red);
                    numTwinBugs++;
                }

                std::cout << grid[i][j]->representation() << " ";
            }
        }
        
        console::setTextColor(white);
        std::cout << (char)179 << " "; // right wall

        std::cout << std::endl;
    }

    // DRAW TOP BORDER
    console::setTextColor(white);

    std::cout << (char)192; // bottom left corner

    for (int j = 0; j < WORLDSIZE * 2 + 1; j++)
        std::cout << (char)196; // bottom walls

    std::cout << (char)217; // bottom right corner 
    std::cout << std::endl;

    console::setTextColor(white);
    std::cout << "Ants: ";
    console::setTextColor(yellow);
    std::cout << std::setw(3) << std::left << numAnts;

    std::cout << std::endl;
    console::setTextColor(white);
    std::cout << "Bugs: ";
    console::setTextColor(green);
    std::cout << std::setw(3) << std::left << numBugs;

    std::cout << std::endl;
    console::setTextColor(white);
    std::cout << "Twin Bugs: ";
    console::setTextColor(red);
    std::cout << std::setw(3) << std::left << numTwinBugs;

    std::cout << std::endl << std::endl;

    console::setTextColor(white);
}

void World::simulateOneStep() {
    // The main routine that simulates one turn in the world:
    // 1. move twin bugs
    // 2. move bugs
    // 3. move ants
    // 4. make bugs starve (which happends under a certain condition)
    // 5. make the organisms breed (again which happens under a certain
    // condition).

    // Reset all organisms to not moved
    resetOrganisms();

    // Move the twin bugs
    moveOrganism(TWINBUG);

    // Move the bugs
    moveOrganism(BUG);

    // Move the ants
    moveOrganism(ANT);

    // Make the bugs starve
    cleanup();

    //Make them breed
    breedOrganisms();
}

// returns a random number in the range 0 to MAX-1
Position World::randomPosition() const 
{
    Position pos;
    pos.x = rand() % WORLDSIZE;
    pos.y = rand() % WORLDSIZE;
    return pos;
}


Move World::randomMove() const 
{
    return static_cast<Move>(rand() % 4);
}

////////////////////
// Private functions
////////////////////

void World::createOrganisms(OrganismType orgType, int count) 
{
    int orgCount = 0;

    while (orgCount < count) 
    {
        Position p = randomPosition();

        // Only put ant in empty spot
        if (grid[p.x][p.y] == NULL) 
        {
            orgCount++;
            if (orgType == ANT) 
            {
                new Ant(this, p.x, p.y);   // Create an Ant and put it into the world
            }
            else if (orgType == BUG)
            {
                new Bug(this, p.x, p.y);   // Create a Bug and put it into the world
            }
            else if (orgType == TWINBUG)
            {
                new TwinBug(this, p.x, p.y);   // Create a TwinBug and put it into the world
            }
        }
    }
}

// Reset all organisms to not moved
void World::resetOrganisms() 
{
    for (int i = 0; i < WORLDSIZE; i++)
    {
        for (int j = 0; j < WORLDSIZE; j++)
        {
            if (grid[i][j] != NULL)
            {
                grid[i][j]->setMoved(false);
            }
        }
    }
}

// Move all organisms of type aType
void World::moveOrganism(OrganismType aType) 
{
    for (int i = 0; i < WORLDSIZE; i++)
    {
        for (int j = 0; j < WORLDSIZE; j++)
        {
            if (grid[i][j] != NULL)
            {
                if (grid[i][j]->getType() == aType && !(grid[i][j]->hasMoved()))
                {
                    grid[i][j]->move();
                }
            }
        }
    }
}

// Remove all dead organisms from this world.
void World::cleanup() 
{
    for (int i = 0; i < WORLDSIZE; i++) 
    {
        for (int j = 0; j < WORLDSIZE; j++) 
        {
            // Kill off any organisms that haven't eaten recently
            if ((grid[i][j] != NULL) && grid[i][j]->isDead()) 
            {
                delete grid[i][j];
                grid[i][j] = NULL;
            }
        }
    }
}

// Make the organisms breed
void World::breedOrganisms() 
{
    for (int i = 0; i < WORLDSIZE; i++)
    {
        for (int j = 0; j < WORLDSIZE; j++)
        {
            if (grid[i][j] != NULL)
            {
                grid[i][j]->breed();
            }
        }
    }
}
