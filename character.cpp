/***************************************
* Author:    Tyler Sands <ty@tyweb.us>
* License:   MIT
* Filename:  character
* Created:   11/8/2018
* Midiified: 11/8/2018
* Changelog:
* - 11/8/2018  : Create Character class
***************************************/
#include "Character.h"

#include <iostream>

using std::cout;
using std::endl;

/***************************************
* Purpose:
*     Provides a default constructor for Character objects
* Precondition:
*     A Character object is created with the default constructor
* Postcondition:
*     A default object is constructed. By default the character has an empty
*     BackPack, an empty CoinPouch, and the name "Character".
***************************************/
Character::Character() : m_backPack(), m_coinPouch(), m_name("Character"), m_health(100), m_armor(2), m_attack(5)
{
}

/***************************************
* Purpose:
*     Deserialization constructor
* Precondition:
*     Inflates serialized object
* Postcondition:
*	  Deserialized object is constructed
***************************************/
Character::Character(SerializedData & data) : m_name(data), m_backPack(data), m_coinPouch(data), m_health(0), m_armor(0), m_attack(0)
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
	
	offset = 0;
	loop = true;
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
	m_armor = atoi(length);

	offset = 0;
	loop = true;
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
	m_attack = atoi(length);
}

/***************************************
* Purpose:
*     Constructs a Character object with the given parameters
* Precondition:
*     Character constructor is called with given types (string, BackPack, CoinPouch)
* Postcondition:
*     A new Character is created with appropriate attributes
***************************************/
Character::Character(String name, BackPack backPack, CoinPouch coinPouch) : m_name(name), m_backPack(backPack), m_coinPouch(coinPouch), m_health(100), m_armor(2), m_attack(5)
{
}

/***************************************
* Purpose:
*     Creates a new character with the same attributes of the given character
* Precondition:
*     Called when a copy of a Character object is needed
* Postcondition:
*     A new Character with the same attributes as the provided is generated
***************************************/
Character::Character(Character & obj) : m_name(obj.m_name), m_backPack(obj.m_backPack), m_coinPouch(obj.m_coinPouch), m_health(obj.m_health), m_armor(obj.m_armor), m_attack(obj.m_attack)
{
}

/***************************************
* Purpose:
*     Allows one character's attributes to be assigned to another
* Precondition:
*     Assignment operator called
* Postcondition:
*     Atributes are copies from the right-hand object to the current object
***************************************/
Character & Character::operator = (Character & rhs)
{
	if (this != &rhs)
	{
		m_name = rhs.m_name;
		m_backPack = rhs.m_backPack;
		m_coinPouch = rhs.m_coinPouch;
		m_health = rhs.m_health;
		m_armor = rhs.m_armor;
		m_attack = rhs.m_attack;
	}
	return *this;
}

/***************************************
* Purpose:
*     Compares two Characters for equality
* Precondition:
*     Called during object comparison
* Postcondition:
*     Boolean indicating equality is returned
***************************************/
bool Character::operator == (const Character & rhs) const
{
	bool equal = true;
	if (m_name != rhs.m_name) equal = false;
	if (m_backPack != rhs.m_backPack) equal = false;
	if (m_coinPouch != rhs.m_coinPouch) equal = false;
	return equal;
}

/***************************************
* Purpose:
*     Inverse equality comparison
* Precondition:
*     Inverted comparison between Character objects is made
* Postcondition:
*     Boolean indicating inequality returned
***************************************/
bool Character::operator != (const Character & rhs) const
{
	return *this == rhs ? false : true;
}

/***************************************
* Purpose:
*     Frees dynamic memory allocated in this class
* Precondition:
*     Called when character goes out of scope or when dynamic character deleted
* Postcondition:
*     All dynamic memory is freed (no memory to free so method has no body)
***************************************/
Character::~Character()
{
}

/***************************************
* Purpose:
*     Returns a private data member
* Precondition:
*     The name of Character is needed by consumer
* Postcondition:
*     The character's name is returned
***************************************/
String Character::GetName()
{
	return m_name;
}

/***************************************
* Purpose:
*     Returns Character's BackPack
* Precondition:
*     called by consumer when BackPack is needed
* Postcondition:
*     BackPack returned to consumer
***************************************/
BackPack & Character::GetBackPack()
{
	return m_backPack;
}

/***************************************
* Purpose:
*     Returns Character's CoinPouch
* Precondition:
*     called by consumer when CoinPouch is needed
* Postcondition:
*     CoinPouch returned to consumer
***************************************/
CoinPouch & Character::GetCoinPouch()
{
	return m_coinPouch;
}

/***************************************
* Purpose:
*     Sets character's name
* Precondition:
*     A string is given containing the new name
* Postcondition:
*     The character's name is updated
***************************************/
void Character::SetName(String name)
{
	m_name = name;
}

/***************************************
* Purpose:
*     Prints all data members of the character on stdout
* Precondition:
*     Called by consumer to display character information
* Postcondition:
*     Data printed on stdout
***************************************/
void Character::Display()
{
	cout << "                         Character name: " << m_name << endl << endl;
	cout << "                Health: " << m_health << "	Armor: " << m_armor << "	Attack: " << m_attack << endl << endl;
	m_backPack.PrintInventory();
	m_coinPouch.Display();
}

