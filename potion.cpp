/***************************************
* Author:    Tyler Sands <ty@tyweb.us>
* License:   MIT
* Filename:  potion.cpp
* Created:   10/1/2018
* Midiified: 10/4/2018
* Changelog:
* - 10/1/2018: Implement constructors, getters/setters and manager functions
* - 10/3/2018: Implement SimplifyCost
* - 10/9/2018: Moving to own string class from std::string
***************************************/
#include "Potion.h"
#include "SerializedData.h"
#include "String.h"

// Prevent Microsoft from complaining about strcpy being "deprecated"
#pragma warning(disable : 4996)

/***************************************
* Purpose:
*     Constructs a Potion object with default parameters.
* Precondition:
*     Potion constructor is called with no arguments
* Postcondition:
*     A new Potion with default attributes is created
***************************************/
Potion::Potion() : m_name("Potion"), m_description("It's tasty, you should try it!"), m_potency("HIGH"), m_cost(SimplifyCost("0.1.99.0"))
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
Potion::Potion(SerializedData & data) : m_name(data), m_description(data), m_potency(data), m_cost(data)
{
}

/***************************************
* Purpose:
*     Constructs a Potion object with the given parameters.
* Precondition:
*     Potion constructor is called with 4 arguments
* Postcondition:
*     A new Potion with the given attributes is created
***************************************/
Potion::Potion(String name, String description, String potency, String cost) : m_name(name), m_description(description), m_potency(potency.toUpperCase()), m_cost(SimplifyCost(cost))
{
}

/***************************************
* Purpose:
*     Constructs a potion from another Potion object (makes a copy)
* Precondition:
*     Potion is passed or returned by value, or Potion constructor is called with
*     a Potion object as an argument.
* Postcondition:
*     A new Potion with the same attributes as the given object is created
***************************************/
Potion::Potion(const Potion & obj) : m_name(obj.m_name), m_description(obj.m_description), m_potency(obj.m_potency), m_cost(obj.m_cost)
{
}

/***************************************
* Purpose:
*     Sets a Potion object's member variables equal to those of another Potion object
* Precondition:
*     The "=" sign is used to set one Potion object equal to another.
* Postcondition:
*     The current Potion object's member variables are replaced with those of the
*     Potion object on the right hand side of the "=" sign.
***************************************/
Potion & Potion::operator = (const Potion & rhs)
{
	if (&rhs != this)
	{
		m_name = rhs.m_name;
		m_description = rhs.m_description;
		m_potency = rhs.m_potency;
		m_cost = rhs.m_cost;
	}
	return *this;
}

/***************************************
* Purpose:
*     Formats and prints the Potion object's member variables on stdout
* Precondition:
*     Member function is invoked on an object of type Potion
* Postcondition:
*     Member variables from the current Potion object are printed on stdout
***************************************/
void Potion::Display() const
{
	cout << "Potion properties:" << endl;
	cout << "Name:           " << m_name.GetValue() << endl;
	cout << "Description:    " << m_description.GetValue() << endl;
	cout << "Potency:        " << m_potency.GetValue() << endl;
	cout << "Cost:           " << m_cost.GetValue() << endl;
}

/***************************************
* Purpose:
*     Returns the current Potion object's member variable m_name
* Precondition:
*     Member function is invoked on an object of type Potion
* Postcondition:
*     Member variable is returned to object consumer
***************************************/
String Potion::GetName() const
{
	return m_name;
}

/***************************************
* Purpose:
*     Compare two Potion objects for equality
* Precondition:
*     Called during object comparison
* Postcondition:
*     True is returned if the two objects are equal
***************************************/
bool Potion::operator == (const Potion & rhs) const
{
	bool equal = true;
	if (m_name != rhs.m_name) equal = false;
	if (m_description != rhs.m_description) equal = false;
	if (m_potency != rhs.m_potency) equal = false;
	if (m_cost != rhs.m_cost) equal = false;
	return equal;
}

/***************************************
* Purpose:
*     Compare two Potion objects for inequality
* Precondition:
*     Called during object comparison
* Postcondition:
*     Returns a boolean indicatinginequality
***************************************/
bool Potion::operator != (const Potion & rhs) const
{
	return *this == rhs ? false : true;
}

