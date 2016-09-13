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

set<bd> data;// набор учёток. хранится в виде бинарного дерева поиска чтобы искать и получать доступ, удалять и изменять за быстрое время o(log(n))
const char nof[] = "bd.txt"; // NameOfFile nof имя файла для БД

void printall(ostream &out, bool console){// вывод всех учёток в указанный выходной поток
	for (const auto &it: data){// ну и выводим всё по порядку в лексикографическом порядке
		if (it.name == "unknown")
			continue;
		if (console)
			cout << "Учетная запись: ";
		out << it.name << "\t";
		if (console)
			cout << "Доход: ";
		out << it.in << "\t";
		if (console){
			if (it.out.size() > 0)
				cout << "Расходы: ";
			else
				cout << "Расходов пока нет.";
			for (int j = 0; j<it.out.size(); ++j)
				out << it.out[j] << ' ';
			out << endl;
			cout << "--------Остаток: ";
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
	cout << "Вас приветствует программа домашней бухгалтерии Sweet Home Pro.";
	data = load(nof);
	cout << "Загружено " << (data).size() << " учётных записей.\n";
	while (cin){
		cout << "Доступные команды:\n";
		cout << "1 - Создать новую учетную запись.\n";
		cout << "2 - Добавить расход к учетной записи.\n";
		cout << "3 - Редактировать учетную запись.\n";
		cout << "4 - Вывести информацию о учетной записи.\n";
		cout << "5 - Вывести имена всех существующих учетных записей.\n";
		cout << "6 - Вывести полную детализацию всех учётных записей на экран.\n";
		cout << "0 - Выход из программы.\n";
		com = -11235813;
		cin >> com;
		if (com == -11235813){			
			cout << "Некорректный ввод. Программа будет завершена.\n";
			break;
		}
		system("cls");

		if (com == 1){
			cout << "Введите данные в формате: Имя Доход\n";
			bd a;
			a.sc();
			if ((data).find(a) == (data).end()){
				(data).insert(a);
				cout << "Учетная запись " << a.name << " создана.\n";
			}
			else
				cout << "Учетная запись с таким именем уже существует.\n";
		}
		if (com == 2){
			cout << "Введите имя учетной записи и расход.\n";
			string name;
			int out;
			cin >> name >> out;
			bd a(name, 0, 0);// создаём элемент с именем какое нам надо
			set<bd>::iterator it = (data).find(a);// итератор ищет элемент а
			if (it == (data).end())
				cout << "Такой учетной записи не существует.\n";
			else{
				a = *it;// переприсваиваем чтобы в а был не пустой элемент только с именем, а то что мы нашли с таким именем
				if (a.cost<out){// если на учётке денег меньше чем ты хочешь потратить
					cout << "Расход привышает остаток счета.\n";
				}
				else{
					a.add(out);// изменяем а
					(data).erase(a);// удаляем то что было
					(data).insert(a);// обратно запихиваем новый измененный элемент
					cout << "Успешно.\n";// так надо. иначе не работает и так будет везде
				}
			}
		}
		if (com == 3){
			cout << "Введите имя учетной записи.\n";
			string name;
			int out;
			cin >> name;
			bd a(name, 0, 0);// тоже самое
			set<bd>::iterator it = (data).find(a);
			if (it == (data).end())
				cout << "Такой учетной записи не существует.\n";
			else{
				a = *it;
				int c;
				cout << "1 - Для изменения имени учетной записи\n";
				cout << "2 - Для изменения дохода.\n";
				cin >> c;
				if (c>2 || c<1)
					cout << "Ошибка ввода.\n";
				else
					if (c == 1){
						cout << "Введите новое имя: ";
						string nn;
						cin >> nn;
						data.erase(it);
						a.name = nn;
						(data).insert(a);
						cout << "Успешно.\n";
					}
					else{
						cout << "Введите новый доход: ";
						int nd;
						cin >> nd;
						a.editin(nd);
						(data).erase(a);
						(data).insert(a);
						cout << "Успешно.\n";
					}
			}
		}
		if (com == 4){
			cout << "Введите имя учетной записи:\n";
			string s;
			cin >> s;
			bd a;
			a.name = s;
			set<bd>::iterator it = (data).find(a);
			if (it == (data).end())
				cout << "Учетная запись с таким именем не найдена.\n";
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
	printall(ofstream(nof), 0);// напечатать в поток
}