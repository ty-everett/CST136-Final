/***************************************
* Author:    Tyler Sands <ty@tyweb.us>
* License:   MIT
* Filename:  villager.cpp
* Created:   11/26/2018
* Midiified: 11/26/2018
* Changelog:
* - 11/26/2018 : Create Villager class from Enemy base
***************************************/
#include "Villager.h"

/* Purpose: Villager constructor */
Villager::Villager() : Enemy("Villager    ", 50, Enemies::VILLAGER)
{
}

/* Purpose: Villager constructor */
Villager::Villager(SerializedData & data) : Enemy(data, Enemies::VILLAGER)
{
}

/* Purpose: Villager dtor */
Villager::~Villager()
{
}

/* Purpose: attack function */
int Villager::Attack()
{
	return 20;
}