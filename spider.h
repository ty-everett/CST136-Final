#pragma once
/***************************************
* Author:    Tyler Sands <ty@tyweb.us>
* License:   MIT
* Filename:  spider.h
* Created:   11/28/2018
* Midiified: 11/28/2018
* Changelog:
* - 11/28/2018 : Create Spider from Enemy abstract base class
***************************************/
#include "enemies/enemy.h"
/***************************************
* Class:
*     Spider
* Purpose:
*     Ceepy spider class for fighting characters
***************************************/
class Spider : public Enemy
{
public:
	Spider();
	Spider(SerializedData & data);
	~Spider();
	int Attack();
};

