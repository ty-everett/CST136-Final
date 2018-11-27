/***************************************
* Author:    Tyler Sands <ty@tyweb.us>
* License:   MIT
* Filename:  dynamicarray.h
* Created:   10/16/2018
* Midiified: 10/16/2018
* Changelog:
* - 10/16/2018: Create the file
***************************************/
#pragma once

#include "Potion.h"
#include "SerializedData.h"

/***************************************
* Class:
*     DynamicArray
* Purpose:
*     Manages a set of potions, allowing for them to be dynamically added and removed
***************************************/
class DynamicArray
{
private:
	Potion * m_arr;
	int m_length;
	int Find(const Potion & target);
public:
	DynamicArray();
	DynamicArray(SerializedData & data);
	DynamicArray(const DynamicArray & obj);
	DynamicArray & operator = (const DynamicArray & rhs);
	Potion & operator [] (int index);
	bool operator == (const DynamicArray & rhs) const;
	bool operator != (const DynamicArray & rhs) const;
	void Insert(const Potion & data);
	void Delete(const Potion & data);
	~DynamicArray();
	int GetLength() const;
	void Display() const;
	SerializedData Serialize();
};

