/***************************************
* Author:    Tyler Sands <ty@tyweb.us>
* License:   MIT
* Filename:  slime.cpp
* Created:   11/26/2018
* Midiified: 11/26/2018
* Changelog:
* - 11/26/2018 : Create Slime class from Enemy base
***************************************/
#include "slime.h"

/* Purpose: Slime constructor */
Slime::Slime() : Enemy("Slime       ", 50, Enemies::SLIME)
{
}

/* Purpose: Slime constructor */
Slime::Slime(SerializedData & data) : Enemy(data, Enemies::SLIME)
{
}

/* Purpose: Slime dtor */
Slime::~Slime()
{
}

/* Purpose: attack function */
int Slime::Attack()
{
	return 10;
}