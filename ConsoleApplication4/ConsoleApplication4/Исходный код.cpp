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

set<bd> data;
const char nof[] = "bd.txt"; // NameOfFile nof

void printall(ostream &out, bool console){// printing data in out stream
	for (const auto &it: data){
		if (it.name == "unknown")
			continue;
		if (console)
			cout << "Accaunt login: ";
		out << it.name << "\t";
		if (console)
			cout << "Income: ";
		out << it.in << "\t";
		if (console){
			if (it.out.size() > 0)
				cout << "Purchases: ";
			else
				cout << "Without spending.";
			for (int j = 0; j<it.out.size(); ++j)
				out << it.out[j] << ' ';
			out << endl;
			cout << "--------Balance: ";
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
	cout << "Welcome to home accounting program Sweet Home Pro.";
	data = load(nof);
	cout << (data).size() << " accounts loaded.\n";
	while (cin){
		cout << "Available commands:\n";
		cout << "1 - Create new account.\n";
		cout << "2 - Add new purchase.\n";
		cout << "3 - Edit account.\n";
		cout << "4 - Show account info.\n";
		cout << "5 - Show accouts list.\n";
		cout << "6 - Print full details of all accounts on the screen.\n";
		cout << "0 - Exit.\n";
		com = -11235813;
		cin >> com;
		if (com == -11235813){			
			cout << "Uncorrect input. It completed the program.\n";
			break;
		}
		system("cls");

		if (com == 1){
			cout << "Input data in format: Name Income\n";
			bd a;
			a.sc();
			if ((data).find(a) == (data).end()){
				(data).insert(a);
				cout << "Account " << a.name << " created.\n";
			}
			else
				cout << "The account with the same name already exists.\n";
		}
		if (com == 2){
			cout << "Enter your account name and consumption.\n";
			string name;
			int out;
			cin >> name >> out;
			bd a(name, 0, 0);
			set<bd>::iterator it = (data).find(a);
			if (it == (data).end())
				cout << "This account does not exist.\n";
			else{
				a = *it;
				if (a.cost<out){
					cout << "Consumption exceeds the account balance.\n";
				}
				else{
					a.add(out);
					(data).erase(a);
					(data).insert(a);
					cout << "Done.\n";
				}
			}
		}
		if (com == 3){
			cout << "Input account name:\n";
			string name;
			int out;
			cin >> name;
			bd a(name, 0, 0);
			set<bd>::iterator it = (data).find(a);
			if (it == (data).end())
				cout << "This account does not exist.\n";
			else{
				a = *it;
				int c;
				cout << "1 - For edit account name\n";
				cout << "2 - For edit account income.\n";
				cin >> c;
				if (c>2 || c<1)
					cout << "Input is incorrect.\n";
				else
					if (c == 1){
						cout << "Input new name: ";
						string nn;
						cin >> nn;
						data.erase(it);
						a.name = nn;
						(data).insert(a);
						cout << "done.\n";
					}
					else{
						cout << "Enter new income: ";
						int nd;
						cin >> nd;
						a.editin(nd);
						(data).erase(a);
						(data).insert(a);
						cout << "done.\n";
					}
			}
		}
		if (com == 4){
			cout << "Enter account name:\n";
			string s;
			cin >> s;
			bd a;
			a.name = s;
			set<bd>::iterator it = (data).find(a);
			if (it == (data).end())
				cout << "This account does not exist.\n";
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
	printall(ofstream(nof), 0);// download data base in file
}
