/***************************************
* Author:    Tyler Sands <ty@tyweb.us>
* License:   MIT
* Filename:  string.h
* Created:   10/3/2018
* Midiified: 10/9/2018
* Changelog:
* - 110/9/2018: Add documentation to existing implementation
***************************************/
#pragma once

#include "SerializedData.h"

/***************************************
* Class:
*     String
* Purpose: 
*     Provide functions to ease the use of null-terminated
*     character arrays. Manage memory and overload
*     expected by the consumer.
***************************************/
class String
{
private:
	char * m_data;
	int FindCharArrayLength(const char * arr) const;
	void CopyCharArray(char * & destination, const char * source);
public:
	String();
	String(SerializedData & data);
	String(const char * str);
	String(const String & obj);
	String & operator = (const String & rhs);
	String & operator = (const char * rhs);
	String & operator += (const char * rhs);
	bool operator == (const char * rhs) const;
	bool operator != (const char * rhs) const;
	operator const char * () const;
	~String();
	int GetLength() const;
	const char * GetValue() const;
	String & toLowerCase();
	String & toUpperCase();
	SerializedData Serialize();
};

