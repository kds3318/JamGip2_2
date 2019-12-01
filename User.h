#pragma once
#include <string>
#include <stdio.h>
#include <iostream>

using namespace std;
class User
{
public:
	User();
	User(string id, string pass);
	~User();
	string getId();
	string getPass();
	string getGroup();
	void setGroup(string group);

private:
	string id;
	string password;
	string group;
};
