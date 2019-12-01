#include "MemoManager.h"

MemoManager::MemoManager()
{
}

void MemoManager::loadData() {
	//현재경로
	char path[129] = { 0 };
	if (GetCurrentDirectoryA(128, path) > 0) {
		//cout << string(path) << endl;
	}
	string way = string(path);
	way = way + "\\" + "*.txt";
	vector<string> txtNames;

	struct _finddata_t fd;

	intptr_t handle;

	if ((handle = _findfirst(way.c_str(), &fd)) == -1L)
		cout << "No file in directory!" << endl;
	else {
		do {
			txtNames.push_back(fd.name);
		} while (_findnext(handle, &fd) == 0);
	}
	_findclose(handle);

	//for (int i = 0; i < txtNames.size(); i++) {
	//   cout << txtNames[i] << endl;
	//}
	//cout << path << endl;
	//현재 경로에서 txt파일 탐색

	//txtNames에 파일목록이 들어있는 상태
	//불러오기 하면된다
	for (int i = 0; i < txtNames.size(); i++) {
		string in_line, power, owner;
		vector<string> tags, content, date;
		ifstream in(txtNames.at(i));
		if (getline(in, in_line)) {
			date = stringSplit(in_line, " ");
		}
		while (getline(in, in_line)) {
			if (in_line == "+")
				break;
			content.push_back(in_line);
		}
		if (getline(in, in_line))
			tags = stringSplit(in_line, " ");
		if (getline(in, in_line))
			power = in_line;
		if (getline(in, in_line))
			owner = in_line;
		in.close();
		string str = txtNames.at(i);
		str.erase(str.begin() + str.length() - 4, str.end());
		Memo memo(str, date, content, tags, power, owner);
		memoList.push_back(memo);
	}
}

void MemoManager::saveMemo(Memo memo)
{
	string nal = "";

	for (int i = 0; i < memo.getDate().size(); i++) {
		nal += memo.getDate()[i] + " ";
	}

	ofstream out(memo.getName() + ".txt");

	out << nal << endl;

	//content 입력
	for (int i = 0; i < memo.getContent().size(); i++) {
		out << memo.getContent()[i] << endl;
	}
	out << "+" << endl;
	//tag 입력
	for (int i = 0; i < memo.getTags().size(); i++) {
		out << memo.getTags()[i] << " ";
	}

	out << memo.getPower() << endl;
	out << memo.getOwner() << endl;

	out << endl;
	out.close();
}

void MemoManager::showMainMenu()
{
	loadData();
	string menu;
	do {
		cout << "1. 메모 작성\n2. 메모 검색\n3. 종 료" << endl;
		cout << "메뉴 번호를 입력하세요 ▶ ";
		getline(cin, menu);
		if (menu.compare("1") == 0) {
			writeMemo();
		}
		else if (menu.compare("2") == 0) {
			searchMenu();
		}
		else if (menu.compare("3") == 0) {
			cout << "프로그램을 종료합니다." << endl;
		}
		else {
			cout << "올바른 메뉴 번호가 아닙니다. 다시 입력해주세요. (press any key) " << endl;
			_getch();
		}
	} while (menu != "3");
}

