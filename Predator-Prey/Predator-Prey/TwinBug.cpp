#include "TwinBug.h"
#include "Organism.h"
#include <iostream>
#include "Console.h"
#include <Windows.h>

TwinBug::TwinBug(World* aWorld, int xcoord, int ycoord) : Organism(aWorld, xcoord, ycoord)
{
    dead = false;
}

void TwinBug::move()
{
    if (world->getAt(x, y + 1) != NULL)
    {
        if (world->getAt(x, y + 1)->getType() == ANT || world->getAt(x, y + 1)->getType() == BUG)
        {
            delete world->getAt(x, y + 1);
            movesTo(x, y + 1);
            return;
        }
        else if (world->getAt(x, y + 1)->getType() == TWINBUG)
        {
            // explode with other twin but 0, 1 from this one
            explode(0, 1);

            return;
        }
    }

    if (world->getAt(x, y - 1) != NULL)
    {
        if (world->getAt(x, y - 1)->getType() == ANT || world->getAt(x, y - 1)->getType() == BUG)
        {
            delete world->getAt(x, y - 1);
            movesTo(x, y - 1);
            return;
        }
        else if (world->getAt(x, y - 1)->getType() == TWINBUG)
        {
            // explode with other twin but 0, -1 from this one
            explode(0, -1);

            return;
        }
    }

    if (world->getAt(x - 1, y) != NULL)
    {
        if (world->getAt(x - 1, y)->getType() == ANT || world->getAt(x - 1, y)->getType() == BUG)
        {
            delete world->getAt(x - 1, y);
            movesTo(x - 1, y);
            return;
        }
        else if (world->getAt(x - 1, y)->getType() == TWINBUG)
        {
            // explode with other twin but -1, 0 from this one
            explode(-1, 0);

            return;
        }
    }

    if (world->getAt(x + 1, y) != NULL)
    {
        if (world->getAt(x + 1, y)->getType() == ANT || world->getAt(x + 1, y)->getType() == BUG)
        {
            delete world->getAt(x + 1, y);
            movesTo(x + 1, y);
            return;
        }
        else if (world->getAt(x + 1, y)->getType() == TWINBUG)
        {
            // explode with other twin but 1, 0 from this one
            explode(1, 0);

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
    // TwinBug does not generate offspring
}

void TwinBug::breed()
{
    // TwinBug does not breed
}

bool TwinBug::isDead() const
{
    if (dead)
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
    return (char)232;
}

int TwinBug::size() const
{
    return 40;
}

bool TwinBug::in_range(int x, int y)
{
    return (x >= 0) && (x < WORLDSIZE) && (y >= 0) && (y < WORLDSIZE);
}

void TwinBug::explode(int xOther, int yOther)
{

    // kill current twin bug
    // current
    dead = true;

    // go to current bug and show explosion
    console::gotoxy(x, y);
    console::setTextColor(red);
    std::cout << "*";

    // go to other bug and show explosion
    console::gotoxy(x + xOther, y + yOther);
    console::setTextColor(red);
    std::cout << "*";

    // up
    console::gotoxy(x, y - 1);
    console::setTextColor(red);
    std::cout << "*";
    if (world->getAt(x, y - 1) != NULL)
    {
        delete world->getAt(x, y - 1);
        world->setAt(x, y - 1, NULL);
    }

    // down
    console::gotoxy(x, y + 1);
    console::setTextColor(red);
    std::cout << "*";
    if (world->getAt(x, y + 1) != NULL)
    {
        delete world->getAt(x, y + 1);
        world->setAt(x, y + 1, NULL);
    }

    // left
    console::gotoxy(x - 1, y);
    console::setTextColor(red);
    std::cout << "*";
    if (world->getAt(x - 1, y) != NULL)
    {
        delete world->getAt(x - 1, y);
        world->setAt(x - 1, y, NULL);
    }

    // right
    console::gotoxy(x + 1, y);
    console::setTextColor(red);
    std::cout << "*";
    if (world->getAt(x + 1, y) != NULL)
    {
        delete world->getAt(x + 1, y);
        world->setAt(x + 1, y, NULL);
    }

    // up left
    console::gotoxy(x - 1, y - 1);
    console::setTextColor(red);
    std::cout << "*";
    if (world->getAt(x - 1, y - 1) != NULL)
    {
        delete world->getAt(x - 1, y - 1);
        world->setAt(x - 1, y - 1, NULL);
    }

    // up right
    console::gotoxy(x + 1, y - 1);
    console::setTextColor(red);
    std::cout << "*";
    if (world->getAt(x + 1, y - 1) != NULL)
    {
        delete world->getAt(x + 1, y - 1);
        world->setAt(x + 1, y - 1, NULL);
    }

    // down left
    console::gotoxy(x - 1, y + 1);
    console::setTextColor(red);
    std::cout << "*";
    if (world->getAt(x - 1, y + 1) != NULL)
    {
        delete world->getAt(x - 1, y + 1);
        world->setAt(x - 1, y + 1, NULL);
    }

    // down right
    console::gotoxy(x + 1, y + 1);
    console::setTextColor(red);
    std::cout << "*";
    if (world->getAt(x + 1, y + 1) != NULL)
    {
        delete world->getAt(x + 1, y + 1);
        world->setAt(x + 1, y + 1, NULL);
    }

    // directions for other twin bug

    // up
    console::gotoxy(x + xOther, y + yOther - 1);
    console::setTextColor(red);
    std::cout << "*";
    if (world->getAt(x + xOther, y + yOther - 1) != NULL && 
        x + xOther != x && 
        y + yOther - 1 != y)
    {
        delete world->getAt(x + xOther, y + yOther - 1);
        world->setAt(x + xOther, y + yOther - 1, NULL);
    }

    // down
    console::gotoxy(x + xOther, y + yOther + 1);
    console::setTextColor(red);
    std::cout << "*";
    if (world->getAt(x + xOther, y + yOther + 1) != NULL && 
        x + xOther != x && 
        y + yOther + 1 != y)
    {
        delete world->getAt(x + xOther, y + yOther + 1);
        world->setAt(x + xOther, y + yOther + 1, NULL);
    }

    // left
    console::gotoxy(x + xOther - 1, y + yOther);
    console::setTextColor(red);
    std::cout << "*";
    if (world->getAt(x + xOther - 1, y + yOther) != NULL &&
        x + xOther - 1 != x &&
        y + yOther != y)
    {
        delete world->getAt(x + xOther - 1, y + yOther);
        world->setAt(x + xOther - 1, y + yOther, NULL);
    }

    // right
    console::gotoxy(x + xOther + 1, y + yOther);
    console::setTextColor(red);
    std::cout << "*";
    if (world->getAt(x + xOther + 1, y + yOther) != NULL &&
        x + xOther + 1 != x &&
        y + yOther != y)
    {
        delete world->getAt(x + xOther + 1, y + yOther);
        world->setAt(x + xOther + 1, y + yOther, NULL);
    }

    // up left
    console::gotoxy(x + xOther - 1, y + yOther - 1);
    console::setTextColor(red);
    std::cout << "*";
    if (world->getAt(x + xOther - 1, y + yOther - 1) != NULL &&
        x + xOther - 1 != x &&
        y + yOther - 1 != y)
    {
        delete world->getAt(x + xOther - 1, y + yOther - 1);
        world->setAt(x + xOther - 1, y + yOther - 1, NULL);
    }

    // up right
    console::gotoxy(x + xOther + 1, y + yOther - 1);
    console::setTextColor(red);
    std::cout << "*";
    if (world->getAt(x + xOther + 1, y + yOther - 1) != NULL &&
        x + xOther + 1 != x &&
        y + yOther - 1 != y)
    {
        delete world->getAt(x + xOther + 1, y + yOther - 1);
        world->setAt(x + xOther + 1, y + yOther - 1, NULL);
    }

    // down left
    console::gotoxy(x + xOther - 1, y + yOther + 1);
    console::setTextColor(red);
    std::cout << "*";
    if (world->getAt(x + xOther - 1, y + yOther + 1) != NULL &&
        x + xOther - 1 != x &&
        y + yOther + 1 != y)
    {
        delete world->getAt(x + xOther - 1, y + yOther + 1);
        world->setAt(x + xOther - 1, y + yOther + 1, NULL);
    }

    // down right
    console::gotoxy(x + xOther + 1, y + yOther + 1);
    console::setTextColor(red);
    std::cout << "*";
    if (world->getAt(x + xOther + 1, y + yOther + 1) != NULL &&
        x + xOther + 1 != x &&
        y + yOther + 1 != y)
    {
        delete world->getAt(x + xOther + 1, y + yOther + 1);
        world->setAt(x + xOther + 1, y + yOther + 1, NULL);
    }
}
