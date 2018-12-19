#include <iostream>
#include <fstream>
#include <string>
#include "d:/myarsenal/readFile/readfile.h"
#include "d:/myarsenal/pystring.h"
#include <unordered_map>
#include <vector>
#include <algorithm>
using namespace std;

int calc_tf() {
	string txt;
	getContent("e:/corpus/gwgz/train.txt", txt);
	//cout << txt << endl;
	wstring wtxt = pystring::s2ws(txt);
	unordered_map<wchar_t, int> c2n;
	/*c2n.insert(make_pair(L'中', 1));
	c2n.insert(make_pair(L'国', 1));
	cout << c2n.size() << endl;
	locale loc("chs");
	wcout.imbue(loc);
	wcout << L"我是" << endl;
	for (auto it : c2n)
	wcout << it.first<< endl;*/
	cout << wtxt.size() << endl;
	for (auto it : wtxt)
		++c2n[it];
	vector<pair<int, wchar_t>> n2c;
	for (auto it : c2n)
		n2c.push_back(make_pair(it.second, it.first));
	sort(n2c.begin(), n2c.end());
	cout << n2c.size() << endl;
	reverse(n2c.begin(), n2c.end());
	locale loc("chs");
	wcout.imbue(loc);
	//for (auto it : n2c)
	//	wcout << it.second << " " << it.first << endl;
	ofstream out("gwgz_features.txt");
	wstring s = L"";
	for (auto it : n2c)
		out << pystring::ws2s(s + it.second) << " " << it.first << endl;
	out.close();
}

void calc_cpls() {
	unordered_map<wchar_t, pair<int, int>> w2nn;
	ifstream fin("gwgz_features.txt");
	string word;
	wchar_t ch;
	int n;
	wstring s = L"";
	while (!fin.eof()) {
		fin >> word >> n;
		ch = (pystring::s2ws(word))[0];
		w2nn.insert(make_pair(ch, make_pair(n, 0)));
	}
	fin.close();
	ifstream fin2("xyj_features.txt");
	cout << 12 << endl;
	while (!fin2.eof()) {
		fin2 >> word >> n;
		ch = (pystring::s2ws(word))[0];
		cout << word << endl;
		if (w2nn.find(ch) == w2nn.end())
			w2nn.insert(make_pair(ch, make_pair(0, n)));
		else
			w2nn[ch].second = n;
	}
	fin2.close();
	cout << 123 << endl;
	ofstream out("features.txt");
	for (auto it : w2nn)
		out << pystring::ws2s(s + it.first) << " " << it.second.first << " " << it.second.second << "\n";
	out.close();
	unordered_map<wchar_t, pair<double, double>> pcls;
	int sum1 = 0, sum2 = 0;
	for (auto it : w2nn) {
		sum1 += it.second.first;
		sum2 += it.second.second;
	}
	for (auto it : w2nn) {
		pcls.insert(make_pair(it.first, make_pair((it.second.first + 1.0) / (sum1 + w2nn.size()), (it.second.second + 1.0) / (sum2 + w2nn.size()))));
	}
	ofstream outpcls("pcls.txt");
	for (auto it : pcls)
		outpcls << pystring::ws2s(s + it.first) << " " << it.second.first << " " << it.second.second << "\n";
}