void MemoManager::writeMemo()
{
	cout << "\n새 메모 작성 " << endl << endl;
	//작성할 변수 선언
	string name, power = "";
	vector<string> content, tags, powers;


	do {
		//제목 입력
		cout << "제목 ▼ " << endl;
		do {
			getline(cin, name);
		} while (name == "");
		//cin.ignore();
		if (name.find("\\") != string::npos || name.find("\t") != string::npos || name.find("\/") != string::npos || name.find(":") != string::npos ||
			name.find("*") != string::npos || name.find("<") != string::npos || name.find(">") != string::npos ||
			name.find("?") != string::npos || name.find("\"") != string::npos || name.find("|") != string::npos) {
			cout << "txt 파일의 이름으로 사용할 수 없는 기호가 포함되어있습니다." << endl;
			continue;
		}
		if (overlapName(name)) {
			cout << "이름 중복" << endl;
			continue;
		}
		if (checkName(name))
			break;
	} while (true);

	do {
		//내용 입력
		content.clear();
		cout << "내용 ▼ " << endl;
		do {
			string line;
			getline(cin, line);
			if (line == "<end>") // 끝을 알리는 문자 입력후 엔터치면 끝
				break;
			content.push_back(line);
		} while (true);

	} while (!checkContent(content));

	do {
		//태그 입력
		cout << "\n태그를 입력하세요(A B C D) ▼ " << endl;
		string t;
		do {
			getline(cin, t);
		} while (t == "");
		tags = stringSplit(t, " "); // 문자열 분리
	} while (!checkTags(tags)); // 미완성

	do {
		//권한 입력
		cout << "\n권한을 입력하세요(xxx xxx) ▼ " << endl;
		string t;
		do {
			getline(cin, t);
		} while (t == "");
		powers = stringSplit(t, " "); // 문자열 분리
	} while (!checkPower(powers, power)); // 미완성

	do {
		cout << "\n메모를 저장하시겠습니까 ? ( y / n )  ";
		string save;
		getline(cin, save);
		if (!save.compare("y") || !save.compare("Y")) {
			cout << "저장되었습니다. (press any key) " << endl;
			_getch();
			break;
		}
		else if (!save.compare("n") || !save.compare("N")) {
			return;
		}
		else {
			cout << "\n올바르지 않은 입력입니다. 다시 입력해주세요." << endl;
		}
	} while (true);

	Memo memo(name, content, tags, power); // 새로운 메모 생성
	memoList.push_back(memo); // 리스트 추가
	saveMemo(memo);
}

void MemoManager::deleteMemo(string a)
{
	a += ".txt";
	const char* cstr = a.c_str();

	if (remove(cstr) != 0) {
		perror("Error deleting file");
	}
	else {
		a.erase(a.begin() + a.length() - 4, a.end());
		cout << "메모 \"" << a << "\"를 삭제하였습니다." << endl;
	}
}

vector<string> MemoManager::stringSplit(string t, string Tok)
{
	vector<string> tags;
	int index = 0;
	int cutAt;
	while ((cutAt = t.find_first_of(Tok)) != t.npos) {
		if (cutAt > 0) {
			tags.push_back(t.substr(0, cutAt));
		}
		t = t.substr(cutAt + 1);
	}
	if (t.length() > 0) {
		tags.push_back(t.substr(0, cutAt));
	}
	return tags;
}

bool MemoManager::checkName(string name) // 김인애 1차
{
	if (checkLength(name, 50) == false) { // 함수로 변경
		return false;
	}
	if (findMyChar(name) == false) {//특정문자를 찾았을 때의 동작
		return false;
	}
	return true;
}

bool MemoManager::overlapName(string name)
{
	for (int i = 0; i < memoList.size(); i++) {
		if (name.compare(memoList.at(i).getName()) == 0) {
			return true;
		}
	}
	return false;
}

bool MemoManager::checkContent(vector<string> content) // 김인애 1차
{
	int size = 0;
	for (int i = 0; i < content.size(); i++) {
		if (findMyChar(content.at(i)) == false) {//특정문자를 찾았을 때의 동작
			return false;
		}
		size += content.at(i).size();
	}

	if (size > 4000) { //길이 초과 ( 숫자는 변경 )
		cout << "내용의 길이는 1byte 이상, 4,000byte 이하이여야 합니다." << endl;
		return false;
	}
	return true;
}

bool MemoManager::checkTags(vector<string> tags) // 김인애 1차
{
	if (tags.size() > 20) { // 태그 개수 초과
		cout << "태그의 개수는 1개 이상, 20개 이하이어야 합니다" << endl;
		return false;
	}
	for (int i = 0; i < tags.size(); i++) {
		if (!findMyChar(tags.at(i))) {
			return false;
		}
		if (!checkLength(tags.at(i), 50)) {
			return false;
		}
	}
	return true;
}

bool MemoManager::findMyChar(string str)
{
	if (str.find("-") != string::npos || str.find("+") != string::npos || str.find("/") != string::npos) {
		cout << "검색 기호가 포함되었습니다." << endl;
		return false;
	}
	return true;
}

bool MemoManager::checkLength(string str, int length)
{
	if (str.length() > length) {
		cout << "길이는 " << length << "byte 이하이어야 합니다." << endl;
		return false;
	}
	return true;
}