/***************************************
* Purpose:
*     Returns the current Potion object's member variable m_description
* Precondition:
*     Member function is invoked on an object of type Potion
* Postcondition:
*     Member variable is returned to object consumer
***************************************/
String Potion::GetDescription() const
{
	return m_description;
}

/***************************************
* Purpose:
*     Returns the current Potion object's member variable m_potency
* Precondition:
*     Member function is invoked on an object of type Potion
* Postcondition:
*     Member variable is returned to object consumer
***************************************/
String Potion::GetPotency() const
{
	return m_potency;
}

/***************************************
* Purpose:
*     Returns the current Potion object's member variable m_cost
* Precondition:
*     Member function is invoked on an object of type Potion
* Postcondition:
*     Member variable is returned to object consumer
***************************************/
String Potion::GetCost() const
{
	return m_cost;
}

/***************************************
* Purpose:
*     Sets the current Potion object's m_name member variable to the given string
* Precondition:
*     Member function is invoked on an object of type Potion
* Postcondition:
*     Member variable is updated with new value
***************************************/
void Potion::SetName(const String name)
{
	m_name = name;
}

/***************************************
* Purpose:
*     Sets the current Potion object's m_description member variable to the given string
* Precondition:
*     Member function is invoked on an object of type Potion
* Postcondition:
*     Member variable is updated with new value
***************************************/
void Potion::SetDescription(const String description)
{
	m_description = description;
}

/***************************************
* Purpose:
*     Sets the current Potion object's m_potency member variable to the given string
* Precondition:
*     Member function is invoked on an object of type Potion
* Postcondition:
*     Member variable is updated with new value
***************************************/
void Potion::SetPotency(const String potency)
{
	m_potency = potency;
	m_potency = m_potency.toUpperCase();
}

/***************************************
* Purpose:
*     Sets the current Potion object's m_cost member variable to the given string,
*     converting the value according to the instructions for Lab 1, using a private
*     helper function.
* Precondition:
*     Member function is invoked on an object of type Potion
* Postcondition:
*     Member variable is updated with new value after conversion
***************************************/
void Potion::SetCost(const String cost)
{
	m_cost = SimplifyCost(cost);
}

/***************************************
* Purpose:
*     Ensures a given cost string is valid and in accordance with the
*     instructions for Lab 1
* Precondition:
*     Helper function is invoked during cost conversion
* Postcondition:
*     Compliant value is returned to function caller
***************************************/
String Potion::SimplifyCost(const String cost)
{
	char * val = new char[cost.GetLength() + 1];
	strcpy(val, cost.GetValue());
	char * token = strtok(val, ".");
	int platinum = std::stoi(token);
	token = strtok(nullptr, ".");
	int gold = std::stoi(token);
	token = strtok(nullptr, ".");
	int silver = std::stoi(token);
	token = strtok(nullptr, ".");
	int copper = std::stoi(token);
	delete[] val;
	while (copper >= 100)
	{
		silver++;
		copper-=100;
	}
	while (silver >= 100)
	{
		gold++;
		silver -= 100;
	}
	while (gold >= 100)
	{
		platinum++;
		gold -= 100;
	}
	String validPrice = std::to_string(platinum).c_str();
	validPrice += ".";
	validPrice += std::to_string(gold).c_str();
	validPrice += ".";
	validPrice += std::to_string(silver).c_str();
	validPrice += ".";
	validPrice += std::to_string(copper).c_str();
	return validPrice;
}

/***************************************
* Purpose:
*     Ensure all dynamic memory is unallocated (freed) prior to object distruction
* Precondition:
*     Potion object goes out of scope, or a dynamically allocated Potion object is
*     deleted.
* Postcondition:
*     Current Potion object is destroyed.
***************************************/
Potion::~Potion()
{
}

/***************************************
* Purpose:
*     Serialize a Potion
* Precondition:
*     A serialized copy of a Potion is needed, for example during file i/o
* Postcondition:
*     Serialized Potion object is returned
***************************************/
SerializedData Potion::Serialize()
{
	SerializedData s(m_name.Serialize());
	s.Add(m_description.Serialize());
	s.Add(m_potency.Serialize());
	s.Add(m_cost.Serialize());
	return s;
}