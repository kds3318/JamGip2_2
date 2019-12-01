#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <time.h>
#include <sstream>
using namespace std;
class Memo
{
private:
	string name; // �޸� �̸�
	vector<string> date; // �޸� �ۼ���
	vector<string> content; // �޸� ����
	vector<string> tags; // �޸� �±�
	string power;   // ����
	string owner;
public:
	Memo(string name, vector<string> content, vector<string> tags, string power);
	Memo(string name, vector<string> date, vector<string> content, vector<string> tags, string power, string owner);
	string getPower();
	string getName();
	vector<string>& getDate();
	vector<string>& getContent();
	vector<string>& getTags();
	string getOwner();
	void showMemo(); // Ư�� �޸��� ���� ��ü ���
	void showMemoSimple(); // �޸��� �̸�, �ۼ� ��¥�� ���

	vector<string> today();
};