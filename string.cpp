/***************************************
* Author:    Tyler Sands <ty@tyweb.us>
* License:   MIT
* Filename:  String.cpp
* Created:   10/4/2018
* Midiified: 10/10/2018
* Changelog:
* - 10/9/2018:  Implement operator +=
* - 10/10/2018: Add documentation to existing implementation
* - 11/7/2018:  Remove debug printing and adapt for lab 4
***************************************/
#include "String.h"

#include <iostream>
#include <cstring>
#include <string>

using std::cout;
using std::endl;

/***************************************
* Purpose:
*     Constructs a String object with no data. Default for empty strings is " "
* Precondition:
*     String constructor is called with no arguments
* Postcondition:
*     A new String with no data is created
***************************************/
String::String() : m_data(nullptr)
{
	CopyCharArray(m_data, " ");
}

/***************************************
* Purpose:
*     Deserialization constructor
* Precondition:
*     Inflates serialized object
* Postcondition:
*	  Deserialized object is constructed
***************************************/
String::String(SerializedData & data) : m_data(nullptr)
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
	int l = atoi(length);
	m_data = new char[l + 1];
	int i;
	for (i = 0; i < l; i++)
	{
		*(m_data + i) = data.ReadCharacter();
	}
	*(m_data + i) = '\0';
}

/***************************************
* Purpose:
*     Constructs a String object given a null-terminated character array.
* Precondition:
*     String constructor is called with 1 argument
* Postcondition:
*     A new String with the given data is created
***************************************/
String::String(const char * str) : m_data(nullptr)
{
	CopyCharArray(m_data, str);
}

/***************************************
* Purpose:
*     Initializes a new string with the data from an existing
*     string, given the existing string as an argument
* Precondition:
*     String copy constructor is called (pass/return byval, etc)
* Postcondition:
*     A copy of the existing string is made and stored in a new string
***************************************/
String::String(const String & obj) : m_data(nullptr)
{
	CopyCharArray(m_data, obj.m_data);
}

/***************************************
* Purpose:
*     Sets this string to the value of another string (assignment)
* Precondition:
*     The assignment operator is used on two strings
* Postcondition:
*     this ( actually, *this :) ) string is replaced with the
*     content of the right-hand string.
***************************************/
String & String::operator = (const String & rhs)
{
	if (this != &rhs)
	{
		CopyCharArray(m_data, rhs.m_data);
	}
	return *this;
}

/***************************************
* Purpose:
*     Allows for a string to be assigned a new value directly from
*     an array of characters.
* Precondition:
*     Assignment operator used with String and const char *
* Postcondition:
*     The current string's value is replaced with the content of
*     the character array on the right hand side.
***************************************/
String & String::operator = (const char * rhs)
{
	CopyCharArray(m_data, rhs);
	return *this;
}

/***************************************
* Purpose:
*     Adds the value of the right-hand char array to the end
*     of the current string
* Precondition:
*     the += operator is used
* Postcondition:
*     The character array has been appended to the string.
***************************************/
String & String::operator += (const char * rhs)
{
	int oldLength = FindCharArrayLength(m_data);
	int newLength = oldLength + FindCharArrayLength(rhs);
	char * old = new char[oldLength + 1];
	CopyCharArray(old, m_data);
	delete[] m_data;
	m_data = new char[newLength + 1];
	int index;
	for (index = 0; index < oldLength; index++)
	{
		*(m_data + index) = *(old + index);
	}
	while (index < newLength)
	{
		*(m_data + index) = *(rhs + (index - oldLength));
		index++;
	}
	*(m_data + index) = '\0';
	delete[] old;
	return *this;
}

/***************************************
* Purpose:
*     Checks for string equality
* Precondition:
*     A comparison of two strings is made
* Postcondition:
*     The value (true or false) is returned
***************************************/
bool String::operator == (const char * rhs) const
{
	return strcmp(m_data, rhs) == 0;
}

/***************************************
* Purpose:
*     Checks for string inequality
* Precondition:
*     A comparison of two strings is made
* Postcondition:
*     The value (true or false) is returned
***************************************/
bool String::operator != (const char * rhs) const
{
	return strcmp(m_data, rhs) != 0;
}

/***************************************
* Purpose:
*     Converts a string to an array of characters
* Precondition:
*     A conversion is made from string to const char * (cout, etc.)
* Postcondition:
*     The character array is returned.
***************************************/
String::operator const char * () const
{
	return m_data;
}

/***************************************
* Purpose:
*     Destroys the string and deallocates dynamic memory
* Precondition:
*     String goes out of scope, or dynamic string is deleted.
* Postcondition:
*     The string is destroyed.
***************************************/
String::~String()
{
	delete[] m_data;
}

/***************************************
* Purpose:
*     Helper function for finding the length of character arrays
* Precondition:
*     A null-terminated array of characters is provided
* Postcondition:
*     The length of the array (minus the null character) is returned
***************************************/
int String::FindCharArrayLength(const char * arr) const
{
	int length = 0;
	if (arr != nullptr)
	{
		while (*(arr + length) != '\0')
		{
			length++;
		}
	}
	return length;
}

/***************************************
* Purpose:
*     Helper function for opying data between character
*     arrays
* Precondition:
*     Destination and source char arrays are provided
* Postcondition:
*     Data is copied from source to destination
***************************************/
void String::CopyCharArray(char * & destination, const char * source)
{
	int length = FindCharArrayLength(source);
	delete[] destination;
	destination = new char[length + 1];
	int i;
	for (i = 0; i < length; i++)
	{
		*(destination + i) = *(source + i);
	}
	destination[i] = '\0';
}

/***************************************
* Purpose:
*     The lenth of the current string is returned
* Precondition:
*     The function is called by the consumer
* Postcondition:
*     The length is returned
***************************************/
int String::GetLength() const
{
	return FindCharArrayLength(m_data);
}

/***************************************
* Purpose:
*     Returns the value of the string as a character array
* Precondition:
*     called by consumer
* Postcondition:
*     value is returned
***************************************/
const char * String::GetValue() const
{
	return m_data;
}

/***************************************
* Purpose:
*     convert the string to all upper case
* Precondition:
*     called by consumer
* Postcondition:
*     conversion is made
***************************************/
String & String::toUpperCase()
{
	for (int i = 0, j = FindCharArrayLength(m_data); i < j; i++)
	{
		char currentChar = *(m_data + i);
		if (currentChar >= 97 && currentChar < 97 + 26)
		{
			currentChar -= 32;
		}
		*(m_data + i) = currentChar;
	}
	return *this;
}

/***************************************
* Purpose:
*     convert the string to all lower case
* Precondition:
*     called by consumer
* Postcondition:
*     conversion is made
***************************************/
String & String::toLowerCase()
{
	for (int i = 0, j = FindCharArrayLength(m_data); i < j; i++)
	{
		char currentChar = *(m_data + i);
		if (currentChar >= 65 && currentChar < 65 + 26)
		{
			currentChar += 32;
		}
		*(m_data + i) = currentChar;
	}
	return *this;
}

/***************************************
* Purpose:
*     Serialize a string
* Precondition:
*     A serialized copy of a String is needed, for example during file i/o
* Postcondition:
*     Serialized String object is returned
***************************************/
SerializedData String::Serialize()
{
	SerializedData s(std::to_string(GetLength()).c_str());
	s.Add("|");
	s.Add(m_data);
	return s;
}