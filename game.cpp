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
#include "skeleton.h"
#include "spider.h"
#include "creeper.h"
#include "pig.h"
#include "pigman.h"
#include "ghast.h"
#include "slime.h"
#include "villager.h"
#include "dragon.h"
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

// Defines the possible GameState options
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

// the size of the array of enemies
const int NUMBER_OF_ENEMIES = 10;

/***************************************
* Purpose:
*     Starts the program. Tests are run if the unit tests variable has been set. Otherwise, the
*		program starts by initializing data structures, setting the default state and then running
*		the game loop. The game loop executes the various portions of the program needed based on the
*		current GameState. The GameState is updated to transition between the various game actions.
*		Once the user quits, files are saved and the program exits.
* Postcondition:
*		By the time the main function exits, the postcondition is that the user has rage quit. Other
*		(less likely) scenarios include the user having had a fun time, a power outage, blue screen of death
*		or nuclear anihalation.
***************************************/
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

/***************************************
* Purpose:
*     Displays the menu options for the main title screen.
* Precondition:
*     Once the data structures have been populated, this is called at the default GameState to start
*		the game. The user is then prompted to select a title screen option.
***************************************/
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

/***************************************
* Purpose:
*     Displays a menu containing the credits for the game. Allows the user to back out into the title
*		screen when they are done viewing the credits.
* Precondition:
*     This is called from the title screen when the credits menu is selected.
***************************************/
void ShowCredits()
{
	ClearConsole();
	cout << endl
		<< " = - - - - - - - - > > >          GAME CREDITS          < < < - - - - - - - - = " << endl << endl
		<< "                  Developer:             Tyler Sands  < ty@tyweb.us >" << endl << endl
		<< "                    License:             MIT    ( sorry OIT )" << endl << endl
		<< "                  Copyright:             2018 Tyler Sands, No rights reserved." << endl << endl
		<< "    Character & Enemy names:             Minecraft (before Micro$OPT broke it)" << endl << endl
		<< "                 Instructor:             Troy Scevers" << endl << endl << endl
		<< "                           Press {  SPACE  } to go back" << endl;
	GetChar();
}

/***************************************
* Purpose:
*     This function, given a LinkedList of characters, gives the user options for managing the characters in the
*		given LinkedList. At the end, the user will have selected a character they would like to use for
*		battle. The user may choose to generate new characters and cycle through the characters in the list.
*		Once satisfied, the user selects a character to send into battle. The function returns the user's
*		selected character, which is then passed into the Battle function along with their enemies.
* Precondition:
*     This is called once the LinkedList of characters has been populated, when the first title screen
*		option was selected from the menu.
* Postcondition:
*     After this function, the user has edited the list of characters to their satisfaction, generating
*		new characters if they wish. The user has selected a character and is ready to battle. The
*		function returns the user's selected character so that they can start the battle.
***************************************/
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
	SaveCharacters(characters);
	return characters.Get(currentCharacter);
}

/***************************************
* Purpose:
*     Generates random characters using the GenerateRandomCharacter function until the user is satisfied
*		with the result. When satisfied, the user is asked to enter a name. The name is set and the
*		character is then added to the  LinkedList of characters.
* Precondition:
*     The LinkedList to append the new Character to needs to be provided to this function.
* Postcondition:
*     The LinkedList now has a new character which was generated by the random character generator. The
*		new character has a name selected by the user.
***************************************/
void AddCharacter(LinkedList<Character> & characters)
{
	ClearConsole();
	cout << "Add character TODO" << endl;
	GetChar();
}

/***************************************
* Purpose:
*     Returns a character with random values for health, armor and attack. The name of the character is
*		"Character". The character has an empty BackPack and CoinPouch. This is used by the AddCharacter
*		function. If the user likes the character's attributes, they will be able to give the character a
*		unique name from the AddCharacter function. Otherwise, they can choose to call this function again
*		and generate a new character.
* Precondition:
*     Random character attributes are required by the AddCharacter function
* Postcondition:
*     Character with random attributes and generic name is provided.
***************************************/
Character GenerateRandomCharacter()
{
	Character c;
	return c;
}

/***************************************
* Purpose:
*     Reads the content of the characters.bin file into the LinkedList of characters
* Precondition:
*     The LinkedList of characters to alter is provided
* Postcondition:
*     The LinkedList provided now contains the characters from the file. If no characters.bin file existed, predefined
*		default characters were added to the LinkedList with full health and correct attributes.
***************************************/
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

/***************************************
* Purpose:
*     Reads the content of the enemies.bin file into the enemy array, deserializing the enemies into
*		their respective base class types
* Precondition:
*     The array of enemies to alter is provided
* Postcondition:
*     The array provided now contains the enemies from the file. If no enemies.bin file existed, predefined
*		default enemies were added to the array with full health and correct attributes.
***************************************/
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
		enemies[0] = new Zombie;
		enemies[1] = new Skeleton;
		enemies[2] = new Spider;
		enemies[3] = new Creeper;
		enemies[4] = new Pig;
		enemies[5] = new Pigman;
		enemies[6] = new Ghast;
		enemies[7] = new Slime;
		enemies[8] = new Villager;
		enemies[9] = new Dragon;
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

