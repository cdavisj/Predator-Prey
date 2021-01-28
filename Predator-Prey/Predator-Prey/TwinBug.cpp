#include "TwinBug.h"
#include "Organism.h"

TwinBug::TwinBug(World* aWorld, int xcoord, int ycoord) : Organism(aWorld, xcoord, ycoord)
{
    deathTicks = 0;
}

void TwinBug::move()
{
    breedTicks++;
    deathTicks++;

    if (world->getAt(x, y + 1) != NULL)
    {
        if (world->getAt(x, y + 1)->getType() == ANT)
        {
            deathTicks = 0;
            delete world->getAt(x, y + 1);
            movesTo(x, y + 1);
            return;
        }
    }

    if (world->getAt(x, y - 1) != NULL)
    {
        if (world->getAt(x, y - 1)->getType() == ANT)
        {
            deathTicks = 0;
            delete world->getAt(x, y - 1);
            movesTo(x, y - 1);
            return;
        }
    }

    if (world->getAt(x - 1, y) != NULL)
    {
        if (world->getAt(x - 1, y)->getType() == ANT)
        {
            deathTicks = 0;
            delete world->getAt(x - 1, y);
            movesTo(x - 1, y);
            return;
        }
    }

    if (world->getAt(x + 1, y) != NULL)
    {
        if (world->getAt(x + 1, y)->getType() == ANT)
        {
            deathTicks = 0;
            delete world->getAt(x + 1, y);
            movesTo(x + 1, y);
            return;
        }
    }

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

void TwinBug::generateOffspring(int whereX, int whereY)
{
    new TwinBug(this->world, whereX, whereY);

    breedTicks = 0;
}

void TwinBug::breed()
{
    if (breedTicks >= BREED_BUGS)
    {
        breedAtAdjacentCell();
    }

}

bool TwinBug::isDead() const
{
    if (deathTicks >= STARVE_BUGS)
    {
        return true;
    }
    else
    {
        return false;
    }
}

OrganismType TwinBug::getType() const
{
    return TWINBUG;
}

char TwinBug::representation() const
{
    return (char)233;
}

int TwinBug::size() const
{
    return 30;
}

bool TwinBug::in_range(int x, int y)
{
    return (x >= 0) && (x < WORLDSIZE) && (y >= 0) && (y < WORLDSIZE);
}
