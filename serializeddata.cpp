/***************************************
* Author:    Tyler Sands <ty@tyweb.us>
* License:   MIT
* Filename:  serializeddata.cpp
* Created:   11/10/2018
* Midiified: 11/10/2018
* Changelog:
* - 11/10/2018: Create the class
***************************************/
#define _CRT_SECURE_NO_WARNINGS
#include "SerializedData.h"
#include <cstring>

/***************************************
* Purpose:
*     Construct a serialized object
* Precondition:
*     A serialized object is needed
* Postcondition:
*     A serialized object is created
***************************************/
SerializedData::SerializedData(const char * data) : m_data(nullptr), m_position(0)
{
	m_data = new char[strlen(data) + 1];
	strcpy(m_data, data);
}

/***************************************
* Purpose:
*     Copy constructor
* Precondition:
*     called when copy is needed
* Postcondition:
*     copy is made
***************************************/
SerializedData::SerializedData(SerializedData & obj) : m_data(nullptr), m_position(0)
{
	m_data = new char[strlen(obj.m_data) + 1];
	strcpy(m_data, obj.m_data);
	m_position = obj.m_position;
}

/***************************************
* Purpose:
*     Converts a serialized object to const char *
* Precondition:
*     Needed for explicit type conversions
* Postcondition:
*     type is converted
***************************************/
SerializedData::operator const char * ()
{
	return m_data;
}

/***************************************
* Purpose:
*     Converts a serialized object to char *
* Precondition:
*     Needed for explicit type conversions
* Postcondition:
*     type is converted
***************************************/
SerializedData::operator char * ()
{
	return m_data;
}

/***************************************
* Purpose:
*     provides the length of the buffer in a convenient manner
* Precondition:
*     required when passing to fstream.write during file I/O operations
* Postcondition:
*     Length of buffer returned
***************************************/
SerializedData::operator int()
{
	return strlen(m_data);
}

/***************************************
* Purpose:
*     frees dynamic memory
* Precondition:
*     object goes out of scopee or is no longer needed
* Postcondition:
*     buffer is destroyed
***************************************/
SerializedData::~SerializedData()
{
	delete[] m_data;
}

/***************************************
* Purpose:
*     Useful for concatonating multiple serialized data members
* Precondition:
*     A second buffer is given to be concatonated
* Postcondition:
*     concat is performed
***************************************/
void SerializedData::Add(const char * str)
{
	int oldLength = strlen(m_data) + 1;
	int newLength = oldLength + strlen(str);
	char * old = new char[oldLength];
	strcpy(old, m_data);
	delete[] m_data;
	m_data = new char[newLength];
	int index;
	for (index = 0; index < oldLength - 1; index++)
	{
		*(m_data + index) = *(old + index);
	}
	while (index < newLength)
	{
		*(m_data + index) = *(str + (index - (oldLength - 1)));
		index++;
	}
	delete[] old;
}

/***************************************
* Purpose:
*     Reads character at index and then imcrements index
* Precondition:
*     Used when iterating over serializedData during deserialization
* Postcondition:
*     char at index returned, position marker updated
***************************************/
char SerializedData::ReadCharacter()
{
	m_position++;
	if (m_position > strlen(m_data))
	{
		return '\0';
	}
	else
	{
		return m_data[m_position - 1];
	}
}