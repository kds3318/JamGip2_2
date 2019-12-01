#include "Group.h"


Group::Group(string name, vector<User> userList, vector<Group> childGroup)
	:name(name), userList(userList), childGroup(childGroup)
{
};

string Group::getName() {
	return name;
}
vector<User>& Group::getList() {
	return userList;
}
vector<Group>& Group::getChild() {
	return childGroup;
}