/***************************************
* Author:    Tyler Sands <ty@tyweb.us>
* License:   MIT
* Filename:  spider.cpp
* Created:   11/26/2018
* Midiified: 11/26/2018
* Changelog:
* - 11/28/2018 : Create Spider class from Enemy base
***************************************/
#include "spider.h"

/* Purpose: Spider constructor */
Spider::Spider() : Enemy("Spider      ", 6, Enemies::SPIDER)
{
}

/* Purpose: Spider constructor */
Spider::Spider(SerializedData & data) : Enemy(data, Enemies::SPIDER)
{
}

/* Purpose: Spider dtor */
Spider::~Spider()
{
}

/* Purpose: attack function */
int Spider::Attack()
{
	return 11;
}