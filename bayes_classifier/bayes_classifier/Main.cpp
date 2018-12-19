#include "features.h"

int main() {
	unordered_map<wchar_t, pair<double, double>> pcls;
	ifstream fin2("pcls.txt");
	string word;
	double p1, p2;
	wchar_t ch;
	while (!fin2.eof()) {
		fin2 >> word >> p1 >> p2;
		ch = (pystring::s2ws(word))[0];
		//cout << word << endl;
		pcls.insert(make_pair(ch, make_pair(p1, p2)));
	}
	fin2.close();
	string txt;
	getContent("test.txt", txt);
	wstring wtxt = pystring::s2ws(txt);
	double pp1 = log(157.0/(157+1213)), pp2 = log(1213.0/(157+1213));
	for (auto it : wtxt) {
		if (pcls.find(it) == pcls.end())
			continue;
		pp1 += log(pcls.find(it)->second.first);
		pp2 += log(pcls.find(it)->second.second);
	}
	cout <<"gwgz >> "<< pp1 << endl;
	cout <<"xyj >> "<< pp2 << endl;
	if (pp1 > pp2)
		cout << "gwgz" << endl;
	else
		cout << "xyj" << endl;
	cin.get();
}
