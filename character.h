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
#include "enemies/enemy.h"

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
	int m_health;
	int m_armor;
	int m_attack;
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
	void FightAttack(Enemy & enemy);
	void FightBlock(Enemy & enemy);
	void FightBerserk(Enemy & enemy);
	void Damage(int damn);
	int GetHealth();
	void SetHealth(int health);
	void SetArmor(int armor);
	void SetAttack(int attack);
};

