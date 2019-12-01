#include "MemoManager.h"

MemoManager::MemoManager()
{
}

void MemoManager::loadData() {
	//������
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
	//���� ��ο��� txt���� Ž��

	//txtNames�� ���ϸ���� ����ִ� ����
	//�ҷ����� �ϸ�ȴ�
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

	//content �Է�
	for (int i = 0; i < memo.getContent().size(); i++) {
		out << memo.getContent()[i] << endl;
	}
	out << "+" << endl;
	//tag �Է�
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
		cout << "1. �޸� �ۼ�\n2. �޸� �˻�\n3. �� ��" << endl;
		cout << "�޴� ��ȣ�� �Է��ϼ��� �� ";
		getline(cin, menu);
		if (menu.compare("1") == 0) {
			writeMemo();
		}
		else if (menu.compare("2") == 0) {
			searchMenu();
		}
		else if (menu.compare("3") == 0) {
			cout << "���α׷��� �����մϴ�." << endl;
		}
		else {
			cout << "�ùٸ� �޴� ��ȣ�� �ƴմϴ�. �ٽ� �Է����ּ���. (press any key) " << endl;
			_getch();
		}
	} while (menu != "3");
}

void MemoManager::writeMemo()
{
	cout << "\n�� �޸� �ۼ� " << endl << endl;
	//�ۼ��� ���� ����
	string name, power = "";
	vector<string> content, tags, powers;


	do {
		//���� �Է�
		cout << "���� �� " << endl;
		do {
			getline(cin, name);
		} while (name == "");
		//cin.ignore();
		if (name.find("\\") != string::npos || name.find("\t") != string::npos || name.find("\/") != string::npos || name.find(":") != string::npos ||
			name.find("*") != string::npos || name.find("<") != string::npos || name.find(">") != string::npos ||
			name.find("?") != string::npos || name.find("\"") != string::npos || name.find("|") != string::npos) {
			cout << "txt ������ �̸����� ����� �� ���� ��ȣ�� ���ԵǾ��ֽ��ϴ�." << endl;
			continue;
		}
		if (overlapName(name)) {
			cout << "�̸� �ߺ�" << endl;
			continue;
		}
		if (checkName(name))
			break;
	} while (true);

	do {
		//���� �Է�
		content.clear();
		cout << "���� �� " << endl;
		do {
			string line;
			getline(cin, line);
			if (line == "<end>") // ���� �˸��� ���� �Է��� ����ġ�� ��
				break;
			content.push_back(line);
		} while (true);

	} while (!checkContent(content));

	do {
		//�±� �Է�
		cout << "\n�±׸� �Է��ϼ���(A B C D) �� " << endl;
		string t;
		do {
			getline(cin, t);
		} while (t == "");
		tags = stringSplit(t, " "); // ���ڿ� �и�
	} while (!checkTags(tags)); // �̿ϼ�

	do {
		//���� �Է�
		cout << "\n������ �Է��ϼ���(xxx xxx) �� " << endl;
		string t;
		do {
			getline(cin, t);
		} while (t == "");
		powers = stringSplit(t, " "); // ���ڿ� �и�
	} while (!checkPower(powers, power)); // �̿ϼ�

	do {
		cout << "\n�޸� �����Ͻðڽ��ϱ� ? ( y / n )  ";
		string save;
		getline(cin, save);
		if (!save.compare("y") || !save.compare("Y")) {
			cout << "����Ǿ����ϴ�. (press any key) " << endl;
			_getch();
			break;
		}
		else if (!save.compare("n") || !save.compare("N")) {
			return;
		}
		else {
			cout << "\n�ùٸ��� ���� �Է��Դϴ�. �ٽ� �Է����ּ���." << endl;
		}
	} while (true);

	Memo memo(name, content, tags, power); // ���ο� �޸� ����
	memoList.push_back(memo); // ����Ʈ �߰�
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
		cout << "�޸� \"" << a << "\"�� �����Ͽ����ϴ�." << endl;
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

bool MemoManager::checkName(string name) // ���ξ� 1��
{
	if (checkLength(name, 50) == false) { // �Լ��� ����
		return false;
	}
	if (findMyChar(name) == false) {//Ư�����ڸ� ã���� ���� ����
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

bool MemoManager::checkContent(vector<string> content) // ���ξ� 1��
{
	int size = 0;
	for (int i = 0; i < content.size(); i++) {
		if (findMyChar(content.at(i)) == false) {//Ư�����ڸ� ã���� ���� ����
			return false;
		}
		size += content.at(i).size();
	}

	if (size > 4000) { //���� �ʰ� ( ���ڴ� ���� )
		cout << "������ ���̴� 1byte �̻�, 4,000byte �����̿��� �մϴ�." << endl;
		return false;
	}
	return true;
}

bool MemoManager::checkTags(vector<string> tags) // ���ξ� 1��
{
	if (tags.size() > 20) { // �±� ���� �ʰ�
		cout << "�±��� ������ 1�� �̻�, 20�� �����̾�� �մϴ�" << endl;
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
		cout << "�˻� ��ȣ�� ���ԵǾ����ϴ�." << endl;
		return false;
	}
	return true;
}

bool MemoManager::checkLength(string str, int length)
{
	if (str.length() > length) {
		cout << "���̴� " << length << "byte �����̾�� �մϴ�." << endl;
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
			bool flag = false; // ������ �������� false
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
		cout << "1. �±׷� �˻�\n2. �������� �˻�\n3. �̸����� �˻�\n4. �±� + �������� �˻�\n5. ���� �޴�" << endl;
		cout << "�޴� ��ȣ�� �Է��ϼ��� �� ";
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
			cout << "�߸��� �Է��Դϴ�.\n" << endl;
		}
	} while (true);
}

void MemoManager::search_Tags()
{
	vector<string> searchWords;
	vector<string> operation;
	vector<vector<string>> slashword;


	while (1) {
		cout << "�˻��� �±׸� �Է��ϼ���(+A, -B, C/D) �� ";
		string words;
		getline(cin, words);
		searchWords = (stringSplit(words, " "));
		if (searchWords.size() > 10) {
			cout << "�˻���� 10�� �����̾�� �մϴ�." << endl;
			searchWords.clear();
		}
		else if (checkSearchWords(searchWords, operation, slashword)) {
			break;
		}
		else {
			cout << "�߸��� �˻� ���� �Դϴ�.\n" << endl;
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
		cout << "�˻��� ������ �Է��ϼ���(+A, -B, C/D) �� ";
		string words;
		getline(cin, words);

		searchWords = stringSplit(words, " ");
		if (searchWords.size() > 10) {
			cout << "�˻���� 10�� �����̾�� �մϴ�." << endl;
			searchWords.clear();
		}
		else if (checkSearchWords(searchWords, operation, slashword)) {
			break;
		}
		else {
			cout << "�߸��� �˻� ���� �Դϴ�.\n" << endl;
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
		cout << "�˻��� �޸��� �̸��� �Է��ϼ���(+A, -B, C/D) �� ";
		string words;
		getline(cin, words);

		searchWords = stringSplit(words, " ");
		if (searchWords.size() > 10) {
			cout << "�˻���� 10�� �����̾�� �մϴ�." << endl;
			searchWords.clear();
		}
		else if (checkSearchWords(searchWords, operation, slashword)) {
			break;
		}
		else {
			cout << "�߸��� �˻� ���� �Դϴ�.\n" << endl;
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
		cout << "�˻��� �޸��� �±׿� ������ �Է��ϼ���(+A, -B, C/D) �� ";
		string words;
		getline(cin, words);

		searchWords = stringSplit(words, " ");
		if (searchWords.size() > 10) {
			cout << "�˻���� 10�� �����̾�� �մϴ�." << endl;
			searchWords.clear();
		}
		else if (checkSearchWords(searchWords, operation, slashword)) {
			break;
		}
		else {
			cout << "�߸��� �˻� ���� �Դϴ�.\n" << endl;
			searchWords.clear();
		}
	}

	searchMemo(searchWords, 4, operation, slashword);
}

void MemoManager::searchMemo(vector<string> searchWords, int menu_flag, vector<string> operation, vector<vector<string>> slashword)
{
	vector<int> tempMemoNumList;
	//�Էµ� ���� ��ü �޸� ����Ʈ���� �˻�
	// + : and , - : not , / : or , " ": and
	for (int i = 0; i < memoList.size(); i++) {
		if (searching(menu_flag, i, searchWords, operation, slashword)) {
			tempMemoNumList.push_back(i);
		}
	}

	if (!tempMemoNumList.empty()) {
		showMemoList(tempMemoNumList);      //�˻��� �޸� ����Ʈ ���
		tempMemoNumList.clear();
	}
	else {
		cout << "�˻��� �޸� �����ϴ�." << endl;
	}
}

bool MemoManager::searching(int menu_flag, int index, vector<string>& searchWords, vector<string>& operation, vector<vector<string>>& slashword) {
	string str = "", str2 = "";
	if (menu_flag == 4) { //�±�+���� �˻�
		for (int j = 0; j < memoList[index].getContent().size(); j++)
			str.append(memoList[index].getContent().at(j));
	}
	else if (menu_flag == 2) { // ���� �˻�
		for (int i = 0; i < memoList[index].getContent().size(); i++) {
			str.append(memoList[index].getContent().at(i));
		}
	}
	else if (menu_flag == 3) { // �̸� �˻�
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
				//�޸��� �±� �� �˻��� �ܾ�� ���� ���� �ִٸ� flag = true
				flag = (str.find(searchWords[i]) != string::npos);
			}
			//operation�� + ��� true
			bool oper = operation[i] == "+" ? true : false;
			//�˻� ���ǿ� ���� ������ �Լ� ����
			if (flag != oper) return false;
		}
	}

	//�������� �������� �ܾ�� ���� �˻�
	if (!slashword.empty()) {
		for (int i = 0; i < slashword.size(); i++) {
			int count = 0;
			for (int j = 0; j < slashword[i].size(); j++) {
				if (menu_flag == 4 || menu_flag == 1) {// 1��, 4��
					if (menu_flag == 4) {// 4���϶� �߰�����
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
			if (count == 0)//�˻��ؾ� �ϴ� �ܾ �Ѱ��� ã�� ������ ���� false ��ȯ
				return false;
		}
	}
	return true;
}


//������ onwer�� ���� �Ǵ� , ����=ownergroup(1), user!=ownergroup(2)
int MemoManager::checkCorrelation(string userID, string groupName)
{
	////user�� owner�� ������
	//if (userID.compare()) { return 0; }

	////user�� owner�� �ƴ����� owner�� ���� �׷��϶�
	//else if () { return 1; }

	////user�� owner�� �ƴϰ� owner�� �ٸ� �׷��϶�
	//else { return 2; }
}

//�˻��Ϸ��� �޸� ������ �ִ��� �˻�
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
	//�˻��� �޸� ����Ʈ ���
	for (int i = 0; i < tempMemoNumList.size(); i++) {
		cout << i + 1 << ") ";
		memoList[tempMemoNumList[i]].showMemoSimple();
	}

	string menu;
	do {
		cout << "1. ����\n2. �޸� Ȯ��\n3. ���� �޴�" << endl;
		cout << "�޴� ��ȣ�� �Է��ϼ��� �� ";
		getline(cin, menu);
		if (!menu.compare("1")) {
			ascend(tempMemoNumList);
		}
		else if (!menu.compare("2")) {
			//�޸� Ȯ��
			string select;
			int num;
			do {
				cout << "�޸� ��ȣ�� �Է��ϼ��� �� ";
				getline(cin, select);
				stringstream ss(select);
				if ((ss >> num).fail()) {
					cout << "�߸��� �Է��Դϴ�.\n" << endl;
					continue;
				}
				else
					break;
			} while (true);

			string userID;
			string permission = "111111";
			string groupName;

			//������ owner�� ���踦 �Ǵ��ϴ� �Լ�
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

			//���� ������ �Ѱ��� ���ٸ�
			if (!checkPermissiones(userID, permission)) {
				cout << "�޸� ���� ������ �����ϴ�." << endl;
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
			cout << "�߸��� �Է��Դϴ�.\n" << endl;
		}
	} while (!menu.compare("1") || menu.compare("2"));
}

void MemoManager::permissionMenu(string permission, int j, vector<int> tempMemoNumList, int num) {

	//���� �׷��϶� permission���� �տ� 3���� ��� t/f ����
	//�ٸ� �׷��϶� �ڿ� 3���� ��� t/f����
	string select;
	vector<int> index;
	int count = 0;  bool flag = false;
	for (int i = (0 + (j * 3)); i < (3 + (j * 3)); i++) {
		int t = permission.at(i) - '0';
		if (t) {
			if (i == 0 || i == 3) {
				cout << (++count) + ". �޸� �б�" << endl;
				index.push_back(1);
				flag = true;
			}
			else if (i == 1 || i == 4) {
				cout << (++count) + ". �޸� ����" << endl;
				index.push_back(2);
			}
			else {
				cout << (++count) + ". �޸� ���� ����" << endl;
				index.push_back(3);
			}
		}
	}
	getline(cin, select);


	if (!select.compare("1")) {
		switch (index[0])
		{
		case 1:
			//�޸� ���
			showSearchedMemo(tempMemoNumList, num);
			break;
		case 2:
			//�޸� ����
			modifyMenu(flag, tempMemoNumList, num);
			break;
		case 3:
			//�޸� ���� ����
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

	//�б� ������ ������ �޸� ��� �� �޴� ���
	if (flag) {
		showSearchedMemo(tempMemoNumList, num);
	}

	do {
		string select;
		cout << "1. �޸� ����\n2. �޸� ����" << endl;
		getline(cin, select);

		//�޸� ����
		if (!select.compare("1")) {
			break;
		}
		//�޸� ����
		else if (!select.compare("2")) {
			string select2;
			do {
				cout << "�޸� ���� �Ͻðڽ��ϱ�? ( y / n ) ";
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
					cout << "�߸��� �Է°��Դϴ�." << endl;
				}
			} while (true);
		}
		else {
			cout << "�߸��� �Է��Դϴ�." << endl;
			continue;
		}
	} while (true);
	

}

//���� ���� �Լ�
void MemoManager::modifyPermission() {
	do {
		cout << "������ ������ �Է����ּ��� �� ";
		string permission;
		getline(cin, permission);
		if (permission.length() == 6) {
			for (int i = 0; i < 6; i++) {
				if (permission[i] != '1' && permission[i] != '0') {
					cout << "�߸��� �Է��Դϴ�." << endl;
					continue;
				}
			}
			break;
		}
		else {
			cout << "�߸��� �Է��Դϴ�." << endl;
			continue;
		}
	} while (true);
	cout << "������ ����Ǿ����ϴ�." << endl;
}

void MemoManager::showSearchedMemo(vector<int> tempMemoNumList, int position)
{
	position--;      //���õ� ������ -1 �ؼ� �ٽ� �ε����� ����
	if (position >= tempMemoNumList.size() || position < 0) {
		cout << "�߸��� �Է��Դϴ�.\n" << endl;
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

		cout << "1. ���� ��������\n2. ���� ��������\n3. ��¥ ��������\n4. ��¥ ��������" << endl;
		cout << "�޴� ��ȣ�� �Է��ϼ��� �� ";
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
			cout << "�߸� �Է��߽��ϴ�." << endl;
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
		cout << "1. �α���\n2. ȸ������\n3. ����\n";
		cout << "�޴� ��ȣ�� �Է��ϼ��� �� ";
		getline(cin, menu);
		if (menu.compare("1") == 0) { //�α���

		}
		else if (menu.compare("2") == 0) { //ȸ������
			regi();
		}
		else if (menu.compare("3") == 0) {
			cout << "���α׷��� �����մϴ�." << endl;
			break;
		}
		else {
			cout << "�ùٸ� �޴� ��ȣ�� �ƴմϴ�. �ٽ� �Է����ּ���. (press any key) " << endl;
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
		cout << "����� ���̵� �Է��ϼ��� ��";
		getline(cin, id);
		bool check = true;
		if (id.find(" ") != -1) {
			cout << "������ �Է� ���� �� �����ϴ�." << endl;
			continue;
		}
		for (int i = 0; i < id.length(); i++) {
			if ((id.at(i) >= 'a' && id.at(i) <= 'z') || (id.at(i) >= 'A' && id.at(i) <= 'Z') || (id.at(i) >= '0' && id.at(i) <= '9'));
			else {
				cout << "���� �Ǵ� ���ڸ� �Է����ּ���." << endl;
				check = false;
				break;
			}

		}
		if (!check)
			continue;
		for (int i = 0; i < userList.size(); i++) {
			if (id.compare(userList.at(i).getId()) == 0) {
				cout << "���̵� �ߺ��˴ϴ�. �ٽ��Է��ϼ���" << endl;
				check = false;
				break;
			}
		}
		if (check)
			break;

	} while (true);

	do
	{
		cout << "����� ��й�ȣ�� �Է��ϼ��� ��";
		getline(cin, id);
		bool check = true;
		if (id.find(" ") != -1) {
			cout << "������ �Է� ���� �� �����ϴ�." << endl;
			continue;
		}
		for (int i = 0; i < id.length(); i++) {
			if ((id.at(i) >= 'a' && id.at(i) <= 'z') || (id.at(i) >= 'A' && id.at(i) <= 'Z') || (id.at(i) >= '0' && id.at(i) <= '9'));
			else {
				cout << "���� �Ǵ� ���ڸ� �Է����ּ���." << endl;
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
