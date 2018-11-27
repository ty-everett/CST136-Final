#pragma once
/***************************************
* Author:    Tyler Sands <ty@tyweb.us>
* License:   MIT
* Filename:  zombie.h
* Created:   11/20/2018
* Midiified: 11/20/2018
* Changelog:
* - 11/20/2018 : Create Zombie from Enemy abstract base class
***************************************/
#include "enemies/enemy.h"
/***************************************
* Class:
*     Zombie
* Purpose:
*     Zombie class for fighting characters
***************************************/
class Zombie : public Enemy
{
public:
	Zombie();
	~Zombie();
	int Attack();
};

