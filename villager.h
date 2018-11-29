#pragma once
/***************************************
* Author:    Tyler Sands <ty@tyweb.us>
* License:   MIT
* Filename:  villager.h
* Created:   11/28/2018
* Midiified: 11/28/2018
* Changelog:
* - 11/28/2018 : Create Villager from Enemy abstract base class
***************************************/
#include "enemies/enemy.h"
/***************************************
* Class:
*     Villager
* Purpose:
*     Villager class for fighting characters
***************************************/
class Villager : public Enemy
{
public:
	Villager();
	Villager(SerializedData & data);
	~Villager();
	int Attack();
};

