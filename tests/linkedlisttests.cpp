/***************************************
* Author:    Tyler Sands <ty@tyweb.us>
* License:   MIT
* Filename:  linkedlisttests.cpp
* Created:   11/20/2018
* Midiified: 11/20/2018
* Changelog:
* - 11/20/2018 : Test the templated LinkedList class
***************************************/
#include "linkedlisttests.h"

#include <iostream>
#include "../linkedlist.h"
#include "../string.h"
#include "../potion.h"

using std::cout;

/* Purpose: to test link list */
int TestLinkedList()
{
	int returnValue = 0;
	try
	{
		cout << "Testing LinkedList class..." << endl;
		cout << "Create LinkedList of strings" << endl;
		LinkedList<String> stringList;
		cout << "Length of new LinkedList: " << stringList.GetLength() << endl;
		cout << "Adding two items to list, 'foobar' and then 'barfoo'" << endl;
		stringList.Add("foobar");
		stringList.Add("barfoo");
		cout << "Length of updated LinkedList: " << stringList.GetLength() << endl;
		cout << "Index of barfoo: " << stringList.IndexOf("barfoo") << endl;
		cout << "Deleting foobar" << endl;
		stringList.Delete("foobar");
		cout << "Index of barfoo after deleting foobar: " << stringList.IndexOf("barfoo") << endl;
		cout << "Creating a copy of the LinkedList with the copy ctor" << endl;
		LinkedList<String> otherStringList(stringList);
		cout << "Does new copy equal original? " << (otherStringList == stringList) << endl;
		cout << "Adding a new element to the copy" << endl;
		otherStringList.Add("potato");
		cout << "Does copy equal the original after modifying the copy? " << (otherStringList == stringList) << endl;
		cout << "Listing items in first LinkedList" << endl;
		for (int i = 0, l = stringList.GetLength(); i < l; i++)
		{
			cout << stringList[i] << endl;
		}
		cout << "Length of first array: " << stringList.GetLength() << endl;
		cout << "Listing items in other LinkedList" << endl;
		for (int i = 0, l = otherStringList.GetLength(); i < l; i++)
		{
			cout << otherStringList[i] << endl;
		}
		cout << "Length of first array: " << otherStringList.GetLength() << endl;
		cout << "other array sub one: " << otherStringList[1] << endl;
		cout << "Adding other array to first array..." << endl;
		stringList += otherStringList;
		cout << "Listing items in first LinkedList" << endl;
		for (int i = 0, l = stringList.GetLength(); i < l; i++)
		{
			cout << stringList[i] << endl;
		}
		cout << "Length of first list: " << stringList.GetLength() << endl;
		cout << "Replacing second element of array with 'second'..." << endl;
		stringList[1] = "second";
		cout << "Listing items in first LinkedList" << endl;
		for (int i = 0, l = stringList.GetLength(); i < l; i++)
		{
			cout << stringList[i] << endl;
		}
		cout << "Length of first list: " << stringList.GetLength() << endl;
		cout << "Deleting second element of first array" << endl;
		stringList.Delete(1);
		cout << "Listing items in first LinkedList" << endl;
		for (int i = 0, l = stringList.GetLength(); i < l; i++)
		{
			cout << stringList[i] << endl;
		}
		cout << "Length of first list: " << stringList.GetLength() << endl;
		cout << "Serializing first array..." << endl;
		SerializedData cereal(stringList.Serialize());
		cout << static_cast<const char *>(cereal) << endl;
		cout << "constructing list from cereal" << endl;
		LinkedList<String> resurrected(cereal);
		cout << "length of resurrected: " << resurrected.GetLength() << endl;
		cout << "contents of resurrected:" << endl;
		for (int i = 0, l = resurrected.GetLength(); i < l; i++)
		{
			cout << resurrected[i] << endl;
		}
		cout << "LinkedList tests: PASS\n";
		returnValue = 0;
	}
	catch (...)
	{
		cout << "LinkedList tests: FAIL" << endl;
		returnValue = -1;
	}
	return returnValue;
}