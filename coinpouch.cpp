/***************************************
* Author:    Tyler Sands <ty@tyweb.us>
* License:   MIT
* Filename:  backpack.h
* Created:   11/8/2018
* Midiified: 11/8/2018
* Changelog:
* - 11/8/2018  : Create CoinPouch class
***************************************/

#include "CoinPouch.h"

#include <iostream>
#include <string>
#include "SerializedData.h"

using std::cout;
using std::endl;

/***************************************
* Purpose:
*     Constructs a default CoinPouch object
* Precondition:
*     CoinPouch default constructor called
* Postcondition:
*     Default CoinPouch object created. By default no coins are inside.
***************************************/
CoinPouch::CoinPouch() : m_copper(0), m_bronze(0), m_silver(0), m_gold(0)
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
CoinPouch::CoinPouch(SerializedData & data) : m_copper(0), m_bronze(0), m_silver(0), m_gold(0)
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
	m_copper = atoi(length);

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
	m_bronze = atoi(length);

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
	m_silver = atoi(length);

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
	m_gold = atoi(length);
}

/***************************************
* Purpose:
*     Creates a copy of a CoinPouch
* Precondition:
*     A copy of a CoinPouch is needed
* Postcondition:
*     Copy of CoinPouch is constructed with same attributes as the given object
***************************************/
CoinPouch::CoinPouch(CoinPouch & obj) : m_copper(obj.m_copper), m_bronze(obj.m_bronze), m_silver(obj.m_silver), m_gold(obj.m_gold)
{
}

/***************************************
* Purpose:
*     Allows CoinPouch objects to be assigned to one another
* Precondition:
*     called when an assignment is made
* Postcondition:
*     Assigne values from right-hand object to the left-hand object
***************************************/
CoinPouch & CoinPouch::operator = (CoinPouch & rhs)
{
	if (this != &rhs)
	{
		m_copper = rhs.m_copper;
		m_bronze = rhs.m_bronze;
		m_silver = rhs.m_silver;
		m_gold = rhs.m_gold;
	}
	return *this;
}

/***************************************
* Purpose:
*     Compares two objects for equality
* Precondition:
*     Called when comparison is needed (i.e. if statements)
* Postcondition:
*     Boolean indicating equality is returned
***************************************/
bool CoinPouch::operator == (const CoinPouch & rhs) const
{
	bool equal = true;
	if (m_copper != rhs.m_copper) equal = false;
	if (m_bronze != rhs.m_bronze) equal = false;
	if (m_silver != rhs.m_silver) equal = false;
	if (m_gold != rhs.m_gold) equal = false;
	return equal;
}

/***************************************
* Purpose:
*     Inverted comparison operator
* Precondition:
*     Called to check when two CoinPouch objects are not equal
* Postcondition:
*     Boolean indicating inequality os returned
***************************************/
bool CoinPouch::operator != (const CoinPouch & rhs) const
{
	return *this == rhs ? false : true;
}

/***************************************
* Purpose:
*     Destroys a CoinPouch object
* Precondition:
*     Called when object goes out of scope, dynamic object is deleted or explicitly
* Postcondition:
*     BackPack returned to consumer
***************************************/
CoinPouch::~CoinPouch()
{
}

/***************************************
* Purpose:
*     Prints currency values on stdout
* Precondition:
*     Called by consumer to display currency info
* Postcondition:
*     Currency information printed on stdout
***************************************/
void CoinPouch::Display()
{
	cout << "Coin Pouch:" << endl;
	cout << "Copper:  " << m_copper << endl;
	cout << "Bronze:  " << m_bronze << endl;
	cout << "Silver:  " << m_silver << endl;
	cout << "Gold:    " << m_gold << endl << endl;
}

/***************************************
* Purpose:
*     Checks if this CoinPouch has enough money for a given purchase
* Precondition:
*     The amount to check for is given as four integers
* Postcondition:
*     Returns a boolean indicating if enough funds are present
***************************************/
bool CoinPouch::HasEnoughMoney(int copper, int bronze, int silver, int gold)
{
	int totalHave = m_copper, haveGold = m_gold, haveSilver = m_silver, haveBronze = m_bronze;
	while (gold > 0)
	{
		gold--;
		silver += 100;
	}
	while (silver > 0)
	{
		silver--;
		bronze += 100;
	}
	while (bronze > 0)
	{
		bronze--;
		copper += 100;
	}
	while (haveGold > 0)
	{
		haveGold--;
		haveSilver += 100;
	}
	while (haveSilver > 0)
	{
		haveSilver--;
		haveBronze += 100;
	}
	while (haveBronze > 0)
	{
		haveBronze--;
		totalHave += 100;
	}
	return totalHave >= copper;
}