/***************************************
* Purpose:
*     Serializes a character
* Precondition:
*     A serialized character is needed by an external process (the consumer)
* Postcondition:
*     Serialized Character returned
***************************************/
SerializedData Character::Serialize()
{
	SerializedData s(m_name.Serialize());
	s.Add(m_backPack.Serialize());
	s.Add(m_coinPouch.Serialize());
	s.Add(std::to_string(m_health).c_str());
	s.Add("|");
	s.Add(std::to_string(m_armor).c_str());
	s.Add("|");
	s.Add(std::to_string(m_attack).c_str());
	s.Add("|");
	return s;
}


// TODO isolate attack logic into separate function for code reuse

/* Purpuse: Fight function */
void Character::FightAttack(Enemy & enemy)
{
	cout << "Character attacks " << enemy.GetName() << endl;
	enemy.Damage(m_attack);
	cout << "Character has dealt " << m_attack << " damage to " << enemy.GetName() << endl;
	if (enemy.GetHealth() == 0)
	{
		cout << "Character slays " << enemy.GetName() << endl;
		cout << "Character takes 5 health from the fallen enemy" << endl;
		m_health += 5;
		cout << "Character now has " << m_health << " health!" << endl;
	}
	else
	{
		cout << "Enemy's health is now " << enemy.GetHealth() << endl;
		int damage = (int)((enemy.Attack() * (1 - (m_armor / 10.0f))) + 0.5f);
		Damage(damage);
		cout << enemy.GetName() << " has dealt " << damage << " damage against Character" << endl;
		if (m_health == 0)
		{
			cout << "Character was slain by " << enemy.GetName() << endl;
		}
		else
		{
			cout << "Character now has " << m_health << " health!" << endl;
		}
	}
}

/* Purpose: Blocking move (1.5x armor, 0.5x damage)*/
void Character::FightBlock(Enemy & enemy)
{
	cout << "Character uses block move on " << enemy.GetName() << endl;
	enemy.Damage((int)(m_attack * 0.5f + 0.5f));
	cout << "Character has dealt " << (int)(m_attack * 0.5f + 0.5f) << " damage to " << enemy.GetName() << endl;
	if (enemy.GetHealth() == 0)
	{
		cout << "Character slays " << enemy.GetName() << endl;
		cout << "Character gains 10 health killing enemy with a BLOCKING move!" << endl;
		m_health += 10;
		if (m_armor < 5)
		{
			cout << "Character killed an enemy with defensive move and has less than 5 armor!" << endl;
			cout << "Character has earned 1 armor point!" << endl;
			m_armor++;
			cout << "Character now has " << m_armor << " armor points!" << endl;
		}
		cout << "Character now has " << m_health << " health!" << endl;
	}
	else
	{
		cout << "Enemy's health is now " << enemy.GetHealth() << endl;
		int damage = (int)((enemy.Attack() * (1 - ((m_armor / 10.0f) * 1.5f))) + 0.5f);
		Damage(damage);
		cout << "Enemy has dealt " << damage << " damage against Character!" << endl;
		if (m_health == 0)
		{
			cout << "Character was slain by " << enemy.GetName() << endl;
		}
		else
		{
			cout << "Character now has " << m_health << " health!" << endl;
		}
	}
}

/* Purpose: BERSERK attack (1.5x damage, 0.6x armor) */
void Character::FightBerserk(Enemy & enemy)
{
	cout << "Character uses BERSERK attack move on " << enemy.GetName() << endl;
	enemy.Damage((int)(m_attack * 1.5f + 0.5f));
	cout << "Character has dealt " << (int)(m_attack * 1.5f + 0.5f) << " damage to " << enemy.GetName() << endl;
	if (enemy.GetHealth() == 0)
	{
		cout << "Character slays " << enemy.GetName() << endl;
		cout << "No health benefits from this kill because character used BERSERK attack!" << endl;
		if (m_attack < 49)
		{
			cout << "Character killed an enemy with BERSERK and has less than 40 attack points!" << endl;
			cout << "Character gains 1 attack point!" << endl;
			m_attack++;
			cout << "Character's new number of attack points: " << m_attack << endl;
		}
	}
	else
	{
		cout << "Enemy's health is now " << enemy.GetHealth() << endl;
		int damage = (int)((enemy.Attack() * (1 - ((m_armor / 10.0f) * 0.6f))) + 0.5f);
		Damage(damage);
		cout << enemy.GetName() << " has dealt " << damage << " damage against Character" << endl;
		if (m_health == 0)
		{
			cout << "Character was slain by " << enemy.GetName() << endl;
		}
		else
		{
			cout << "Character now has " << m_health << " health!" << endl;
		}
	}
}


/* purpose to damage character without negative health */
void Character::Damage(int damn)
{
	m_health - damn > 0 ? m_health -= damn : m_health = 0;
}

/* Purpose: To return the health variable. */
int Character::GetHealth()
{
	return m_health;
}

/* Purpose: setter */
void Character::SetHealth(int health)
{
	m_health = health;
}

/* Purpose: setter */
void Character::SetArmor(int armor)
{
	m_armor = armor;
}

/* Purpose: setter */
void Character::SetAttack(int attack)
{
	m_attack = attack;
}