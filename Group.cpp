#include "Group.h"


Group::Group(string name)
	:name(name)
{
}

Group::Group(string name, vector<Group> childGroup)
	:name(name), childGroup(childGroup)
{
};

string Group::getName() {
	return name;
}
vector<Group>& Group::getChild() {
	return childGroup;
}
