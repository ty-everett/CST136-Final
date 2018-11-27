/***************************************
* Assignment:
*	CST136 Final Project
* Instructor:
*	Troy Scevers
*
* Author:    Tyler Sands <ty@tyweb.us>
* License:   MIT
* Filename:  backpack.cpp
* Created:   11/7/2018
* Midiified: 11/8/2018
* Changelog:
* - 11/20/2018: Create game stub
***************************************/
#include <iostream>
#include <fstream>
#include <conio.h>
#include "character.h"
#include "enemies/enemy.h"
#include "zombie.h"
#include "linkedlist.h"

using std::cout;
using std::fstream;
using std::ios;
using std::endl;

// Enable or disable unit tests
//#define RUN_TESTS_AND_EXIT

// Suppress Microsoft deprecation warnings
#define CRT_SECURE_NO_WARNINGS

#ifdef RUN_TESTS_AND_EXIT
	#include "tests/tests.h"
#endif

void PrintMainMenu();
void ShowCredits();
Character & SelectCharacter(LinkedList<Character> & characters);
void AddCharacter(LinkedList<Character> & characters);
Character GenerateRandomCharacter();
void PopulateCharacters(LinkedList<Character> & characters);
void PopulateEnemies(Enemy * enemies[]);
void SaveCharacters(LinkedList<Character> & characters);
void SaveEnemies(Enemy * enemies[]);
void Battle(Character & player, Enemy * enemies[]);
void ViewEnemies(Enemy * enemies[]);
char GetChar();
bool GetYesNo(char * query);
void ClearConsole();

enum State {
	MENU,
	CREDITS,
	CHARACTERS,
	ADDCHARACTER,
	BATTLE,
	ENEMIES,
	PLAYAGAIN,
	QUIT
};

const int NUMBER_OF_ENEMIES = 10;

int main()
{
	// run unit tests if enabled
#ifdef RUN_TESTS_AND_EXIT
	return TestGame();
#else
	// declare data structures
	LinkedList<Character> characters;
	PopulateCharacters(characters);
	Enemy * enemies[NUMBER_OF_ENEMIES];
	PopulateEnemies(enemies);
	int state = State::MENU;

	// set up the cconsole window
	system("title Tyler Sands - Arena Battle - CST 136 Final Project");
	system("mode con cols=80 lines=25");
	system("color 0a");

	// game loop 
	while (state != State::QUIT)
	{
		switch (state)
		{
		case State::MENU :
			PrintMainMenu();
			switch (GetChar())
			{
			case '1':
				state = State::CHARACTERS;
				break;
			case '2':
				state = State::ENEMIES;
				break;
			case '3':
				state = State::CREDITS;
				break;
			case '4':
				state = State::QUIT;
				break;
			}
			break;
		case State::CHARACTERS :
		{
			Character selected = SelectCharacter(characters);
			Battle(selected, enemies);
			break;
		}
		case State::ENEMIES :
			ViewEnemies(enemies);
			break;
		case State::CREDITS :
			ShowCredits();
			state = State::MENU;
			break;
		}
	}
	return 0;
#endif
}

void PrintMainMenu()
{
	ClearConsole();
	cout << endl
		<< " = - - - - - - - - > > >          ARENA BATTLE          < < < - - - - - - - - = " << endl << endl << endl
		<< " { 1 } :                  Pick Your Character & BATTLE!" << endl << endl
		<< " { 2 } :                        View Your Enemies" << endl << endl
		<< " { 3 } :                      Credits & Attribution" << endl << endl
		<< " { 4 } :                           Rage Quit" << endl;
}

void ShowCredits()
{
	ClearConsole();
	cout << endl
		<< " = - - - - - - - - > > >          ARENA BATTLE          < < < - - - - - - - - = " << endl << endl
		<< "                            Developer:   Tyler Sands" << endl
		<< "                              License:   MIT" << endl
		<< "                           Instructor:   Troy Scevers" << endl << endl
		<< "                              PRESS SPACE TO GO BACK" << endl;
	GetChar();
}

