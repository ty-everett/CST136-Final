#pragma once
/***************************************
* Author:    Tyler Sands <ty@tyweb.us>
* License:   MIT
* Filename:  creeper.h
* Created:   11/28/2018
* Midiified: 11/28/2018
* Changelog:
* - 11/28/2018 : Create Skeleton from Enemy abstract base class
***************************************/
#include "enemies/enemy.h"
/***************************************
* Class:
*     Creeper
* Purpose:
*     Creeper class for blowing up characters
***************************************/
class Creeper : public Enemy
{
public:
	Creeper();
	Creeper(SerializedData & data);
	~Creeper();
	int Attack();
};

