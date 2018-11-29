#pragma once
/***************************************
* Author:    Tyler Sands <ty@tyweb.us>
* License:   MIT
* Filename:  pigman.h
* Created:   11/28/2018
* Midiified: 11/28/2018
* Changelog:
* - 11/28/2018 : Create Pigman from Enemy abstract base class
***************************************/
#include "enemies/enemy.h"
/***************************************
* Class:
*     Pigman
* Purpose:
*     Pigman class for fighting characters
***************************************/
class Pigman : public Enemy
{
public:
	Pigman();
	Pigman(SerializedData & data);
	~Pigman();
	int Attack();
};

