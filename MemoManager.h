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
	int user_index; //�α��� �� ������ userList ���� index
	vector<Group> groupList;
	

	
public:
	MemoManager();
	void showMainMenu(); // ���� �޴�
	void writeMemo(); // 1. �޸� �ۼ�
	void deleteMemo(string a); // �޸� ����
	vector<string> stringSplit(string t, string Tok);
	bool checkName(string name); // �ۼ��� �޸� �̸� �˻�
	bool overlapName(string name); // �޸� �̸� �ߺ� ����
	bool checkContent(vector<string> content); // �ۼ��� �޸� ���� �˻�
	bool checkTags(vector<string> tags); // �ۼ��� �޸� �±� �˻�
	bool findMyChar(string str); // �˻� ��ȣ ���� ����
	bool checkLength(string str, int length); //���� �ʰ� Ȯ�� (length = �ִ� ����)
	bool checkSearchWords(vector<string>& searchWords, vector<string>& operation, vector<vector<string>>& slashword); // �˻� �� �±� �˻�
	bool checkPower(vector<string> powers, string& power); // �ۼ��� ���� �˻�
	//����
	void searchMenu();            // 2. �޸� �˻�
	void search_Tags();            //2.1. �±׷� �˻�
	void search_Content();         //2.2. �������� �˻�
	void search_Name();            //2.3. �̸����� �˻�
	void search_Tags_Content();      //2.4. �±�+�������� �˻�
	void searchMemo(vector<string> searchWords, int menu_flag, vector<string> operation, vector<vector<string>> slashword);
	void showMemoList(vector<int> tempMemoNumList);         //�˻��� �޸� ����Ʈ
	void showSearchedMemo(vector<int> tempMemoNumList, int position);   //�˻��� �޸� ���
	bool searching(int menu_flag, int index, vector<string>& searchWords, vector<string>& operation, vector<vector<string>>& slashword);
	int checkCorrelation(string userID, string groupName);
	//����
	void loadData();
	void saveMemo(Memo memo);
	//��ȣ
	void ascend(vector<int> & list);
	void name_ascend(vector<int>& list);//��ȯ�� ���� vector<Memo>, ���� ���� vector<Memo>
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

