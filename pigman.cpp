/***************************************
* Author:    Tyler Sands <ty@tyweb.us>
* License:   MIT
* Filename:  pigman.cpp
* Created:   11/26/2018
* Midiified: 11/26/2018
* Changelog:
* - 11/26/2018 : Create Pigman class from Enemy base
***************************************/
#include "pigman.h"

/* Purpose: Pigman constructor */
Pigman::Pigman() : Enemy("Pigman      ", 20, Enemies::PIGMAN)
{
}

/* Purpose: Pigman constructor */
Pigman::Pigman(SerializedData & data) : Enemy(data, Enemies::PIGMAN)
{
}

/* Purpose: Pigman dtor */
Pigman::~Pigman()
{
}

/* Purpose: attack function */
int Pigman::Attack()
{
	return 14;
}