#pragma once

#include<iostream>
using namespace std;

class CardStatsLibrary
{
public:
	CardStatsLibrary();
	~CardStatsLibrary();
	int getAttack(int id);
	int getHP(int id);
	string getpath(int id);
};