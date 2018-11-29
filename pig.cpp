/***************************************
* Author:    Tyler Sands <ty@tyweb.us>
* License:   MIT
* Filename:  pig.cpp
* Created:   11/26/2018
* Midiified: 11/26/2018
* Changelog:
* - 11/26/2018 : Create Pig class from Enemy base
***************************************/
#include "pig.h"

/* Purpose: Pig constructor */
Pig::Pig() : Enemy("Pig         ", 20, Enemies::PIG)
{
}

/* Purpose: Pig constructor */
Pig::Pig(SerializedData & data) : Enemy(data, Enemies::PIG)
{
}

/* Purpose: Pig dtor */
Pig::~Pig()
{
}

/* Purpose: attack function */
int Pig::Attack()
{
	return 4;
}