/***************************************
* Author:    Tyler Sands <ty@tyweb.us>
* License:   MIT
* Filename:  dynamicarray.cpp
* Created:   10/16/2018
* Midiified: 10/16/2018
* Changelog:
* - 10/16/2018: Create the file
* - 11/2/2018:  Remove debug output
***************************************/
#include "DynamicArray.h"

#include <iostream>
#include <new>
#include "SerializedData.h"

using std::cout;
using std::endl;
using std::bad_alloc;

/***************************************
* Purpose:
*     Constructs a dynamic array
* Precondition:
*     Dynamic array constructor is called
* Postcondition:
*     Dynamic array is created with no data
***************************************/
DynamicArray::DynamicArray() : m_length(0), m_arr(nullptr)
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
DynamicArray::DynamicArray(SerializedData & data) : m_arr(nullptr), m_length(0)
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
	m_length = atoi(length);
	m_arr = new Potion[m_length];
	int i;
	for (i = 0; i < m_length; i++)
	{
		*(m_arr + i) = Potion(data);
	}
}

/***************************************
* Purpose:
*     Finds the index of a given element of the array
* Precondition:
*     The element who's index is needed is provided
* Postcondition:
*     The provided element's index is returned, or -1 if it was not found.
***************************************/
int DynamicArray::Find(const Potion & target)
{
	int index = -1;
	for (int i = 0; i < m_length; i++)
	{
		if (m_arr[i] == target)
		{
			index = i;
		}
	}
	return index;
}

/***************************************
* Purpose:
*     Creates a copy of the provided dynamic array
* Precondition:
*     The array to be copied is given
* Postcondition:
*     A copy of the given array is made
***************************************/
DynamicArray::DynamicArray(const DynamicArray & obj) : m_length(obj.m_length), m_arr(nullptr)
{
	try
	{
		m_arr = new Potion[m_length];
	}
	catch (bad_alloc e)
	{
		throw;
	}
	for (int i = 0; i < m_length; i++)
	{
		m_arr[i] = Potion(obj.m_arr[i]);
	}
}

/***************************************
* Purpose:
*     Sets the current dynamic array equal to another
* Precondition:
*     The array to be set equal to is given
* Postcondition:
*     The contents of the current array are purged and eplaced with the given array
***************************************/
DynamicArray & DynamicArray::operator = (const DynamicArray & rhs)
{
	if (this != &rhs)
	{
		delete[] m_arr;
		m_length = rhs.m_length;
		try {
			m_arr = new Potion[m_length];
		}
		catch (bad_alloc e) {
			throw;
		}
		for (int i = 0; i < m_length; i++)
		{
			m_arr[i] = Potion(rhs.m_arr[i]);
		}
	}
	return *this;
}

/***************************************
* Purpose:
*     Adds an element to the dynamic array
* Precondition:
*     the element to be added is given
* Postcondition:
*     The element is appended to the array
***************************************/
void DynamicArray::Insert(const Potion & data)
{
	m_length++;
	try {
		Potion * temp = new Potion[m_length];
		for (int i = 0; i < m_length - 1; i++)
		{
			temp[i] = m_arr[i];
		}
		temp[m_length - 1] = data;
		delete[] m_arr;
		m_arr = temp;
	}
	catch (bad_alloc e) {
		throw;
	}
}

/***************************************
* Purpose:
*     Deletes a given element from the array
* Precondition:
*     Element to be deleted is given
* Postcondition:
*     Element has ben deleted from the array
***************************************/
void DynamicArray::Delete(const Potion & data)
{
	int index = Find(data);
	if (index != -1)
	{
		m_length--;
		try {
			Potion * new_arr = new Potion[m_length];
			for (int i = 0; i < index; i++)
			{
				new_arr[i] = Potion(m_arr[i]);
			}
			for (int i = index + 1; i < m_length; i++)
			{
				new_arr[i - 1] = Potion(m_arr[i]);
			}
			delete[] m_arr;
			m_arr = new_arr;
		}
		catch (bad_alloc e) {
			throw;
		}
	}
}

/***************************************
* Purpose:
*     Returns element from array at given index
* Precondition:
*     The element index is given
* Postcondition:
*     The element is returned
***************************************/
Potion & DynamicArray::operator [] (int index)
{
	return m_arr[index];
}

/***************************************
* Purpose:
*     Compare DynamicArrays for equality
* Precondition:
*     Called during object comparison
* Postcondition:
*     Boolean indicating equality
***************************************/
bool DynamicArray::operator == (const DynamicArray & rhs) const
{
	if (m_length != rhs.m_length)
	{
		return false;
	}
	else 
	{
		bool equal = true;
		for (int i = 0; i < m_length && i < rhs.m_length && equal == true; i++)
		{
			if (m_arr[i] != rhs.m_arr[i])
			{
				equal = false;
			}
		}
		return equal;
	}
}

/***************************************
* Purpose:
*     Compare DynamicArrays for equality
* Precondition:
*     Called during object comparison
* Postcondition:
*     Boolean indicating equality
***************************************/
bool DynamicArray::operator != (const DynamicArray & rhs) const
{
	return *this == rhs ? false : true;
}

/***************************************
* Purpose:
*     Deletes a dynamic array
* Precondition:
*     Array goes out of scope or delete[] is called on dynamic array
* Postcondition:
*     DMemoy reserved by the array is freed
***************************************/
DynamicArray::~DynamicArray()
{
	delete[] m_arr;
}

/***************************************
* Purpose:
*     Returns the number of elements in the array
* Precondition:
*     called by consumer
* Postcondition:
*     number of elements is returned
***************************************/
int DynamicArray::GetLength() const
{
	return m_length;
}

/***************************************
* Purpose:
*     Displays the elements in the array
* Precondition:
*     called by consumer
* Postcondition:
*     Contents of the array have been printed on stdout
***************************************/
void DynamicArray::Display() const
{
	cout << "   ==========[ DISPLAYING ARRAY ]==========" << endl;
	for (int i = 0; i < m_length; i++)
	{
		cout << "Potion" << i << ":" << endl;
		m_arr[i].Display();
	}
	cout << "   ==========[  END ARRAY DUMP  ]==========" << endl;
}

/***************************************
* Purpose:
*     Serialize a DynamicArray
* Precondition:
*     A serialized copy of a DynamicArray is needed, for example during file i/o
* Postcondition:
*     Serialized DynamicArray object is returned
***************************************/
SerializedData DynamicArray::Serialize()
{
	SerializedData s(std::to_string(GetLength()).c_str());
	s.Add("|");
	for (int i = 0, l = GetLength(); i < l; i++)
	{
		s.Add(m_arr[i].Serialize());
	}
	return s;
}