#include <iostream>
#include <random>
#include <ctime>
#include <vector>

using namespace std;

double mean(vector<double> &v) {
	double sum = 0;
	for (auto it : v)
		sum += it;
	return sum / v.size();
}

double var(vector<double> & v, double mean) {
	double sum = 0;
	for (auto it : v) {
		sum += (it - mean) * (it - mean);
	}
	sum /= v.size();
	return sqrt(sum);
}

int main() {
	default_random_engine e;
	uniform_real_distribution<double> u(0,120);
	vector<double> data;
	int ndata = 1000000;
	for (int i = 0; i < ndata; ++i) {
		data.push_back(u(e));
	}
	cout << "data size¡¡>> " <<data.size() << endl;
	double m = mean(data);
	cout << "mean >> " << m << endl;
	double v = var(data, m);
	cout << "var >>" << v << endl;

	vector<double> means;
	vector<double> vars;
	int nsample = 100;
	int nex = 100;
	srand(clock());
	for (int i = 0; i < nsample; ++i) {
		vector<double> sv;
		for (int j = 0; j < nex; ++j) {
			int idx = rand() % ndata;
			sv.push_back(data[idx]);
		}
		double me = mean(sv);
		double mvar = var(sv, me);
		means.push_back(me);
		vars.push_back(mvar);
	}
	cout << vars[0] << endl;
	cout << vars[1] << endl;
	double smean = mean(means);
	double svar = var(means, smean);
	cout << "sample means >> " << smean << endl;
	cout << "samples var >> " << svar << endl;
	vector<int> vfveiw(120,0);
	for (auto it : means)
		vfveiw[(int)(it)]++;
	for (auto it : vfveiw) {
		for (int i = 0; i < it; ++i)
			cout << "#";
		cout << endl;
	}
	cin.get();
}