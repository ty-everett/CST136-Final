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
#include "enemy.h"
#include "../string.h"

using std::cout;
using std::endl;

/* Purpose: Constructor for enemies */
Enemy::Enemy() : m_name("Enemy"), m_health(10)
{
}

/* Purpose: 2arg ctor for enemies */
Enemy::Enemy(String name, int health) : m_name(name), m_health(health)
{
}

/* Purpose: enemy copy ctor */
Enemy::Enemy(const Enemy & obj) : m_name(obj.m_name), m_health(obj.m_health)
{
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
	cout << "Name:   " << m_name << endl
		<< "Health: " << m_health << endl;
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