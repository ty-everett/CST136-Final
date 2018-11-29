#pragma once
/***************************************
* Author:    Tyler Sands <ty@tyweb.us>
* License:   MIT
* Filename:  dragon.h
* Created:   11/28/2018
* Midiified: 11/28/2018
* Changelog:
* - 11/28/2018 : Create Dragon from Enemy abstract base class
***************************************/
#include "enemies/enemy.h"
/***************************************
* Class:
*     Dragon
* Purpose:
*     Dragon class for fighting characters
***************************************/
class Dragon : public Enemy
{
public:
	Dragon();
	Dragon(SerializedData & data);
	~Dragon();
	int Attack();
};

