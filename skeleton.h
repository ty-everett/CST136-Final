#pragma once
/***************************************
* Author:    Tyler Sands <ty@tyweb.us>
* License:   MIT
* Filename:  skeleton.h
* Created:   11/28/2018
* Midiified: 11/28/2018
* Changelog:
* - 11/28/2018 : Create Skeleton from Enemy abstract base class
***************************************/
#include "enemies/enemy.h"
/***************************************
* Class:
*     Skeleton
* Purpose:
*     Skeleton class for fighting characters
***************************************/
class Skeleton : public Enemy
{
public:
	Skeleton();
	Skeleton(SerializedData & data);
	~Skeleton();
	int Attack();
};

