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
	vector<Group> childGroup;
public :
	Group(string name);
	Group(string name, vector<Group> childGroup);
	string getName();
	vector<Group>& getChild();
};

