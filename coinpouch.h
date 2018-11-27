/***************************************
* Author:    Tyler Sands <ty@tyweb.us>
* License:   MIT
* Filename:  coinpouch.h
* Created:   11/8/2018
* Midiified: 11/8/2018
* Changelog:
* - 11/7/2018  : Create CoinPouch class
***************************************/
#pragma once

#include "SerializedData.h"

/***************************************
* Class:
*     CoinPouch
* Purpose:
*     Responsible for maintaining and organizing data about the in-game currency
***************************************/
class CoinPouch
{
private:
	int m_copper;
	int m_bronze;
	int m_silver;
	int m_gold;
	void CombineCoins();
public:
	CoinPouch();
	CoinPouch(SerializedData & data);
	CoinPouch(CoinPouch & obj);
	CoinPouch & operator = (CoinPouch & rhs);
	bool operator == (const CoinPouch & rhs) const;
	bool operator != (const CoinPouch & rhs) const;
	~CoinPouch();
	void Display();
	bool HasEnoughMoney(int copper, int bronze, int silver, int gold);
	void SetCopper(int copper);
	void SetBronze(int bronze);
	void SetSilver(int silver);
	void SetGold(int gold);
	int GetCopper() const;
	int GetBronze() const;
	int GetSilver() const;
	int GetGold() const;
	void AddCopper(int copper);
	void AddBronze(int bronze);
	void AddSilver(int silver);
	void AddGold(int gold);
	SerializedData Serialize();
};

