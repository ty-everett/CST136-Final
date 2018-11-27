/***************************************
* Author:    Tyler Sands <ty@tyweb.us>
* License:   MIT
* Filename:  potion.h
* Created:   10/1/2018
* Midiified: 10/3/2018
* Changelog:
* - 10/1/2018: Define variables, getters/setters and manager functions
* - 10/3/2018: Add SimplifyCost helper function definition
* - 10/9/2018: Updated to use internal String class
***************************************/
#pragma once

#include <iostream>
#include <string>

#include "String.h"
#include "SerializedData.h"

using std::cout;
using std::endl;

/***************************************
* Class:
*     Potion
* Purpose: 
*     Stores and manages data relating to Potions, as defined by the Lab 1
*     instructions.
***************************************/
class Potion
{
private:
	String m_name;
	String m_description;
	String m_potency;
	String m_cost;
	String SimplifyCost(const String cost);
public:
	Potion();
	Potion(SerializedData & data);
	Potion(String name, String description, String potency, String cost);
	Potion(const Potion & obj);
	Potion & operator = (const Potion & rhs);
	bool operator == (const Potion & rhs) const;
	bool operator != (const Potion & rhs) const;
	void Display() const;
	~Potion();
	String GetName() const;
	String GetDescription() const;
	String GetPotency() const;
	String GetCost() const;
	void SetName(const String name);
	void SetDescription(const String description);
	void SetPotency(const String potency);
	void SetCost(const String cost);
	SerializedData Serialize();
};

