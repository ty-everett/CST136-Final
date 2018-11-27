#pragma once
/***************************************
* Author:    Tyler Sands <ty@tyweb.us>
* License:   MIT
* Filename:  node.h
* Created:   11/19/2018
* Midiified: 11/19/2018
* Changelog:
* - 11/19/2018: Create the templated Node class
***************************************/

/***************************************
* Class:
*     Node
* Purpose:
*     Stores a single element for use in a templated LinkedList class
***************************************/
template <typename T>
class LinkedList;
template <typename T>
class Node
{
private:
	T m_data;
	Node * m_next;
public:
	Node(T data);
	Node(Node & obj);
	Node & operator = (Node & rhs);
	~Node();
	friend class LinkedList<T>;
};

/* Purpose: create new node given data */
template <typename T>
Node<T>::Node(T data) : m_data(data), m_next(nullptr)
{
}

/* Purpose: copy a node */
template <typename T>
Node<T>::Node(Node & obj) : m_data(obj.m_data), m_next(obj.m_next)
{
}

/* Purpose: op= */
template <typename T>
Node<T> & Node<T>::operator = (Node<T> & rhs)
{
	if (this != &rhs)
	{
		m_data = rhs.m_data;
		m_next = rhs.m_next;
	}
	return *this;
}

/* Purpose: dtor */
template <typename T>
Node<T>::~Node()
{
}