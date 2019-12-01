#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "User.h"

using namespace std;

class Group
{
private:
	string name;
	int depth;
	vector<string> childGroup;
public:
	Group(string name);
	Group(string name, vector<string> childGroup);
	string getName();
	vector<string>& getChild();
};