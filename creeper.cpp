/***************************************
* Author:    Tyler Sands <ty@tyweb.us>
* License:   MIT
* Filename:  creeper.cpp
* Created:   11/26/2018
* Midiified: 11/26/2018
* Changelog:
* - 11/26/2018 : Create creeper class from Enemy base
***************************************/
#include "creeper.h"

/* Purpose: Creeper constructor */
Creeper::Creeper() : Enemy("Creeper    ", 16, Enemies::CREEPER)
{
}

/* Purpose: Creeper constructor */
Creeper::Creeper(SerializedData & data) : Enemy(data, Enemies::CREEPER)
{
}

/* Purpose: Creeper dtor */
Creeper::~Creeper()
{
}

/* Purpose: attack function */
int Creeper::Attack()
{
	return 16;
}