bool MemoManager::checkSearchWords(vector<string>& searchWords, vector<string>& operation, vector<vector<string>>& slashword)
{
	int slash_count = 0;
	for (int i = 0; i < searchWords.size(); i++) {
		if (searchWords.at(i).length() == 1)
			return false;
		if (searchWords[i][0] == '+') {
			for (int j = 1; j < searchWords[i].length(); j++)
				if (searchWords[i][j] == '+' || searchWords[i][j] == '-' || searchWords[i][j] == '/')
					return false;
			operation.push_back("+");
			searchWords[i].erase(searchWords[i].begin());
		}
		else if (searchWords[i][0] == '-') {
			for (int j = 1; j < searchWords[i].length(); j++)
				if (searchWords[i][j] == '+' || searchWords[i][j] == '-' || searchWords[i][j] == '/')
					return false;
			operation.push_back("-");
			searchWords[i].erase(searchWords[i].begin());
		}
		else {
			bool flag = false; // 슬래시 만났을때 false
			bool isSlash = false;
			for (int j = 0; j < searchWords[i].length(); j++) {
				if (searchWords[i][j] == '/') {
					isSlash = true;
					if (flag == false)
						return false;
					flag = false;
				}
				else if (searchWords[i][j] == '+' || searchWords[i][j] == '-') {
					return false;
				}
				else {
					flag = true;
				}
			}
			if (flag == false)
				return false;
			if (isSlash == false)
				return false;
			slashword.push_back(stringSplit(searchWords[i], "/"));
			operation.push_back("/");
		}
	}
	return true;
}

void MemoManager::searchMenu()
{
	string menu;
	do {
		cout << "1. 태그로 검색\n2. 내용으로 검색\n3. 이름으로 검색\n4. 태그 + 내용으로 검색\n5. 이전 메뉴" << endl;
		cout << "메뉴 번호를 입력하세요 ▶ ";
		getline(cin, menu);

		if (!menu.compare("1")) {
			search_Tags();
		}
		else if (!menu.compare("2")) {
			search_Content();
		}
		else if (!menu.compare("3")) {
			search_Name();
		}
		else if (!menu.compare("4")) {
			search_Tags_Content();
		}
		else if (!menu.compare("5")) {
			break;
		}
		else {
			cout << "잘못된 입력입니다.\n" << endl;
		}
	} while (true);
}

void MemoManager::search_Tags()
{
	vector<string> searchWords;
	vector<string> operation;
	vector<vector<string>> slashword;


	while (1) {
		cout << "검색할 태그를 입력하세요(+A, -B, C/D) ▶ ";
		string words;
		getline(cin, words);
		searchWords = (stringSplit(words, " "));
		if (searchWords.size() > 10) {
			cout << "검색어는 10개 이하이어야 합니다." << endl;
			searchWords.clear();
		}
		else if (checkSearchWords(searchWords, operation, slashword)) {
			break;
		}
		else {
			cout << "잘못된 검색 구문 입니다.\n" << endl;
			searchWords.clear();
		}
	}
	searchMemo(searchWords, 1, operation, slashword);
}

void MemoManager::search_Content()
{
	vector<string> searchWords;
	vector<string> operation;
	vector<vector<string>> slashword;

	while (1) {
		cout << "검색할 내용을 입력하세요(+A, -B, C/D) ▶ ";
		string words;
		getline(cin, words);

		searchWords = stringSplit(words, " ");
		if (searchWords.size() > 10) {
			cout << "검색어는 10개 이하이어야 합니다." << endl;
			searchWords.clear();
		}
		else if (checkSearchWords(searchWords, operation, slashword)) {
			break;
		}
		else {
			cout << "잘못된 검색 구문 입니다.\n" << endl;
			searchWords.clear();
		}
	}

	searchMemo(searchWords, 2, operation, slashword);
}

void MemoManager::search_Name()
{
	vector<string> searchWords;
	vector<string> operation;
	vector<vector<string>> slashword;

	while (1)
	{
		cout << "검색할 메모의 이름을 입력하세요(+A, -B, C/D) ▶ ";
		string words;
		getline(cin, words);

		searchWords = stringSplit(words, " ");
		if (searchWords.size() > 10) {
			cout << "검색어는 10개 이하이어야 합니다." << endl;
			searchWords.clear();
		}
		else if (checkSearchWords(searchWords, operation, slashword)) {
			break;
		}
		else {
			cout << "잘못된 검색 구문 입니다.\n" << endl;
			searchWords.clear();
		}
	}

	searchMemo(searchWords, 3, operation, slashword);
}

