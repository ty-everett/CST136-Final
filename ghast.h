#pragma once
/***************************************
* Author:    Tyler Sands <ty@tyweb.us>
* License:   MIT
* Filename:  ghast.h
* Created:   11/28/2018
* Midiified: 11/28/2018
* Changelog:
* - 11/28/2018 : Create Ghast from Enemy abstract base class
***************************************/
#include "enemies/enemy.h"
/***************************************
* Class:
*     Ghast
* Purpose:
*     Ghast class for fighting characters
***************************************/
class Ghast : public Enemy
{
public:
	Ghast();
	Ghast(SerializedData & data);
	~Ghast();
	int Attack();
};

