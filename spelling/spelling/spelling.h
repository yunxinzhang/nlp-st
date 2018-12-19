#include <iostream>
#include "D:/myarsenal/pystring.h"
#include <string>
#include "D:/myarsenal/readFile/readfile.h"
#include "../../min_edit_distance/min_edit_distance/med.h"
#include <fstream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
using namespace std;

void new_corpus() {
	string txt;
	getContent("e:/corpus/aesopa10.txt", txt);
	//cout << txt << endl;
	ofstream out("aesopa10_words.txt");
	string word = "";
	bool flag = true;
	for (int i = 0; i < txt.size(); ++i) {
		if ((txt[i] >= 'a' && txt[i] <= 'z') || (txt[i] >= 'A' && txt[i] <= 'Z') || txt[i] == '\'') {
			if ((txt[i] >= 'A' && txt[i] <= 'Z'))
				word += (txt[i] + 32);
			else
				word += txt[i];
		}
		else if (word.size() > 0) {
			out << word << "\n";
			word = "";
		}
	}
	out.close();
}

unordered_set<string> load_dict() {
	unordered_set<string> s;
	ifstream fin("ap_dict.txt");
	string word;
	while (!fin.eof()) {
		fin >> word;
		s.insert(word);
	}
	fin.close();
	return s;
}
unordered_map<string,int> load_w2n() {
	unordered_map<string, int> s;
	ifstream fin("ap_dict.txt");
	string word;
	int cnt = 0;
	while (!fin.eof()) {
		fin >> word;
		++cnt;
		s[word]++;
	}
	s["$"] = cnt;
	fin.close();
	return s;
}

unordered_map<string, int> load_ww2n() {
	unordered_map<string, int> s;
	ifstream fin("ap_dict.txt");
	string word1, word2;
	int cnt = 0;
	fin >> word1;
	while (!fin.eof()) {
		fin >> word2;
		s[word1+" "+word2]++;
		word1 = word2;
		++cnt;
	}
	s["$"] = cnt;
	fin.close();
	return s;
}

vector<string> candidate_generate(string word, unordered_set<string> &dict) {
	vector<string> v;
	for (auto it : dict) {
		if (it != word && min_edit_distance(word, it) <= 2)
			v.push_back(it);
	}
	v.push_back(word);
	if (word.size() > 2) {
		for (int i = 1; i < word.size() - 1; ++i) {
			string word1 = word.substr(0, i);
			string word2 = word.substr(i);
			if (dict.find(word1) != dict.end() && dict.find(word2) != dict.end())
				v.push_back(word1 + " " + word2);
			if (dict.find(word1 + "-" + word2) != dict.end())
				v.push_back(word1 + "-" + word2);
		}
	}
	return v;
}
bool cmp(pair<double, string> a, pair<double, string> b) {
	return a.first > b.first;
}
vector<pair<double, string>> use_a_bi_gram(const string word, const string afterword, 
	unordered_set<string> &dict , 
	unordered_map<string, int> &w2n,
	unordered_map<string, int>& ww2n) {
	vector<string> v = candidate_generate(word, dict);
	vector<pair<double, string>> ans;
	for (auto it : v) {
		auto n = w2n.find(it);
		if (n != w2n.end()) {
			//cout << it << " " << n->second << " " << ((ww2n.find(it + " fox") != ww2n.end()) ? ww2n.at(it + " fox") : 0) << endl;
			auto wwn = ww2n.find(it + " " + afterword);
			if (wwn != ww2n.end())
				ans.push_back(make_pair(1.0*wwn->second*n->second, it));
			else
				ans.push_back(make_pair(0.0, it));
		}
		else {
			//cout << it << " " << "inf" << endl;
			ans.push_back(make_pair(-1, it));
		}
	}
	sort(ans.begin(), ans.end(), cmp);
	return ans;
}