void MemoManager::search_Tags_Content()
{
	vector<string> searchWords;
	vector<string> operation;
	vector<vector<string>> slashword;

	while (1)
	{
		cout << "검색할 메모의 태그와 내용을 입력하세요(+A, -B, C/D) ▶ ";
		string words;
		getline(cin, words);

		searchWords = stringSplit(words, " ");
		if (searchWords.size() > 10) {
			cout << "검색어는 10개 이하이어야 합니다." << endl;
			searchWords.clear();
		}
		else if (checkSearchWords(searchWords, operation, slashword)) {
			break;
		}
		else {
			cout << "잘못된 검색 구문 입니다.\n" << endl;
			searchWords.clear();
		}
	}

	searchMemo(searchWords, 4, operation, slashword);
}

void MemoManager::searchMemo(vector<string> searchWords, int menu_flag, vector<string> operation, vector<vector<string>> slashword)
{
	vector<int> tempMemoNumList;
	//입력된 값을 전체 메모 리스트에서 검색
	// + : and , - : not , / : or , " ": and
	for (int i = 0; i < memoList.size(); i++) {
		if (searching(menu_flag, i, searchWords, operation, slashword)) {
			tempMemoNumList.push_back(i);
		}
	}

	if (!tempMemoNumList.empty()) {
		showMemoList(tempMemoNumList);      //검색한 메모 리스트 출력
		tempMemoNumList.clear();
	}
	else {
		cout << "검색된 메모가 없습니다." << endl;
	}
}

bool MemoManager::searching(int menu_flag, int index, vector<string>& searchWords, vector<string>& operation, vector<vector<string>>& slashword) {
	string str = "", str2 = "";
	if (menu_flag == 4) { //태그+내용 검색
		for (int j = 0; j < memoList[index].getContent().size(); j++)
			str.append(memoList[index].getContent().at(j));
	}
	else if (menu_flag == 2) { // 내용 검색
		for (int i = 0; i < memoList[index].getContent().size(); i++) {
			str.append(memoList[index].getContent().at(i));
		}
	}
	else if (menu_flag == 3) { // 이름 검색
		str = memoList[index].getName();
	}

	for (int i = 0; i < operation.size(); i++) {
		bool flag = false;
		if (operation[i].compare("/")) {
			if (menu_flag == 1 || menu_flag == 4) {
				for (int j = 0; j < memoList[index].getTags().size(); j++) {
					if (searchWords[i].compare(memoList[index].getTags().at(j)) == 0) {
						flag = true;
					}
				}
			}
			if (menu_flag != 1 && flag == false) {
				//메모의 태그 중 검색한 단어와 같은 것이 있다면 flag = true
				flag = (str.find(searchWords[i]) != string::npos);
			}
			//operation이 + 라면 true
			bool oper = operation[i] == "+" ? true : false;
			//검색 조건에 맞지 않으면 함수 종료
			if (flag != oper) return false;
		}
	}

	//슬래쉬로 나누어진 단어는 따로 검색
	if (!slashword.empty()) {
		for (int i = 0; i < slashword.size(); i++) {
			int count = 0;
			for (int j = 0; j < slashword[i].size(); j++) {
				if (menu_flag == 4 || menu_flag == 1) {// 1번, 4번
					if (menu_flag == 4) {// 4번일때 추가조건
						if (str.find(slashword[i][j]) != string::npos)
							count++;
					}
					for (int k = 0; k < memoList[index].getTags().size(); k++) {
						if (slashword[i][j].compare(memoList[index].getTags()[k]) == 0) {
							count++;
						}
					}
				}
				else if (str.find(slashword[i][j]) != string::npos)
					count++;
			}
			if (count == 0)//검색해야 하는 단어를 한개도 찾지 못했을 때는 false 반환
				return false;
		}
	}
	return true;
}


//유저와 onwer의 관계 판단 , 유저=ownergroup(1), user!=ownergroup(2)
int MemoManager::checkCorrelation(string userID, string groupName)
{
	////user와 owner가 같으면
	//if (userID.compare()) { return 0; }

	////user가 owner는 아니지만 owner와 같은 그룹일때
	//else if () { return 1; }

	////user는 owner가 아니고 owner와 다른 그룹일때
	//else { return 2; }
}

//검색하려는 메모에 권한이 있는지 검사
bool MemoManager::checkPermissiones(string userID, string permission)
{
	if (permission.compare("000000")) {
		return false;
	}
	else {
		return true;
	}
}

