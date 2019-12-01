#include <iostream>
#include <string>
#include <vector>
#include <io.h>
#include <filesystem>
#include<fstream>
#include <direct.h>
#include <Windows.h>
#include<stdlib.h>
#include<conio.h>
#include"Memo.h"
#include"User.h"
#include"Group.h"

class MemoManager
{
private:
	vector<Memo> memoList;
	vector<User> userList;
	int user_index; //로그인 한 유저의 userList 내의 index
	vector<Group> groupList;
	

	
public:
	MemoManager();
	void showMainMenu(); // 메인 메뉴
	void writeMemo(); // 1. 메모 작성
	void deleteMemo(string a); // 메모 삭제
	vector<string> stringSplit(string t, string Tok);
	bool checkName(string name); // 작성시 메모 이름 검사
	bool overlapName(string name); // 메모 이름 중복 유무
	bool checkContent(vector<string> content); // 작성시 메모 내용 검사
	bool checkTags(vector<string> tags); // 작성시 메모 태그 검사
	bool findMyChar(string str); // 검색 기호 포함 유무
	bool checkLength(string str, int length); //길이 초과 확인 (length = 최대 길이)
	bool checkSearchWords(vector<string>& searchWords, vector<string>& operation, vector<vector<string>>& slashword); // 검색 시 태그 검사
	bool checkPower(vector<string> powers, string& power); // 작성시 권한 검사
	//성윤
	void searchMenu();            // 2. 메모 검색
	void search_Tags();            //2.1. 태그로 검색
	void search_Content();         //2.2. 내용으로 검색
	void search_Name();            //2.3. 이름으로 검색
	void search_Tags_Content();      //2.4. 태그+내용으로 검색
	void searchMemo(vector<string> searchWords, int menu_flag, vector<string> operation, vector<vector<string>> slashword);
	void showMemoList(vector<int> tempMemoNumList);         //검색한 메모 리스트
	void showSearchedMemo(vector<int> tempMemoNumList, int position);   //검색된 메모 출력
	bool searching(int menu_flag, int index, vector<string>& searchWords, vector<string>& operation, vector<vector<string>>& slashword);
	int checkCorrelation(string userID, string groupName);
	//종우
	void loadData();
	void saveMemo(Memo memo);
	//지호
	void ascend(vector<int> & list);
	void name_ascend(vector<int>& list);//반환값 원래 vector<Memo>, 인자 원래 vector<Memo>
	void name_decend(vector<int>& list);
	void time_ascend(vector<int>& list);
	void time_decend(vector<int>& list);
	

	void loginMenu();
	void regi();
	void root_menu();
	void make_group();
	void change_group();
	bool search_group(string n1, string n2);
};

