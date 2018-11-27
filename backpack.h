/***************************************
* Author:    Tyler Sands <ty@tyweb.us>
* License:   MIT
* Filename:  backpack.h
* Created:   11/7/2018
* Midiified: 11/8/2018
* Changelog:
* - 11/7/2018  : Create BackPack class
***************************************/

#pragma once

#include "DynamicArray.h"
#include "SerializedData.h"

/***************************************
* Class:
*     BackPack
* Purpose:
*     Responsible for maintaining an array of Potions for use with the Character.
***************************************/

class BackPack
{
private:
	DynamicArray m_potionArray;
public:
	BackPack();
	BackPack(SerializedData & data);
	BackPack(BackPack & obj);
	BackPack & operator = (BackPack & rhs);
	bool operator == (const BackPack & rhs) const;
	bool operator != (const BackPack & rhs) const;
	void AddItem(Potion item);
	void DeleteItem(int index);
	void PrintInventory();
	int GetLength();
	~BackPack();
	SerializedData Serialize();
};