void MemoManager::showMemoList(vector<int> tempMemoNumList)
{
	//검색한 메모 리스트 출력
	for (int i = 0; i < tempMemoNumList.size(); i++) {
		cout << i + 1 << ") ";
		memoList[tempMemoNumList[i]].showMemoSimple();
	}

	string menu;
	do {
		cout << "1. 정렬\n2. 메모 확인\n3. 이전 메뉴" << endl;
		cout << "메뉴 번호를 입력하세요 ▶ ";
		getline(cin, menu);
		if (!menu.compare("1")) {
			ascend(tempMemoNumList);
		}
		else if (!menu.compare("2")) {
			//메모 확인
			string select;
			int num;
			do {
				cout << "메모 번호를 입력하세요 ▶ ";
				getline(cin, select);
				stringstream ss(select);
				if ((ss >> num).fail()) {
					cout << "잘못된 입력입니다.\n" << endl;
					continue;
				}
				else
					break;
			} while (true);

			string userID;
			string permission = "111111";
			string groupName;

			//유저와 owner와 관계를 판단하는 함수
			int j = 0;
			switch (checkCorrelation(userID, groupName))
			{
			case 0:
				break;
			case 1:
				j = 0;
				break;
			case 2:
				j = 1;
				break;
			default:
				break;
			}

			//만약 권한이 한개도 없다면
			if (!checkPermissiones(userID, permission)) {
				cout << "메모에 접근 권한이 없습니다." << endl;
				continue;
			}
			else {
				permissionMenu(permission, j, tempMemoNumList, num);
			}

		}
		else if (!menu.compare("3")) {
			break;
		}
		else {
			cout << "잘못된 입력입니다.\n" << endl;
		}
	} while (!menu.compare("1") || menu.compare("2"));
}

void MemoManager::permissionMenu(string permission, int j, vector<int> tempMemoNumList, int num) {

	//같은 그룹일때 permission에서 앞에 3개를 끊어서 t/f 구분
	//다른 그룹일때 뒤에 3개를 끊어서 t/f구분
	string select;
	vector<int> index;
	int count = 0;  bool flag = false;
	for (int i = (0 + (j * 3)); i < (3 + (j * 3)); i++) {
		int t = permission.at(i) - '0';
		if (t) {
			if (i == 0 || i == 3) {
				cout << (++count) + ". 메모 읽기" << endl;
				index.push_back(1);
				flag = true;
			}
			else if (i == 1 || i == 4) {
				cout << (++count) + ". 메모 수정" << endl;
				index.push_back(2);
			}
			else {
				cout << (++count) + ". 메모 권한 변경" << endl;
				index.push_back(3);
			}
		}
	}
	getline(cin, select);


	if (!select.compare("1")) {
		switch (index[0])
		{
		case 1:
			//메모 출력
			showSearchedMemo(tempMemoNumList, num);
			break;
		case 2:
			//메모 수정
			modifyMenu(flag, tempMemoNumList, num);
			break;
		case 3:
			//메모 권한 변경
			modifyPermission();
			break;
		default:
			break;
		}
	}
	else if (!select.compare("2")) {
		switch (index[1])
		{
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		default:
			break;
		}
	}
	else if (!select.compare("3")) {
		switch (index[2])
		{
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		default:
			break;
		}
	}
}

void MemoManager::modifyMenu(bool flag, vector<int> tempMemoNumList, int num) {

	//읽기 권한이 있으면 메모 출력 후 메뉴 출력
	if (flag) {
		showSearchedMemo(tempMemoNumList, num);
	}

	do {
		string select;
		cout << "1. 메모 수정\n2. 메모 삭제" << endl;
		getline(cin, select);

		//메모 수정
		if (!select.compare("1")) {
			break;
		}
		//메모 삭제
		else if (!select.compare("2")) {
			string select2;
			do {
				cout << "메모를 삭제 하시겠습니까? ( y / n ) ";
				getline(cin, select2);
				if (!select2.compare("y")) {
					deleteMemo(memoList[tempMemoNumList[num - 1]].getName());
					memoList.erase(memoList.begin() + (num - 1));
					break;
				}
				else if ((!select2.compare("n"))) {
					break;
				}
				else {
					cout << "잘못된 입력값입니다." << endl;
				}
			} while (true);
		}
		else {
			cout << "잘못된 입력입니다." << endl;
			continue;
		}
	} while (true);
	

}

