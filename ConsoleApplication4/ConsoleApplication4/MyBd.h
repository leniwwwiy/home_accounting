#include <iostream>
#include <set>                      
#include <vector>					
#include <string>
#include <cstdio>  
#include <sstream>
#include <clocale>
#include <fstream>

using namespace std;

struct bd{
	int in, cost; // доход и остаток соотв.
	vector<int> out;// список расходов
	string name;// имя
	bd(string &s, int i, int c) :name(s), in(i), cost(c){}
	bd() :name("unknown"), in(0), cost(0){}// по умолчанию конструктор
	void clr(){ in = 0; cost = 0; out.clear(); name = "unknown"; }// функция-метод "почистить" обнуляет всё
	void pr(){// функция-метод вывода на экран
		cout << name << "\t Доход: " << in << "\t Остаток:" << cost << "\t Расходы:";
		if (out.size() == 0)
			cout << "расходов пока нет.";
		for (int j = 0; j<out.size(); ++j)
			cout << out[j] << ' ';
		cout << endl;
	}
	void sca(ifstream &i){// функция-метод считывания элемента из указанного входного потока
		clr();
		string s;
		int t;
		i >> name >> in >> cost;
		getline(i, s);// читаем всю оставшуюся строку
		stringstream ss(s);// запихиваем в строковый потоковый буфер 
		cost = in;
		ss >> t; // и из него по одному инты вытягиваем как обычно
		while (ss){
			cost -= t;
			out.push_back(t);
			ss >> t;
		}
	}
	void sc(){// просто считать имя и доход для создания новой учетки с расчётом остатка
		cin >> name >> in;
		cost = in;
	}
	void add(int o){// добавить расход с расчётом остатка
		out.push_back(o);
		cost -= o;
	}
	void editin(int newin){// изменить доход и рассчитать остаток
		int d = newin - in;
		cost += d;
		in = newin;
	}
};

bool operator < (const bd &l, const bd &r) {// оператор сравнения для элементов БД
	return l.name<r.name;
}

set<bd> load(const string &nof){// загрузить все учётки которые в файле
	ifstream in(nof);
	set<bd> data;
	if (!in)
		return data;
	bd a;
	do{
		a.sca(in);
		data.insert(a);
	} while (in);
	in.close();
	a.name = "unknown";
	data.erase(a);
	return data;
}