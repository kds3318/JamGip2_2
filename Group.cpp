#include "Group.h"


Group::Group(string name)
	:name(name)
{
}

Group::Group(string name, vector<string> childGroup)
	: name(name), childGroup(childGroup)
{
};

string Group::getName() {
	return name;
}
vector<string>& Group::getChild() {
	return childGroup;
}