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
	vector<User> userList;
	vector<Group> childGroup;
public :
	Group(string name, vector<User> userList, vector<Group> childGroup);
	string getName();
	vector<User>& getList();
	vector<Group>& getChild();
};

