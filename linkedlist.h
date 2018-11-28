/***************************************
* Author:    Tyler Sands <ty@tyweb.us>
* License:   MIT
* Filename:  linkedlist.h
* Created:   11/26/2018
* Midiified: 10/26/2018
* Changelog:
* - 11/26/2018: Add docs
***************************************/
#pragma once
#include <string>
#include "node.h"
#include "exceptions.h"
#include "serializeddata.h"

/**
 * Class:
 *	LinkedList
 * Purpose:
 *	Provides a templated way to store data
 */
template <typename T>
class LinkedList
{
private:
	Node<T> * m_data;
public:
	LinkedList();
	LinkedList(SerializedData & data);
	LinkedList(LinkedList & obj);
	void Deserialize(SerializedData & data);
	LinkedList & operator = (LinkedList & rhs);
	~LinkedList();
	void Add(T data);
	void Delete(T data);
	void Delete(int index);
	int IndexOf(T data);
	T & Get(int index);
	int GetLength();
	operator int();
	LinkedList & operator + (LinkedList & rhs);
	LinkedList & operator + (T & data);
	LinkedList & operator - (T & data);
	void operator += (LinkedList & rhs);
	void operator += (T & data);
	void operator -= (LinkedList & rhs);
	void operator -= (T & data);
	bool operator == (LinkedList & rhs);
	bool operator != (LinkedList & rhs);
	T & operator [] (int index);
	void Purge();
	SerializedData Serialize();
};

/* Purpose: Provide default ctor */
template <typename T>
LinkedList<T>::LinkedList() : m_data(nullptr)
{
}

/* Purpose: deserialize ctor */
template <typename T>
LinkedList<T>::LinkedList(SerializedData & data) : m_data(nullptr)
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
	for (int i = 0; i < l; i++)
	{
		Add(T(data));
	}
}

/* Purpose: copy ctor */
template <typename T>
LinkedList<T>::LinkedList(LinkedList<T> & obj) : m_data(nullptr)
{
	int remoteCurrentPosition = 0;
	Node<T> * remoteCurrentNode = obj.m_data;
	Node<T> * localPreviousNode = nullptr;
	while (remoteCurrentNode != nullptr)
	{
		if (remoteCurrentPosition == 0)
		{
			// set up the local m_data on the first iteration
			m_data = new Node<T>(*remoteCurrentNode);
			localPreviousNode = m_data;
		}
		else
		{
			// build off the current chain for subsequent iterations
			localPreviousNode->m_next = new Node<T>(*remoteCurrentNode);
			localPreviousNode = localPreviousNode->m_next;
		}
		remoteCurrentPosition++;
		remoteCurrentNode = remoteCurrentNode->m_next;
	}
}

/* Purpose: Deserialization ctor */
template <typename T>
void LinkedList<T>::Deserialize(SerializedData & data)
{
	Purge();
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
	for (int i = 0; i < l; i++)
	{
		T newObject(data);
		Add(newObject);
	}
}

/* Purpose: op= */
template <typename T>
LinkedList<T> & LinkedList<T>::operator = (LinkedList<T> & rhs)
{
	if (this != &rhs)
	{
		Purge();
		int remoteCurrentPosition = 0;
		Node<T> * remoteCurrentNode = rhs.m_data;
		Node<T> * localPreviousNode;
		while (remoteCurrentNode != nullptr)
		{
			if (remoteCurrentPosition == 0)
			{
				// set up the local m_data on the first iteration
				m_data = new Node<T>(remoteCurrentNode);
				localPreviousNode = m_data;
			}
			else
			{
				// build off the current chain for subsequent iterations
				localPreviousNode->SetNext(new Node<T>(remoteCurrentNode));
				localPreviousNode = localPreviousNode->GetNext();
			}
			remoteCurrentPosition++;
			remoteCurrentNode = remoteCurrentNode->GetNext();
		}
	}
	return *this;
}

/* Purpose: dtor */
template <typename T>
LinkedList<T>::~LinkedList()
{
	Purge();
}

/* Purpose: adder for concat */
template <typename T>
void LinkedList<T>::Add(T data)
{
	Node<T> * currentNode = m_data;
	Node<T> * previousNode = nullptr;
	while (currentNode != nullptr)
	{
		previousNode = currentNode;
		currentNode = currentNode->m_next;
	}
	if (previousNode == nullptr)
	{
		m_data = new Node<T>(data);
	}
	else
	{
		previousNode->m_next = new Node<T>(data);
	}
}

/* Purpose: delete given a data object */
template <typename T>
void LinkedList<T>::Delete(T data)
{
	bool looping = true;
	Node<T> * currentNode = m_data;
	Node<T> * previusNode = nullptr;
	while (currentNode != nullptr && looping)
	{
		if (currentNode->m_data == data)
		{
			if (previusNode != nullptr)
			{
				previusNode->m_next = currentNode->m_next;
			}
			else
			{
				m_data = currentNode->m_next;
			}
			delete currentNode;
			looping = false;
		}
		previusNode = currentNode;
		currentNode = currentNode->m_next;
	}
	if (looping)
	{
		throw ITEM_NOT_FOUNT_EXCEPTION;
	}
}