//권한 변경 함수
void MemoManager::modifyPermission() {
	do {
		cout << "변경할 권한을 입력해주세요 ▶ ";
		string permission;
		getline(cin, permission);
		if (permission.length() == 6) {
			for (int i = 0; i < 6; i++) {
				if (permission[i] != '1' && permission[i] != '0') {
					cout << "잘못된 입력입니다." << endl;
					continue;
				}
			}
			break;
		}
		else {
			cout << "잘못된 입력입니다." << endl;
			continue;
		}
	} while (true);
	cout << "권한이 변경되었습니다." << endl;
}

void MemoManager::showSearchedMemo(vector<int> tempMemoNumList, int position)
{
	position--;      //선택된 값에서 -1 해서 다시 인덱스로 변경
	if (position >= tempMemoNumList.size() || position < 0) {
		cout << "잘못된 입력입니다.\n" << endl;
	}
	else {
		memoList[tempMemoNumList[position]].showMemo();
	}
}


/////////////////////////////////////////////////////////////////////////////


void MemoManager::ascend(vector<int>& list)
{
	string menu;

	do {

		cout << "1. 제목 오름차순\n2. 제목 내림차순\n3. 날짜 오름차순\n4. 날짜 내림차순" << endl;
		cout << "메뉴 번호를 입력하세요 ▶ ";
		getline(cin, menu);
		if (!menu.compare("1")) {
			name_ascend(list);
			for (int i = 0; i < list.size(); i++) {
				cout << i + 1 << ") ";
				memoList.at(list.at(i)).showMemoSimple();
			}
			break;
		}
		else if (!menu.compare("2")) {
			name_decend(list);
			for (int i = 0; i < list.size(); i++) {
				cout << i + 1 << ") ";
				memoList.at(list.at(i)).showMemoSimple();
			}
			break;
		}
		else if (!menu.compare("3")) {
			time_ascend(list);
			for (int i = 0; i < list.size(); i++) {
				cout << i + 1 << ") ";
				memoList.at(list.at(i)).showMemoSimple();
			}
			break;
		}
		else if (!menu.compare("4")) {
			time_decend(list);
			for (int i = 0; i < list.size(); i++) {
				cout << i + 1 << ") ";
				memoList.at(list.at(i)).showMemoSimple();
			}
			break;
		}
		else {
			cout << "잘못 입력했습니다." << endl;
		}
	} while (true);
}

void MemoManager::name_ascend(vector<int>& list)
{

	for (int i = 0; i < list.size() - 1; i++) {
		for (int j = i + 1; j < list.size(); j++) {

			if (strcmp(memoList.at(list.at(i)).getName().c_str(), memoList.at(list.at(j)).getName().c_str()) > 0) {
				int n = list.at(i);
				list.at(i) = list.at(j);
				list.at(j) = n;
			}
		}
	}
}

void MemoManager::name_decend(vector<int>& list)
{
	for (int i = 0; i < list.size() - 1; i++) {
		for (int j = i + 1; j < list.size(); j++) {

			if (strcmp(memoList.at(list.at(i)).getName().c_str(), memoList.at(list.at(j)).getName().c_str()) < 0) {
				int n = list.at(i);
				list.at(i) = list.at(j);
				list.at(j) = n;
			}
		}
	}
}

void MemoManager::time_ascend(vector<int>& list)
{
	for (int i = 0; i < list.size() - 1; i++) {
		for (int j = i + 1; j < list.size(); j++) {
			if (strcmp(memoList.at(list.at(i)).getDate().at(2).c_str(), memoList.at(list.at(j)).getDate().at(2).c_str()) > 0) {
				int n = list.at(i);
				list.at(i) = list.at(j);
				list.at(j) = n;
			}
			else if (strcmp(memoList.at(list.at(i)).getDate().at(2).c_str(), memoList.at(list.at(j)).getDate().at(2).c_str()) == 0) {
				if (strcmp(memoList.at(list.at(i)).getDate().at(0).c_str(), memoList.at(list.at(j)).getDate().at(0).c_str()) > 0) {
					int m = list.at(i);
					list.at(i) = list.at(j);
					list.at(j) = m;
				}
				else if (strcmp(memoList.at(list.at(i)).getDate().at(0).c_str(), memoList.at(list.at(j)).getDate().at(0).c_str()) == 0) {
					if (strcmp(memoList.at(list.at(i)).getDate().at(1).c_str(), memoList.at(list.at(j)).getDate().at(1).c_str()) > 0) {
						int k = list.at(i);
						list.at(i) = list.at(j);
						list.at(j) = k;
					}
				}
			}

		}
	}
}

