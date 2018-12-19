#include "n_gram.h"
int main() {

	string txt;
	getContent("E:/corpus/aesopa10.txt", txt);
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