/***************************************
* Purpose:
*     Sets number of coins and then ensures coins are properly combined
* Precondition:
*     Consumer desires to set number of coins
* Postcondition:
*     Number of coins has been set
***************************************/
void CoinPouch::SetCopper(int copper)
{
	m_copper = copper > 0 ? copper : m_copper;
	CombineCoins();
}

/***************************************
* Purpose:
*     Sets number of coins and then ensures coins are properly combined
* Precondition:
*     Consumer desires to set number of coins
* Postcondition:
*     Number of coins has been set
***************************************/
void CoinPouch::SetBronze(int bronze)
{
	m_bronze = bronze > 0 ? bronze : m_bronze;
	CombineCoins();
}

/***************************************
* Purpose:
*     Sets number of coins and then ensures coins are properly combined
* Precondition:
*     Consumer desires to set number of coins
* Postcondition:
*     Number of coins has been set
***************************************/
void CoinPouch::SetSilver(int silver)
{
	m_silver = silver > 0 ? silver : m_silver;
	CombineCoins();
}

/***************************************
* Purpose:
*     Sets number of coins and then ensures coins are properly combined
* Precondition:
*     Consumer desires to set number of coins
* Postcondition:
*     Number of coins has been set
***************************************/
void CoinPouch::SetGold(int gold)
{
	m_gold = gold > 0 ? gold : m_gold;
	CombineCoins();
}

/***************************************
* Purpose:
*     Returns the number of coins present
* Precondition:
*     Consumer desires to know number of coins
* Postcondition:
*     Number of coins returned for the given category
***************************************/
int CoinPouch::GetCopper() const
{
	return m_copper;
}

/***************************************
* Purpose:
*     Returns the number of coins present
* Precondition:
*     Consumer desires to know number of coins
* Postcondition:
*     Number of coins returned for the given category
***************************************/
int CoinPouch::GetBronze() const
{
	return m_bronze;
}

/***************************************
* Purpose:
*     Returns the number of coins present
* Precondition:
*     Consumer desires to know number of coins
* Postcondition:
*     Number of coins returned for the given category
***************************************/
int CoinPouch::GetSilver() const
{
	return m_silver;
}

/***************************************
* Purpose:
*     Returns the number of coins present
* Precondition:
*     Consumer desires to know number of coins
* Postcondition:
*     Number of coins returned for the given category
***************************************/
int CoinPouch::GetGold() const
{
	return m_gold;
}

/***************************************
* Purpose:
*     Adds more coins to a category and then combines all coins
* Precondition:
*     Coins need to be added for a particular category
* Postcondition:
*     Coins have been added and combined
***************************************/
void CoinPouch::AddCopper(int copper)
{
	m_copper += copper > 0 ? copper : 0;
	CombineCoins();
}

/***************************************
* Purpose:
*     Adds more coins to a category and then combines all coins
* Precondition:
*     Coins need to be added for a particular category
* Postcondition:
*     Coins have been added and combined
***************************************/
void CoinPouch::AddBronze(int bronze)
{
	m_bronze += bronze > 0 ? bronze : 0;
	CombineCoins();
}

/***************************************
* Purpose:
*     Adds more coins to a category and then combines all coins
* Precondition:
*     Coins need to be added for a particular category
* Postcondition:
*     Coins have been added and combined
***************************************/
void CoinPouch::AddSilver(int silver)
{
	m_silver += silver > 0 ? silver : 0;
	CombineCoins();
}

/***************************************
* Purpose:
*     Adds more coins to a category and then combines all coins
* Precondition:
*     Coins need to be added for a particular category
* Postcondition:
*     Coins have been added and combined
***************************************/
void CoinPouch::AddGold(int gold)
{
	m_gold += gold > 0 ? gold : 0;
	CombineCoins();
}

/***************************************
* Purpose:
*     Combines coins such that there are no more than 100 of lower denominations
* Precondition:
*     Coins need to be combined after values have been changed
* Postcondition:
*     Coins have been combined
***************************************/
void CoinPouch::CombineCoins()
{
	while (m_copper >= 100)
	{
		m_copper -= 100;
		m_bronze++;
	}
	while (m_bronze >= 100)
	{
		m_bronze -= 100;
		m_silver++;
	}
	while (m_silver >= 100)
	{
		m_silver -= 100;
		m_gold++;
	}
}

/***************************************
* Purpose:
*     Serialize a CoinPouch into binary format
* Precondition:
*     A CoinPouch neeeds serializing
* Postcondition:
*     Serialized CoinPouch is returned
***************************************/

SerializedData CoinPouch::Serialize()
{
	SerializedData s(std::to_string(m_copper).c_str());
	s.Add("|");
	s.Add(std::to_string(m_bronze).c_str());
	s.Add("|");
	s.Add(std::to_string(m_silver).c_str());
	s.Add("|");
	s.Add(std::to_string(m_gold).c_str());
	s.Add("|");
	return s;
}