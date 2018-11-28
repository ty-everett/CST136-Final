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
void Battle(Character & character, Enemy * enemies[], LinkedList<Character> & characters);
void ViewEnemies(Enemy * enemies[]);
char GetChar();
bool GetYesNo(char * query);
void ClearConsole();
void ClassifyEnemy(SerializedData & s, Enemy * enemies[], int index);

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
			Battle(SelectCharacter(characters), enemies, characters);
			state = State::MENU;
			break;
		}
		case State::ENEMIES :
			ViewEnemies(enemies);
			state = State::MENU;
			break;
		case State::CREDITS :
			ShowCredits();
			state = State::MENU;
			break;
		}
	}
	SaveCharacters(characters);
	SaveEnemies(enemies);
	// deallocate dynamic memory
	for (int i = 0; i < NUMBER_OF_ENEMIES; i++)
	{
		delete enemies[i];
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
		<< " = - - - - - - - - > > >          GAME CREDITS          < < < - - - - - - - - = " << endl << endl
		<< "                  Developer:             Tyler Sands" << endl << endl
		<< "                    License:             MIT    ( sorry OIT )" << endl << endl
		<< "                  Copyright:             2018 Tyler Sands, No rights reserved." << endl << endl
		<< "    Character & Enemy names:             Minecraft (before Micro$OPT broke it)" << endl << endl
		<< "                 Instructor:             Troy Scevers" << endl << endl << endl
		<< "                           Press {  SPACE  } to go back" << endl;
	GetChar();
}

Character & SelectCharacter(LinkedList<Character> & characters)
{
	int currentCharacter = 0;
	bool selected = false;
	while (selected == false)
	{
		ClearConsole();
		cout << endl << "                         Displaying character { "
			<< (currentCharacter + 1) << " } of { " << characters.GetLength()
			<< " }" << endl << endl;
		characters.Get(currentCharacter).Display();
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
		if (currentCharacter < characters.GetLength() - 1)
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
			currentCharacter < characters.GetLength() - 1 && currentCharacter++;
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
			ClassifyEnemy(s, enemies, i);
		}
	}
	else // file did not exist and we need to create it with defaults
	{
		for (int i = 0; i < NUMBER_OF_ENEMIES; i++)
		{
			// TODO call the RNG
			enemies[i] = new Zombie;
		}
	}
	f.close();
}

void ViewEnemies(Enemy * enemies[])
{
	ClearConsole();
	cout << "\n = - - - - - - - - > > >          YOUR ENEMIES          < < < - - - - - - - - = \n\n";
	for (int i = 0; i < NUMBER_OF_ENEMIES; i++)
	{
		enemies[i]->Display();
	}
	cout << "\n\n                          To go back to the main menu, press\n\n";
	cout << "                                   {  SPACE  }" << endl;
	GetChar();
}

void SaveCharacters(LinkedList<Character> & characters)
{
	fstream f("characters.bin", ios::binary | ios::out | ios::trunc);
	SerializedData s = characters.Serialize();
	f.write(s, s);
	f.close();
}

void SaveEnemies(Enemy * enemies[])
{
	fstream f("enemies.bin", ios::binary | ios::out | ios::trunc);
	for (int i = 0; i < NUMBER_OF_ENEMIES; i++)
	{
		SerializedData s = enemies[i]->Serialize();
		f.write(s, s);
	}
	f.close();
}

void Battle(Character & character, Enemy * enemies[], LinkedList<Character> & characters)
{
	ClearConsole();
	for (int i = 0; i < NUMBER_OF_ENEMIES && character.GetHealth() > 0; i++)
	{
		while (character.GetHealth() != 0 && enemies[i]->GetHealth() != 0) // keep fighting till one dies
		{
			cout << endl << "                    Battling enemy { " << i + 1 << " } of { " << NUMBER_OF_ENEMIES << " }" << endl << endl;
			enemies[i]->Display();
			cout << endl;
			character.Display();
			cout << endl;
			cout << "     [ A ] NORMAL ATTACK     [ D ] BLOCK     [ B ] BERSERK" << endl;
			GetChar(); // TODO implement keys
			ClearConsole();
			character.FightAttack(*enemies[i]);
			SaveCharacters(characters);
			SaveEnemies(enemies);
			cout << endl << "                         Press {  SPACE  } to continue" << endl;
			GetChar();
			ClearConsole();
		}
		if (character.GetHealth() == 0)
		{
			cout << "Character was defeated by " << enemies[i]->GetName() << "!" << endl;
		}
		else
		{
			cout << "Character successfully defeated " << enemies[i]->GetName() << "!" << endl;
		}
		cout << endl << "                         Press {  SPACE  } to continue" << endl;
		GetChar();
		ClearConsole();
	}
	if (character.GetHealth() == 0)
	{
		ClearConsole();
		cout << "Character has been defeated." << endl;
		cout << "Generate new character or use other character to fight." << endl;
		cout << "Press {  SPACE  } to go back." << endl;
		GetChar();
	}
}

void ClassifyEnemy(SerializedData & s, Enemy * enemies[], int index)
{
	char length[10];
	int offset = 0;
	bool loop = true;
	do
	{
		length[offset] = s.ReadCharacter();
		if (length[offset] == '|')
		{
			length[offset] = '\0';
			loop = false;
		}
		offset++;
	} while (loop);
	int ID = atoi(length);
	switch (ID)
	{
	case Enemies::ZOMBIE :
		enemies[index] = new Zombie(s);
		break;
	//case Enemies::SKELETON :
	//	break;
	//	...
	}
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