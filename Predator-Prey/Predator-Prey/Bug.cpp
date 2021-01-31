#include "Bug.h"
#include "Organism.h"

Bug::Bug(World* aWorld, int xcoord, int ycoord) : Organism(aWorld, xcoord, ycoord)
{
    deathTicks = 0;

    canMove = false;
}

void Bug::move()
{
    if (canMove)
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

        // set canMove to false to skip next move
        canMove = false;
    }
    else
    {
        // set canMove to true to allow them to move next turn
        canMove = true;
    }
}

void Bug::generateOffspring(int whereX, int whereY)
{
    new Bug(this->world, whereX, whereY);

    breedTicks = 0;
}

void Bug::breed()
{
    if (breedTicks >= BREED_BUGS)
    {
        breedAtAdjacentCell();
    }
    
}

bool Bug::isDead() const
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

OrganismType Bug::getType() const
{
    return BUG;
}

char Bug::representation() const
{
    return (char)233;
}

int Bug::size() const
{
    return 30;
}

bool Bug::in_range(int x, int y)
{
    return (x >= 0) && (x < WORLDSIZE) && (y >= 0) && (y < WORLDSIZE);
}
