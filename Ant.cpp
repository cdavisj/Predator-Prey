#include <cstdlib>
#include <iostream>

#include "Ant.h"
#include "Organism.h"
#include "World.h"

Ant::Ant(World* aWorld, int xcoord, int ycoord) : Organism(aWorld, xcoord, ycoord)
{
}

void Ant::move()
{
    breedTicks++;
    Move mover = world->randomMove();

    switch (mover) 
    {
    case UP:
        if (world->getAt(x, y + 1) == NULL && in_range(x, y + 1))
        {
            movesTo(x, y + 1);
        }
        break;

    case DOWN:
        if (world->getAt(x, y - 1) == NULL && in_range(x, y - 1))
        {
            movesTo(x, y - 1);
        }
        break;

    case LEFT:
        if (world->getAt(x - 1, y) == NULL && in_range(x - 1, y))
        {
            movesTo(x - 1, y);
        }
        break;

    case RIGHT:
        if (world->getAt(x + 1, y) == NULL && in_range(x + 1, y))
        {
            movesTo(x + 1, y);
        }
        break;

    default:
        break;
    }
}

void Ant::breed()
{
    if (breedTicks >= BREED_ANTS)
    {
        breedAtAdjacentCell();
    }
}


void Ant::generateOffspring(int whereX, int whereY)
{
    new Ant(this->world, whereX, whereY);
    breedTicks = 0;
}


OrganismType Ant::getType() const
{
    return ANT;
}

char Ant::representation() const
{
    return (char)248;
}

int Ant::size() const
{
    return 10;
}

bool Ant::in_range(int x, int y)
{
    return (x >= 0) && (x < WORLDSIZE) && (y >= 0) && (y < WORLDSIZE);
}
