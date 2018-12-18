#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <algorithm>
#include "D:/myarsenal/readFile/readfile.h"

using namespace std;

unordered_map<char, int>  uni(string &txt) {	
	unordered_map<char, int> ch2n;
	for (auto ch : txt) {
		if (ch >= 'A' && ch <= 'Z')
			ch += 'a' - 'A';
		++ch2n[ch];
	}
	return ch2n;
}
unordered_map<string, int> bi(string &txt) {
	unordered_map<string, int> bi2n;
	for (int i = 0; i < txt.size() - 1; ++i) {
		char ch1 = txt[i];
		if (ch1 >= 'A' && ch1 <= 'Z')
			ch1 += 'a' - 'A';
		char ch2 = txt[i + 1];
		if (ch2 >= 'A' && ch2 <= 'Z')
			ch2 += 'a' - 'A';
		++bi2n[string("") + ch1 + ch2];
	}
	return bi2n;
	/*for (auto it : bi2n)
		cout << it.first << " " << it.second << endl;*/
}
double calc_prob(string str, unordered_map<char, int> & ch2n ,unordered_map<string, int> &bi2n) {
	double sum = 0;
	for (int i = 0; i < str.size() - 1; ++i) {
		// add a very small number
		sum += log(1.0*bi2n[str.substr(i, 2)] / ch2n[str[i]]+1e-100);
	}
	sum /= (str.size() - 1);
	return sum;
}
// add one smoothing or Laplace smoothing
double calc_prob_add_one(string str, unordered_map<char, int> & ch2n, unordered_map<string, int> &bi2n) {
	double sum = 0;
	for (int i = 0; i < str.size() - 1; ++i) {
		// add a very small number
		sum += log(1.0*(bi2n[str.substr(i, 2)]+1) / (ch2n[str[i]] + ch2n.size()));
	}
	sum /= (str.size() - 1);
	return sum;
}
unordered_map<int, double> calc_nc(unordered_map<string, int> &bi2n) {
	unordered_map<int, double> nc;
	for (auto it : bi2n)
		nc[it.second]++;
	nc[0] = bi2n.size() * bi2n.size() - nc.size();
	/*vector<pair<int, double>> vv;
	for (auto it : nc)
		vv.push_back(make_pair(it.first, it.second));
	sort(vv.begin(), vv.end());
	for (int i = 0; i < vv.size(); ++i) {
		
	}
	for (auto it : vv)
		cout << it.first << " " << it.second << endl;*/
	return nc;
}
// good_turing smoothing
double calc_prob_good_turing(string str, unordered_map<char, int> & ch2n, unordered_map<string, int> &bi2n, unordered_map<int, double> &nc) {
	double sum = 0;
	for (int i = 0; i < str.size() - 1; ++i) {
		int c = bi2n[str.substr(i, 2)];
		// 进行了近似计算 max， 也可以用拟合的函数
		sum += log(1.0*(c +1)*(max(nc[c+1],1.0)/nc[c]) / ch2n[str[i]]);
	}
	sum /= (str.size() - 1);
	return sum;
}
unordered_map<char, int> calc_continuation(unordered_map<string, int> &bi2n) {
	unordered_map<char, int> cc;
	for (auto it : bi2n)
		cc[it.first[1]]++;
	return cc;
}
unordered_map<char, int> calc_continuation_head(unordered_map<string, int> &bi2n) {
	unordered_map<char, int> cc;
	for (auto it : bi2n)
		cc[it.first[0]]++;
	return cc;
}
// Kneser-Ney smoothing
double calc_prob_Kneser_Ney(string str, unordered_map<char, int> & ch2n, unordered_map<string, int> &bi2n, unordered_map<char, int> &cc, unordered_map<char, int> &cch) {
	double sum = 0;
	for (int i = 0; i < str.size() - 1; ++i) {
		sum += log(1.0*max(bi2n[str.substr(i,2)]-0.75, 0.0)/ ch2n[str[i]]  + 0.75*cch[str[i]]/ch2n[str[i]] * cc[str[i+1]]);
	}
	sum /= (str.size() - 1);
	return sum;
}
int main() {

	string txt;
	getContent("E:/copus/aesopa10.txt", txt);
	unordered_map<char, int>  ch2n = uni(txt);
	unordered_map<string, int> bi2n = bi(txt);
	unordered_map<int, double> nc = calc_nc(bi2n);
	unordered_map<char, int> cc = calc_continuation(bi2n);
	unordered_map<char, int> cch = calc_continuation_head(bi2n);
	/*for (auto it : nc)
		cout << it.first << " " << it.second << endl;*/
	
	//string strs[5] = { "speak", "speek", "speik", "speok", "speuk" };
	string strs[5] = { "said", "saad", "saed", "saod", "saud" };
	for (auto i = 0; i < 5; ++i) {
		cout << calc_prob_Kneser_Ney(strs[i], ch2n, bi2n, cc, cch) << endl;
	}
	cin.get();
}