void MemoManager::time_decend(vector<int>& list)
{
	for (int i = 0; i < list.size() - 1; i++) {
		for (int j = i + 1; j < list.size(); j++) {
			if (strcmp(memoList.at(list.at(i)).getDate().at(2).c_str(), memoList.at(list.at(j)).getDate().at(2).c_str()) < 0) {
				int n = list.at(i);
				list.at(i) = list.at(j);
				list.at(j) = n;
			}
			else if (strcmp(memoList.at(list.at(i)).getDate().at(2).c_str(), memoList.at(list.at(j)).getDate().at(2).c_str()) == 0) {
				if (strcmp(memoList.at(list.at(i)).getDate().at(0).c_str(), memoList.at(list.at(j)).getDate().at(0).c_str()) < 0) {
					int m = list.at(i);
					list.at(i) = list.at(j);
					list.at(j) = m;
				}
				else if (strcmp(memoList.at(list.at(i)).getDate().at(0).c_str(), memoList.at(list.at(j)).getDate().at(0).c_str()) == 0) {
					if (strcmp(memoList.at(list.at(i)).getDate().at(1).c_str(), memoList.at(list.at(j)).getDate().at(1).c_str()) < 0) {
						int k = list.at(i);
						list.at(i) = list.at(j);
						list.at(j) = k;
					}
				}
			}

		}
	}
}

void MemoManager::loginMenu()
{
	string menu;
	do
	{
		cout << "1. 로그인\n2. 회원가입\n3. 종료\n";
		cout << "메뉴 번호를 입력하세요 ▶ ";
		getline(cin, menu);
		if (menu.compare("1") == 0) { //로그인

		}
		else if (menu.compare("2") == 0) { //회원가입
			regi();
		}
		else if (menu.compare("3") == 0) {
			cout << "프로그램을 종료합니다." << endl;
			break;
		}
		else {
			cout << "올바른 메뉴 번호가 아닙니다. 다시 입력해주세요. (press any key) " << endl;
			_getch();
		}

	} while (true);
}

void MemoManager::regi()
{
	system("cls");
	string id;
	string pass;

	do
	{
		cout << "사용할 아이디를 입력하세요 ▶";
		getline(cin, id);
		bool check = true;
		if (id.find(" ") != -1) {
			cout << "공백은 입력 받을 수 없습니다." << endl;
			continue;
		}
		for (int i = 0; i < id.length(); i++) {
			if ((id.at(i) >= 'a' && id.at(i) <= 'z') || (id.at(i) >= 'A' && id.at(i) <= 'Z') || (id.at(i) >= '0' && id.at(i) <= '9'));
			else {
				cout << "영어 또는 숫자만 입력해주세요." << endl;
				check = false;
				break;
			}

		}
		if (!check)
			continue;
		for (int i = 0; i < userList.size(); i++) {
			if (id.compare(userList.at(i).getId()) == 0) {
				cout << "아이디가 중복됩니다. 다시입력하세요" << endl;
				check = false;
				break;
			}
		}
		if (check)
			break;

	} while (true);

	do
	{
		cout << "사용할 비밀번호를 입력하세요 ▶";
		getline(cin, id);
		bool check = true;
		if (id.find(" ") != -1) {
			cout << "공백은 입력 받을 수 없습니다." << endl;
			continue;
		}
		for (int i = 0; i < id.length(); i++) {
			if ((id.at(i) >= 'a' && id.at(i) <= 'z') || (id.at(i) >= 'A' && id.at(i) <= 'Z') || (id.at(i) >= '0' && id.at(i) <= '9'));
			else {
				cout << "영어 또는 숫자만 입력해주세요." << endl;
				check = false;
				break;
			}

		}
		if (!check)
			continue;

		if (check)
			break;

	} while (true);

	User user(id, pass);
	userList.push_back(user);
}

bool MemoManager::checkPower(vector<string> powers, string& power)
{
	if (powers.size() == 2) {
		if (powers.at(0).length() == 3 && powers.at(1).length() == 3) {
			for (int j = 0; j < 2; j++) {
				for (int i = 0; i < 3; i++) {
					if (powers.at(j)[i] == '1' || powers.at(j)[i] == '0') {
						power += powers.at(j)[i];
					}
					else {
						return false;
					}
				}
			}

		}
		else {
			return false;
		}
	}
	else
		return false;

	return true;
}
