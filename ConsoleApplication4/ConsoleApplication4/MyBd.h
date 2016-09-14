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
	int in, cost;
	vector<int> out;
	string name;
	bd(string &s, int i, int c) :name(s), in(i), cost(c){}
	bd() :name("unknown"), in(0), cost(0){}
	void clr(){ in = 0; cost = 0; out.clear(); name = "unknown"; }
	void pr(){
		cout << name << "\t Äîõîä: " << in << "\t Îñòàòîê:" << cost << "\t Ðàñõîäû:";
		if (out.size() == 0)
			cout << "ðàñõîäîâ ïîêà íåò.";
		for (int j = 0; j<out.size(); ++j)
			cout << out[j] << ' ';
		cout << endl;
	}
	void sca(ifstream &i){
		clr();
		string s;
		int t;
		i >> name >> in >> cost;
		getline(i, s);
		stringstream ss(s);
		cost = in;
		ss >> t;
		while (ss){
			cost -= t;
			out.push_back(t);
			ss >> t;
		}
	}
	void sc(){
		cin >> name >> in;
		cost = in;
	}
	void add(int o){
		out.push_back(o);
		cost -= o;
	}
	void editin(int newin){
		int d = newin - in;
		cost += d;
		in = newin;
	}
};

bool operator < (const bd &l, const bd &r) {
	return l.name<r.name;
}

set<bd> load(const string &nof){
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
