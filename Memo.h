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
	string name; // 메모 이름
	vector<string> date; // 메모 작성일
	vector<string> content; // 메모 내용
	vector<string> tags; // 메모 태그
	string power;   // 권한
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
	void showMemo(); // 특정 메모의 내용 전체 출력
	void showMemoSimple(); // 메모의 이름, 작성 날짜만 출력

	vector<string> today();
};