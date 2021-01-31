#ifndef INHERITANCE_AND_POLYMORPHISM_Ant
#define INHERITANCE_AND_POLYMORPHISM_Ant

#include <iostream>

#include "Organism.h"
#include "World.h"

class Ant : public Organism
{
public:
    
    Ant(World* aWorld, int xcoord, int ycoord);

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
    
    bool in_range(int xx, int yy);
    
private:
    
    void generateOffspring(int whereX, int whereY);

    bool canMove;
};

#endif /* defined(__INHERITANCE_AND_POLYMORPHISM__Ant__) */
