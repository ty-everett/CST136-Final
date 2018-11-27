/***************************************
* Author:    Tyler Sands <ty@tyweb.us>
* License:   MIT
* Filename:  backpack.cpp
* Created:   11/7/2018
* Midiified: 11/8/2018
* Changelog:
* - 11/7/2018  : Create BackPack class
***************************************/

#include "BackPack.h"

#include "SerializedData.h"

#include <iostream>
#include "Potion.h"

using std::cout;
using std::cin;
using std::endl;

/***************************************
* Purpose:
*     Provide a default constructor for BackPack objects
* Precondition:
*     Default constructor called
* Postcondition:
*     Default object created. Empty DynamicArray object generated.
*     By default the BackPack object is empty upon creation.
***************************************/
BackPack::BackPack() : m_potionArray()
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
BackPack::BackPack(SerializedData & data) : m_potionArray(data)
{
}

/***************************************
* Purpose:
*     Allow for copies of BackPack objects to be made
* Precondition:
*     Called when a copy of an existing object is needed
* Postcondition:
*     A copy of an object is created with the same members as the provided object
***************************************/
BackPack::BackPack(BackPack & obj) : m_potionArray()
{
	m_potionArray = obj.m_potionArray;
}

/***************************************
* Purpose:
*     Allows for assignment of existing objects.
* Precondition:
*     Operator = called during assignment
* Postcondition:
*     Data in left-hand object is replaced with the data in the right-hand object
***************************************/
BackPack & BackPack::operator = (BackPack & rhs)
{
	if (this != &rhs)
	{
		m_potionArray = rhs.m_potionArray;
	}
	return *this;
}

/***************************************
* Purpose:
*     Checks two objects for equality
* Precondition:
*     A comparison of objects is performed 
* Postcondition:
*     A boolean is returned indicating equality
***************************************/
bool BackPack::operator == (const BackPack & rhs) const
{
	return m_potionArray == rhs.m_potionArray;
}

/***************************************
* Purpose:
*     Provides negative comparison of two objects
* Precondition:
*     A negative comparison is made to check if two objects are not equal
* Postcondition:
*     A boolean indicating inequality is returned.
***************************************/
bool BackPack::operator != (const BackPack & rhs) const
{
	return m_potionArray != rhs.m_potionArray;
}

/***************************************
* Purpose:
*     Adds an item to the BackPack
* Precondition:
*     An item is given which will be added
* Postcondition:
*     The item is added to the BackPack's DynamicArray
***************************************/
void BackPack::AddItem(Potion item)
{
	m_potionArray.Insert(item);
}

/***************************************
* Purpose:
*     Deletes an item given its index
* Precondition:
*     Index of item to purge is given
* Postcondition:
*     Item is purged from BackPack
***************************************/
void BackPack::DeleteItem(int index)
{
	m_potionArray.Delete(m_potionArray[index]);
}

/***************************************
* Purpose:
*     Prints all items in BackPack
* Precondition:
*     Called by consumer of BackPack object
* Postcondition:
*     All BackPack items are printed
***************************************/
void BackPack::PrintInventory()
{
	cout << "Items in BackPack (" << m_potionArray.GetLength() << "):" << endl;
	for (int i = 0, l = m_potionArray.GetLength(); i < l; i++)
	{
		cout << "Item index: " << i << endl;
		m_potionArray[i].Display();
	}
	cout << endl;
}

/***************************************
* Purpose:
*     Returns the number of items in the BackPack
* Precondition:
*     Called by consumer
* Postcondition:
*     Number of items is returned
***************************************/
int BackPack::GetLength()
{
	return m_potionArray.GetLength();
}

/***************************************
* Purpose:
*     Destroys a BackPack object
* Precondition:
*     BackPack goes out of scope, dynamic object is deleted or destructor called.
* Postcondition:
*     BackPack object dynamic memory is freed (no dynamic memory to free)
***************************************/
BackPack::~BackPack()
{
}

/***************************************
* Purpose:
*     Serializes a BackPack
* Precondition:
*     Required during File IO
* Postcondition:
*     Serialized object returned
***************************************/
SerializedData BackPack::Serialize()
{
	return m_potionArray.Serialize();
}