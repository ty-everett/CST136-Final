/***************************************
* Author:    Tyler Sands <ty@tyweb.us>
* License:   MIT
* Filename:  ghast.cpp
* Created:   11/26/2018
* Midiified: 11/26/2018
* Changelog:
* - 11/26/2018 : Create Ghast class from Enemy base
***************************************/
#include "ghast.h"

/* Purpose: Ghast constructor */
Ghast::Ghast() : Enemy("Ghast       ", 25, Enemies::GHAST)
{
}

/* Purpose: Ghast constructor */
Ghast::Ghast(SerializedData & data) : Enemy(data, Enemies::GHAST)
{
}

/* Purpose: Ghast dtor */
Ghast::~Ghast()
{
}

/* Purpose: attack function */
int Ghast::Attack()
{
	return 18;
}