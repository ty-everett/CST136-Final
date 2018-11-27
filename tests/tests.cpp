/***************************************
* Author:    Tyler Sands <ty@tyweb.us>
* License:   MIT
* Filename:  tests.cpp
* Created:   11/20/2018
* Midiified: 11/20/2018
* Changelog:
* - 11/20/2018 : Write unit tests
***************************************/
#include "tests.h"
#include <iostream>

#include "linkedlisttests.h"

using std::cout;

/* Purpose: unit testing */
int TestGame()
{
	int testResults = 0;
	testResults += TestLinkedList();
	if (testResults == 0)
	{
		cout << "All tests: PASS\n";
	}
	else
	{
		cout << "Number of top-level failures: " << (testResults * -1) << "\n";
		cout << "Tests: FAIL\n";
	}
	system("pause");
	return testResults;
}