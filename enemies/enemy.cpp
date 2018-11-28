/***************************************
* Author:    Tyler Sands <ty@tyweb.us>
* License:   MIT
* Filename:  enemy.cpp
* Created:   11/26/2018
* Midiified: 11/26/2018
* Changelog:
* - 11/26/2018 : Create enemy class
***************************************/
#include <iostream>
#include <string>
#include "enemy.h"
#include "../string.h"
#include "../serializeddata.h"

using std::cout;
using std::endl;

/* Purpose: Constructor for enemies */
Enemy::Enemy() : m_name("Enemy"), m_health(10)
{
}

/* Purpose: 2arg ctor for enemies */
Enemy::Enemy(String name, int health, int type) : m_name(name), m_health(health), m_type(type)
{
}

/* Purpose: enemy copy ctor */
Enemy::Enemy(const Enemy & obj) : m_name(obj.m_name), m_health(obj.m_health)
{
}

Enemy::Enemy(SerializedData & data, int type) : m_type(type), m_name(data), m_health(0)
{
	char length[10];
	int offset = 0;
	bool loop = true;
	do
	{
		length[offset] = data.ReadCharacter();
		if (length[offset] == '|')
		{
			length[offset] = '\0';
			loop = false;
		}
		offset++;
	} while (loop);
	m_health = atoi(length);
}

/* Purpose: enemy op = */
Enemy & Enemy::operator = (const Enemy & rhs)
{
	if (this != &rhs)
	{
		m_name = rhs.m_name;
		m_health = rhs.m_health;
	}
	return *this;
}

/* Purpose: dtor */
Enemy::~Enemy()
{
}

/* Purpose: Display function */
void Enemy::Display()
{
	cout << "	Type:   " << m_name
		<< "		Health: " << m_health
		<< "		Strength: " << Attack() << endl;
}

/* Purpose: getter */
String & Enemy::GetName()
{
	return m_name;
}

/* Purpose: getter */
int Enemy::GetHealth()
{
	return m_health;
}

/* Purpose: setter */
void Enemy::SetName(String name)
{
	m_name = name;
}

/* Purpose: setter */
void Enemy::SetHealth(int health)
{
	m_health = health;
}

/* Purpose: serialization */
SerializedData Enemy::Serialize()
{
	SerializedData s(std::to_string(m_type).c_str());
	s.Add("|");
	s.Add(m_name.Serialize());
	s.Add(std::to_string(m_health).c_str());
	s.Add("|");
	return s;
}

/* purpose to damage the enemy and do proper health validation */
void Enemy::Damage(int hits)
{
	m_health - hits > 0 ? m_health -= hits : m_health = 0;
}