#include "User.h"

User::User()
{
}

User::User(string id, string pass)
	:id(id), password(pass), group("default")
{
}


User::~User()
{
}

string User::getId()
{
	//asdfasdfasdf
	return id;
}

string User::getPass()
{
	return password;
}

string User::getGroup()
{
	return group;
}

void User::setGroup(string group)
{
	this->group = group;
}
