/***************************************
* Author:    Tyler Sands <ty@tyweb.us>
* License:   MIT
* Filename:  enemy.h
* Created:   11/20/2018
* Midiified: 11/20/2018
* Changelog:
* - 11/26/2018 : enemy class create
***************************************/
#pragma once

#include "../string.h"

// define an identifier for each type of enemy
enum Enemies {
	ZOMBIE,
	SKELETON,
	SPIDER,
	CREEPER,
	PIGMAN,
	PIG,
	VILLAGER,
	DRAGON,
	GHAST,
	SLIME
};

/***************************************
* Class:
*     Enemy
* Purpose:
*     Provide an abstract interface for enemies so they can go in arrays
***************************************/
class Enemy
{
private:
	String m_name;
	int m_health;
	int m_type;
public:
	Enemy();
	Enemy(String name, int health, int type);
	Enemy(const Enemy & obj);
	Enemy(SerializedData & data, int type);
	Enemy & operator = (const Enemy & rhs);
	~Enemy();
	void Display();
	virtual int Attack() = 0;
	String & GetName();
	int GetHealth();
	void SetName(String name);
	void SetHealth(int health);
	SerializedData Serialize();
	void Damage(int hits);
};

