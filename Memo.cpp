#include "Memo.h"

Memo::Memo(string name, vector<string> content, vector<string> tags, string power)
	:name(name), content(content), tags(tags), power(power)
{
	//date �������ֱ�
	this->date = today();
}

Memo::Memo(string name, vector<string> date, vector<string> content, vector<string> tags, string power, string owner)
	:name(name), date(date), content(content), tags(tags), power(power), owner(owner)
{
}

vector<string> Memo::today() {
	vector<string> today;
	time_t current_time;
	time(&current_time);
	string date = ctime(&current_time);
	//date�� ��ĭ ������ �ɰ��� �� �� �� ������ ���Ϳ� ����

	istringstream iss(date);
	int cnt = 0;

	do
	{
		string sub;
		iss >> sub;
		if (cnt == 1 || cnt == 2 || cnt == 4) {
			//cout << " print : " << sub << endl;
			//today.push_back(sub);
			if (cnt == 1) {
				if (!sub.compare("Jan"))
					today.push_back("1");
				else if (!sub.compare("Feb"))
					today.push_back("2");
				else if (!sub.compare("Mar"))
					today.push_back("3");
				else if (!sub.compare("Apr"))
					today.push_back("4");
				else if (!sub.compare("May"))
					today.push_back("5");
				else if (!sub.compare("June"))
					today.push_back("6");
				else if (!sub.compare("July"))
					today.push_back("7");
				else if (!sub.compare("Aug"))
					today.push_back("8");
				else if (!sub.compare("Sept"))
					today.push_back("9");
				else if (!sub.compare("Oct"))
					today.push_back("10");
				else if (!sub.compare("Nov"))
					today.push_back("11");
				else if (!sub.compare("Dec"))
					today.push_back("12");
			}
			else
				today.push_back(sub);
		}
		cnt++;
	} while (iss);
	// [4],[1],[2]
	return today;
}

string Memo::getName()
{
	return name;
}

vector<string>& Memo::getDate()
{
	return date;
}

vector<string>& Memo::getContent()
{
	return content;
}

vector<string>& Memo::getTags()
{
	return tags;
}

string Memo::getPower()
{
	return power;
}

string Memo::getOwner() {
	return owner;
}

void Memo::showMemo()
{
	cout << "�ƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢ�\n" << endl;
	cout << "���� ��\n" << name << endl;
	cout << "�ۼ��� ��\n" << owner << endl;
	cout << "\n�ۼ��� ��\n";
	for (int i = 0; i < date.size(); i++)
		cout << date.at(i) << " ";
	cout << endl;
	cout << "\n���� ��" << endl;
	for (int i = 0; i < content.size(); i++)
		cout << content.at(i) << endl;
	cout << "\n�±� ��" << endl;
	for (int i = 0; i < tags.size(); i++)
		cout << "#" << tags.at(i) << " ";
	cout << "\n���� ��" << endl;
	cout << power << " ";
	cout << endl;
	cout << "\n�ƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢ�" << endl;

}

void Memo::showMemoSimple()
{
	cout << name << "\t";
	for (int i = 0; i < date.size(); i++) {
		cout << date.at(i) << ".";
	}
	cout << endl;
}