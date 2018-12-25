#include <iostream>
#include <Eigen>
#include <random>
#include <ctime>
#include <cmath>
using namespace std;
using namespace Eigen;

int main() {
	Eigen::Vector3f x[4];
	x[0] = { 0, 0, 1 };
	x[1] = { 0, 1, 1 };
	x[2] = { 1, 0, 1 };
	x[3] = { 1, 1, 1 };
	int y[4] = { 0, 0, 0, 1 }; // or, and
	double b;
	Eigen::Vector3f w, wprev;
	// init para
	srand(clock());
	w[2] = (rand() % 100 + 1.0) / 1000;
	w[0] = (rand() % 100 + 1.0) / 1000;
	w[1] = (rand() % 100 + 1.0) / 1000;
	cout << "init w:" << endl;
	cout << w << endl;
	
	double lr = 0.1; // learing rate
	double yp;		  // predict y
	int iter = 0;	
	double diff;	
	double cri = 0.00001;
	while (true || ++iter < 100000) {
		for (int i = 0; i < 4; ++i) {
			// forword;
			yp = x[i].dot(w) + b;
			// diff; activation = 'sigmoid'
			diff = y[i] - 1.0 /( pow(2.71828, -yp)+1 );
			// backword
			w += lr * x[i] * diff;
		}
		
		if ((w - wprev).norm() < cri) {
			cout << "diff(wprev,w) small enought." << endl;
			break;
		}
		wprev = w;
	}
	cout << "ans w:" << endl;
	cout << w << endl;
	

	cin.get();
}