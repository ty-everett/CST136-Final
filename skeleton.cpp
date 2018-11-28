/***************************************
* Author:    Tyler Sands <ty@tyweb.us>
* License:   MIT
* Filename:  skeleton.cpp
* Created:   11/26/2018
* Midiified: 11/26/2018
* Changelog:
* - 11/26/2018 : Create Skeleton class from Enemy base
***************************************/
#include "skeleton.h"

/* Purpose: Skeleton constructor */
Skeleton::Skeleton() : Enemy("Skeleton", 10, Enemies::SKELETON)
{
}

/* Purpose: Skeleton constructor */
Skeleton::Skeleton(SerializedData & data) : Enemy(data, Enemies::SKELETON)
{
}

/* Purpose: Skeleton dtor */
Skeleton::~Skeleton()
{
}

/* Purpose: attack function */
int Skeleton::Attack()
{
	return 9;
}