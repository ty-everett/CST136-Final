/***************************************
* Author:    Tyler Sands <ty@tyweb.us>
* License:   MIT
* Filename:  character.h
* Created:   11/8/2018
* Midiified: 11/8/2018
* Changelog:
* - 11/8/2018  : Create Character class
***************************************/
#pragma once

#include "String.h"
#include "BackPack.h"
#include "CoinPouch.h"
#include "SerializedData.h"

/***************************************
* Class:
*     Character
* Purpose:
*     Responsible for representing an in-game character and managing associated data
***************************************/
class Character
{
private:
	String m_name;
	BackPack m_backPack;
	CoinPouch m_coinPouch;
public:
	Character();
	Character(SerializedData & data);
	Character(String name, BackPack backPack, CoinPouch coinPouch);
	Character(Character & obj);
	Character & operator = (Character & rhs);
	bool operator == (const Character & rhs) const;
	bool operator != (const Character & rhs) const;
	~Character();
	String GetName();
	BackPack & GetBackPack();
	CoinPouch & GetCoinPouch();
	void SetName(String name);
	void Display();
	SerializedData Serialize();
};

