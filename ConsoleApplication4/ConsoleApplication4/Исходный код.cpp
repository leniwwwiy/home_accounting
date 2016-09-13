#include <iostream>
#include <set>                      
#include <vector>					
#include <string>
#include <cstdio>  
#include <sstream>
#include <clocale>
#include <fstream>
#include "MyBd.h"

using namespace std;

set<bd> data;// ����� ������. �������� � ���� ��������� ������ ������ ����� ������ � �������� ������, ������� � �������� �� ������� ����� o(log(n))
const char nof[] = "bd.txt"; // NameOfFile nof ��� ����� ��� ��

void printall(ostream &out, bool console){// ����� ���� ������ � ��������� �������� �����
	for (const auto &it: data){// �� � ������� �� �� ������� � ������������������ �������
		if (it.name == "unknown")
			continue;
		if (console)
			cout << "������� ������: ";
		out << it.name << "\t";
		if (console)
			cout << "�����: ";
		out << it.in << "\t";
		if (console){
			if (it.out.size() > 0)
				cout << "�������: ";
			else
				cout << "�������� ���� ���.";
			for (int j = 0; j<it.out.size(); ++j)
				out << it.out[j] << ' ';
			out << endl;
			cout << "--------�������: ";
			out << it.cost << "\n";
		}
		else{
			out << it.cost << "\t";
			for (int j = 0; j<it.out.size(); ++j)
				out << it.out[j] << ' ';
			out << endl;
		}
		
		
	}
}

int main(){
	setlocale(LC_ALL, "Russian");
	int com;
	cout << "��� ������������ ��������� �������� ����������� Sweet Home Pro.";
	data = load(nof);
	cout << "��������� " << (data).size() << " ������� �������.\n";
	while (cin){
		cout << "��������� �������:\n";
		cout << "1 - ������� ����� ������� ������.\n";
		cout << "2 - �������� ������ � ������� ������.\n";
		cout << "3 - ������������� ������� ������.\n";
		cout << "4 - ������� ���������� � ������� ������.\n";
		cout << "5 - ������� ����� ���� ������������ ������� �������.\n";
		cout << "6 - ������� ������ ����������� ���� ������� ������� �� �����.\n";
		cout << "0 - ����� �� ���������.\n";
		com = -11235813;
		cin >> com;
		if (com == -11235813){			
			cout << "������������ ����. ��������� ����� ���������.\n";
			break;
		}
		system("cls");

		if (com == 1){
			cout << "������� ������ � �������: ��� �����\n";
			bd a;
			a.sc();
			if ((data).find(a) == (data).end()){
				(data).insert(a);
				cout << "������� ������ " << a.name << " �������.\n";
			}
			else
				cout << "������� ������ � ����� ������ ��� ����������.\n";
		}
		if (com == 2){
			cout << "������� ��� ������� ������ � ������.\n";
			string name;
			int out;
			cin >> name >> out;
			bd a(name, 0, 0);// ������ ������� � ������ ����� ��� ����
			set<bd>::iterator it = (data).find(a);// �������� ���� ������� �
			if (it == (data).end())
				cout << "����� ������� ������ �� ����������.\n";
			else{
				a = *it;// ��������������� ����� � � ��� �� ������ ������� ������ � ������, � �� ��� �� ����� � ����� ������
				if (a.cost<out){// ���� �� ������ ����� ������ ��� �� ������ ���������
					cout << "������ ��������� ������� �����.\n";
				}
				else{
					a.add(out);// �������� �
					(data).erase(a);// ������� �� ��� ����
					(data).insert(a);// ������� ���������� ����� ���������� �������
					cout << "�������.\n";// ��� ����. ����� �� �������� � ��� ����� �����
				}
			}
		}
		if (com == 3){
			cout << "������� ��� ������� ������.\n";
			string name;
			int out;
			cin >> name;
			bd a(name, 0, 0);// ���� �����
			set<bd>::iterator it = (data).find(a);
			if (it == (data).end())
				cout << "����� ������� ������ �� ����������.\n";
			else{
				a = *it;
				int c;
				cout << "1 - ��� ��������� ����� ������� ������\n";
				cout << "2 - ��� ��������� ������.\n";
				cin >> c;
				if (c>2 || c<1)
					cout << "������ �����.\n";
				else
					if (c == 1){
						cout << "������� ����� ���: ";
						string nn;
						cin >> nn;
						data.erase(it);
						a.name = nn;
						(data).insert(a);
						cout << "�������.\n";
					}
					else{
						cout << "������� ����� �����: ";
						int nd;
						cin >> nd;
						a.editin(nd);
						(data).erase(a);
						(data).insert(a);
						cout << "�������.\n";
					}
			}
		}
		if (com == 4){
			cout << "������� ��� ������� ������:\n";
			string s;
			cin >> s;
			bd a;
			a.name = s;
			set<bd>::iterator it = (data).find(a);
			if (it == (data).end())
				cout << "������� ������ � ����� ������ �� �������.\n";
			else{
				a = *it;
				a.pr();
			}
		}
		if (com == 5){
			vector<bd> a((data).begin(), (data).end());
			for (int i = 0; i<a.size(); ++i)
				cout << a[i].name << ' ';
		}
		if (com == 6) printall(cout, 1);
		if (com == 0){

			break;
		}
		cout << endl << endl;
		
	}
	printall(ofstream(nof), 0);// ���������� � �����
}