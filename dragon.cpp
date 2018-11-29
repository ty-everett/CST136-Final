/***************************************
* Author:    Tyler Sands <ty@tyweb.us>
* License:   MIT
* Filename:  dragon.cpp
* Created:   11/26/2018
* Midiified: 11/26/2018
* Changelog:
* - 11/26/2018 : Create Dragon class from Enemy base
***************************************/
#include "Dragon.h"

/* Purpose: Dragon constructor */
Dragon::Dragon() : Enemy("Dragon      ", 100, Enemies::DRAGON)
{
}

/* Purpose: Dragon constructor */
Dragon::Dragon(SerializedData & data) : Enemy(data, Enemies::DRAGON)
{
}

/* Purpose: Dragon dtor */
Dragon::~Dragon()
{
}

/* Purpose: attack function */
int Dragon::Attack()
{
	return 50;
}