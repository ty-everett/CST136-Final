#pragma once
/***************************************
* Author:    Tyler Sands <ty@tyweb.us>
* License:   MIT
* Filename:  pig.h
* Created:   11/28/2018
* Midiified: 11/28/2018
* Changelog:
* - 11/28/2018 : Create Pig from Enemy abstract base class
***************************************/
#include "enemies/enemy.h"
/***************************************
* Class:
*     Pig
* Purpose:
*     Pig class for fighting characters
***************************************/
class Pig : public Enemy
{
public:
	Pig();
	Pig(SerializedData & data);
	~Pig();
	int Attack();
};

