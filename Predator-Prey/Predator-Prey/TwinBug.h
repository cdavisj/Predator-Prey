#ifndef INHERITANCE_AND_POLYMORPHISM_TwinBug
#define INHERITANCE_AND_POLYMORPHISM_TwinBug

#include <iostream>

#include "World.h"
#include "Organism.h"

class TwinBug : public Organism
{
public:

    TwinBug(World* aWorld, int xcoord, int ycoord);

    // In the given world moves this organism.
    void move();

    // Makes this organism breed.
    void breed();

    // Returns the type of this organism.
    OrganismType getType() const;

    // The character representation of this organism.
    char representation() const;

    // The size of this organism.
    int size() const;

    // Returns true if organism is dead, false otherwise.
    bool isDead() const;

    bool in_range(int x, int y);

    // Method for doing an explosion in the direction 
    // of the other twin bug it came into contact with
    void explode(int, int);

private:
    void generateOffspring(int whereX, int whereY);

    bool dead;
};

#endif /* defined(__INHERITANCE_AND_POLYMORPHISM__TwinBug__) */