/* Purpose: delete given an index from beginning of set */
template <typename T>
void LinkedList<T>::Delete(int index)
{
	bool looping = true;
	int currentIndex = 0;
	Node<T> * currentNode = m_data;
	Node<T> * previusNode = nullptr;
	while (currentNode != nullptr && looping)
	{
		if (currentIndex == index)
		{
			if (previusNode != nullptr)
			{
				previusNode->m_next = currentNode->m_next;
			}
			else
			{
				m_data = currentNode->m_next;
			}
			delete currentNode;
			looping = false;
		}
		previusNode = currentNode;
		currentNode = currentNode->m_next;
		currentIndex++;
	}
	if (looping)
	{
		throw BAD_INDEX_EXCEPTION;
	}
}

/* Purpose: find index of object */
template <typename T>
int LinkedList<T>::IndexOf(T data)
{
	bool looping = true;
	int currentIndex = 0;
	Node<T> * currentNode = m_data;
	Node<T> * previusNode = nullptr;
	while (currentNode != nullptr && looping)
	{
		if (currentNode->m_data == data)
		{
			looping = false;
		}
		currentIndex++;
		previusNode = currentNode;
		currentNode = currentNode->m_next;
	}
	if (looping)
	{
		throw BAD_INDEX_EXCEPTION;
	}
	else
	{
		return currentIndex;
	}
}

/* Purpose: Get object at index */
template <typename T>
T & LinkedList<T>::Get(int index)
{
	bool looping = true;
	int currentIndex = 0;
	Node<T> * currentNode = m_data;
	Node<T> * previusNode = nullptr;
	while (currentNode != nullptr && looping)
	{
		if (currentIndex == index)
		{
			looping = false;
		}
		currentIndex++;
		previusNode = currentNode;
		currentNode = currentNode->m_next;
	}
	if (looping)
	{
		throw ITEM_NOT_FOUNT_EXCEPTION;
	}
 	else
	{
		return previusNode->m_data;
	}
}

/* Purpose: return number of elements */
template <typename T>
int LinkedList<T>::GetLength()
{
	int currentIndex = 0;
	Node<T> * currentNode = m_data;
	Node<T> * previusNode = nullptr;
	while (currentNode != nullptr)
	{
		currentIndex++;
		previusNode = currentNode;
		currentNode = currentNode->m_next;
	}
	return currentIndex;
}

/* Purpose: return length */
template <typename T>
LinkedList<T>::operator int()
{
	return GetLength();
}

/* Purpose: concat two lists */
template <typename T>
LinkedList<T> & LinkedList<T>::operator + (LinkedList<T> & rhs)
{
	LinkedList<T> newList(*this);
	for (int i = 0, l = rhs.GetLength(); i < l; i++)
	{
		newList.Add(rhs.Get(i));
	}
	return newList;
}

/* Purpose: concat object with list */
template <typename T>
LinkedList<T> & LinkedList<T>::operator + (T & data)
{
	LinkedList<T> newList(*this);
	newList.Add(data);
	return newList;
}

/* Purpose: delete object from list */
template <typename T>
LinkedList<T> & LinkedList<T>::operator - (T & data)
{
	LinkedList<T> newList(*this);
	newList.Delete(data);
	return newList;
}

/* Purpose: add list to current list */
template <typename T>
void LinkedList<T>::operator += (LinkedList<T> & rhs)
{
	for (int i = 0, l = rhs.GetLength(); i < l; i++)
	{
		Add(rhs.Get(i));
	}
}

/* Purpose: add data to end of current list */
template <typename T>
void LinkedList<T>::operator += (T & data)
{
	Add(data);
}

/* Purpose: delete all items in the given list from the current list */
template <typename T>
void LinkedList<T>::operator -= (LinkedList<T> & rhs)
{
	for (int i = 0, l = rhs.GetLength(); i < l; i++)
	{
		Delete(rhs.Get(i));
	}
}

/* Purpose: delete given data object from current list */
template <typename T>
void LinkedList<T>::operator -= (T & data)
{
	Delete(data);
}

/* Purpose: compare for equality */
template <typename T>
bool LinkedList<T>::operator == (LinkedList<T> & rhs)
{
	bool equal = true;
	Node<T> * currentNode = m_data;
	Node<T> * remoteCurrentNode = rhs.m_data;
	while (equal && currentNode != nullptr && remoteCurrentNode != nullptr)
	{
		if (currentNode->m_data != remoteCurrentNode->m_data)
		{
			equal = false;
		}
		currentNode = currentNode->m_next;
		remoteCurrentNode = remoteCurrentNode->m_next;
	}
	equal = GetLength() == rhs.GetLength() ? equal : false;
	return equal;
}

/* Purpose: compare for inequality */
template <typename T>
bool LinkedList<T>::operator != (LinkedList<T> & rhs)
{
	return *this == rhs ? false : true;
}

/* Purpose: return item at given index */
template <typename T>
T & LinkedList<T>::operator [] (int index)
{
	return Get(index);
}

/* Purpose: delete all data from list */
template <typename T>
void LinkedList<T>::Purge()
{
	Node<T> * nextVictim = m_data;
	while (nextVictim != nullptr)
	{
		Node<T> * currentVictim = nextVictim;
		nextVictim = nextVictim->m_next;
		delete currentVictim;
	}
}

/* Purpose: serialize for sending over the wire */
template <typename T>
SerializedData LinkedList<T>::Serialize()
{
	SerializedData s(std::to_string(GetLength()).c_str());
	s.Add("|");
	for (int i = 0, l = GetLength(); i < l; i++)
	{
		s.Add(Get(i).Serialize());
	}
	return s;
}