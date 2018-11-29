#pragma once
/***************************************
* Author:    Tyler Sands <ty@tyweb.us>
* License:   MIT
* Filename:  slime.h
* Created:   11/28/2018
* Midiified: 11/28/2018
* Changelog:
* - 11/28/2018 : Create Slime from Enemy abstract base class
***************************************/
#include "enemies/enemy.h"
/***************************************
* Class:
*     Slime
* Purpose:
*     Slime class for fighting characters
***************************************/
class Slime : public Enemy
{
public:
	Slime();
	Slime(SerializedData & data);
	~Slime();
	int Attack();
};