/***************************************
* Purpose:
*     Serialize and save characters to the characters.bin file
* Precondition:
*     The LinkedList of characters to save is given
* Postcondition:
*     characters.bin file is updated with the contents of the LinkedList, which replace any previous file content.
***************************************/
void SaveCharacters(LinkedList<Character> & characters)
{
	fstream f("characters.bin", ios::binary | ios::out | ios::trunc);
	SerializedData s = characters.Serialize();
	f.write(s, s);
	f.close();
}

/***************************************
* Purpose:
*     Serialize and save enemies to the enemies.bin file
* Precondition:
*     The array of enemies to save is given
* Postcondition:
*     enemies.bin file is updated with the contents of the array, which replace any previous file content.
***************************************/
void SaveEnemies(Enemy * enemies[])
{
	/*
	
	As of right now in my game it doesn't make sense to do this.

	When you fight you expect new enemies to spawn and you try to defeat them.
	You do not expect them to all be dead already when you start new game.
	It's possible the intention was to do something different, but the code is written
	for it regardless, I've just commented it out to make the game work as expected and
	to improve UX.

	If I recall correctly, Troy said we could skip one of the requirements. If this was the
	case, this was the requirement I am choosing to skip.
	
	*/

	/*

	fstream f("enemies.bin", ios::binary | ios::out | ios::trunc);
	for (int i = 0; i < NUMBER_OF_ENEMIES; i++)
	{
		SerializedData s = enemies[i]->Serialize();
		f.write(s, s);
	}
	f.close();

	*/
}

/***************************************
* Purpose:
*     Provides a way for a given character to battle a given array of enemies
* Precondition:
*     The following are given:
*		- A character who will be battling
*		- An array of enemies for the character to fight
*		- The LinkedList of characters (so that it can be updated and saved after each round)
* Postcondition:
*     enemies.bin file is updated with the contents of the array, which replace any previous file content.
***************************************/
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
			char response = GetChar();
			while (
				response != 'A' &&
				response != 'a' &&
				response != 'D' &&
				response != 'd' &&
				response != 'B' &&
				response != 'b'
				)
			{
				response = GetChar();
			}
			ClearConsole();
			switch (response)
			{
			case 'A':
			case 'a':
				character.FightAttack(*enemies[i]);
				break;
			case 'D':
			case 'd':
				character.FightBlock(*enemies[i]);
				break;
			case 'B':
			case 'b':
				character.FightBerserk(*enemies[i]);
				break;
			}
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
	ClearConsole();
	if (character.GetHealth() == 0)
	{
		cout << "Character has been defeated." << endl;
		cout << "Generate new character or use other character to fight." << endl;
	}
	else
	{
		cout << "Character has defeated all enemies." << endl;
	}
	cout << "Press {  SPACE  } to go back." << endl;
	GetChar();
}

/***************************************
* Purpose:
*     When reading an enemy in from the enemies.bin file, calls the appropriate derived constructor based 
*		on the indicated derived type of the enemy.
* Precondition:
*     The SerializedData stream object is given so that the type and enemy data can be read from it.
*		The SerializedDats's position should already be set to the correct place such that the enemy
*		type is the next thing to be read. The array of enemies is given so that the new object
*		being reconstructed can be inserted. The object is then inserted at the given inex in the
*		array of enemies.
* Postcondition:
*     Appropriate derived constructor is called according to the indicated enemy type and the new
*		object is inserted into the array at the index.
***************************************/
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
	case Enemies::SKELETON :
		enemies[index] = new Skeleton(s);
		break;
	case Enemies::SPIDER :
		enemies[index] = new Spider(s);
		break;
	case Enemies::CREEPER :
		enemies[index] = new Creeper(s);
		break;
	case Enemies::PIG:
		enemies[index] = new Pig(s);
		break;
	case Enemies::PIGMAN:
		enemies[index] = new Pigman(s);
		break;
	case Enemies::GHAST:
		enemies[index] = new Ghast(s);
		break;
	case Enemies::SLIME:
		enemies[index] = new Slime(s);
		break;
	case Enemies::VILLAGER:
		enemies[index] = new Villager(s);
		break;
	case Enemies::DRAGON:
		enemies[index] = new Dragon(s);
		break;
	}
}

/***************************************
* Purpose:
*     Empties the keyboard buffer and then reads a single character
* Precondition:
*     A char is to be read for menus
* Postcondition:
*     The next character typed is returned
***************************************/
char GetChar()
{
	char input = '\0';
	while (input == '\0')
	{
		input = _getch();
	}
	return input;
}

/***************************************
* Purpose:
*     Returns a boolean indicating the user's answer to the given query
* Precondition:
*     The query to ask the user is provided
* Postcondition:
*     A boolean value indicating user intent is returned
***************************************/
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

/***************************************
* Purpose:
*     Clears the console
***************************************/
void ClearConsole()
{
	system("cls");
}