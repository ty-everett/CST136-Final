/***************************************
* Author:    Tyler Sands <ty@tyweb.us>
* License:   MIT
* Filename:  serializeddata.h
* Created:   11/10/2018
* Midiified: 11/10/2018
* Changelog:
* - 11/10/2018: Create the class
***************************************/
#pragma once
/***************************************
* Class:
*     SerializedData
* Purpose:
*     Provides a data structure for serialized data.
***************************************/
class SerializedData
{
private:
	char * m_data;
	unsigned int m_position;
public:
	SerializedData(const char * data);
	SerializedData(SerializedData & obj);
	~SerializedData();
	operator int ();
	operator const char * ();
	operator char * ();
	void Add(const char * str);
	char ReadCharacter();
};

