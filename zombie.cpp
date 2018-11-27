/***************************************
* Author:    Tyler Sands <ty@tyweb.us>
* License:   MIT
* Filename:  zombie.cpp
* Created:   11/26/2018
* Midiified: 11/26/2018
* Changelog:
* - 11/26/2018 : Create Zombie class from Enemy base
***************************************/
#include "zombie.h"

/* Purpose: zombie constructor */
Zombie::Zombie() : Enemy("Zombie", 15)
{
}

/* Purpose: zombie dtor */
Zombie::~Zombie()
{
}

/* Purpose: attack function */
int Zombie::Attack()
{
	return 5;
}