Character & SelectCharacter(LinkedList<Character> & characters)
{
	int currentCharacter = 0;
	bool selected = false;
	while (selected == false)
	{
		ClearConsole();
		cout << endl << "                            Displaying character { "
			<< (currentCharacter + 1) << " } of { " << (characters.GetLength() + 1)
			<< " }" << endl << endl;
		characters.Get(selected).Display();
		cout << endl;
		if (currentCharacter > 0)
		{
			cout << "   < P ] PREVIOUS   ";
		}
		else
		{
			cout << "                    ";
		}
		cout << " [ G ] GENERATE NEW ";
		cout << "    [ B ] BATTLE    ";
		if (currentCharacter < characters.GetLength())
		{
			cout << "       [ N > NEXT   ";
		}
		else
		{
			cout << "                    ";
		}
		cout << endl;
		char response = GetChar();
		while (
			response != 'P' &&
			response != 'p' &&
			response != 'G' &&
			response != 'g' &&
			response != 'B' &&
			response != 'b' &&
			response != 'N' &&
			response != 'n'
			)
		{
			response = GetChar();
		}
		switch (response)
		{
		case 'P' :
		case 'p' :
			currentCharacter > 0 && currentCharacter--;
			break;
		case 'N' :
		case 'n' :
			currentCharacter < characters.GetLength() && currentCharacter++;
			break;
		case 'B' :
		case 'b' :
			selected = true;
			break;
		case 'G' :
		case 'g' :
			AddCharacter(characters);
			break;
		}
	}
	return characters.Get(currentCharacter);
}

void AddCharacter(LinkedList<Character> & characters)
{
	ClearConsole();
	cout << "Add character TODO" << endl;
	GetChar();
}

Character GenerateRandomCharacter()
{
	Character c;
	return c;
}

void PopulateCharacters(LinkedList<Character> & characters)
{
	fstream f("characters.bin", ios::binary | ios::in);
	if (f.good()) // file EXISTS and is open
	{
		// read data from file
		// ref. https://stackoverflow.com/a/18398230
		std::string contents((std::istreambuf_iterator<char>(f)),
			std::istreambuf_iterator<char>());
		SerializedData s(contents.c_str());
		characters.Deserialize(s);
	} 
	else // file did not exist and we need to create it with defaults
	{
		for (int i = 0; i < 3; i++)
		{
			// TODO call the RNG
			Character newCharacter;
			characters.Add(newCharacter);
		}
	}
	f.close();
}

void PopulateEnemies(Enemy * enemies[])
{
	fstream f("enemies.bin", ios::binary | ios::in);
	if (f.good()) // file EXISTS and is open
	{
		// read data from file
		// ref. https://stackoverflow.com/a/18398230
		std::string contents((std::istreambuf_iterator<char>(f)),
			std::istreambuf_iterator<char>());
		SerializedData s(contents.c_str());
		for (int i = 0; i < NUMBER_OF_ENEMIES; i++)
		{
			enemies[i] = new Zombie(); // TODO enemy type identification, serialization functions, deserialization ctors for all enemy types
		}
	}
	else // file did not exist and we need to create it with defaults
	{
		for (int i = 0; i < NUMBER_OF_ENEMIES; i++)
		{
			// TODO call the RNG
			Zombie newZombie;
			enemies[i] = &newZombie;
		}
	}
	f.close();
}

void ViewEneemies(Enemy * enemies[])
{
	cout << "Enemies:" << endl;
	for (int i = 0; i < NUMBER_OF_ENEMIES; i++)
	{
		enemies[i]->Display();
	}
}

void SaveCharacters()
{
	fstream f("characters.bin", ios::binary | ios::out | ios::trunc);
	
	f.close();
}

char GetChar()
{
	char input = '\0';
	while (input == '\0')
	{
		input = _getch();
	}
	return input;
}

bool GetYesNo(char * query)
{
	cout << query << " (Y/N): ";
	char input = GetChar();
	cout << endl;
	while (input != 'Y' && input != 'N' && input != 'y' && input != 'n')
	{
		cout << "Please answer with either Y or N" << endl;
		cout << query << " (Y/N): ";
		input = GetChar();
		cout << endl;
	}
	return input == 'Y' || input == 'y';
}

void ClearConsole()
{
	system("cls");
}