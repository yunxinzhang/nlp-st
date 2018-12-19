#include "spelling.h"

int main() {
	unordered_set<string> dict = load_dict();
	cout << (dict.find("the")==dict.end()) << endl;
	unordered_map<string, int> w2n = load_w2n();
	unordered_map<string, int> ww2n = load_ww2n();
	cout << dict.size() << endl;
	cout << min_edit_distance("the", "hte") << endl;
	vector<string> v = candidate_generate("they", dict);
	for (auto it : v) {
		auto n = w2n.find(it);
		if (n != w2n.end()) {
			cout << it << " " << n->second << " "<< ((ww2n.find(it+" fox") != ww2n.end()) ? ww2n.at(it + " fox") : 0) << endl;
		}
		else {
			cout << it << " " << "inf" << endl;
		}
	}
	pystring::printv(v);

	vector<pair<double, string> > ans = use_a_bi_gram("hte", "said", dict, w2n, ww2n);
	for (auto it : ans)
		cout << it.first <<" "<< it.second << endl;
	cin.get();
}