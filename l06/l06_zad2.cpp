#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <string>
#include <algorithm>

// Zadanie 1
class Zadanie1 {
public:
	Zadanie1();
	void exc();
	void fill();
private:
	int nx, ny, t;
	double d, dt, TOL, k, ro, c, h;
	std::vector<std::vector<double> > T;
	std::vector<std::vector<double> > nextT;
	std::vector<std::vector<int> > mask;
};
/***************************************************************************/
Zadanie1::Zadanie1()
	: nx		(100)
	, ny		(50)
	, d 		(1)
	, k			(1)
	, ro 		(1)
	, c 		(1)
	, t 		(5000)
	, TOL		(1e-6)
	, h 		(0.01)
	, dt 		(2.5)
{
	T =	*(new std::vector<std::vector<double> >(ny + 1, std::vector<double>(nx + 1)));
	nextT = *(new std::vector<std::vector<double> >(ny + 1, std::vector<double>(nx + 1)));
	mask = *(new std::vector<std::vector<int> >(ny + 1, std::vector<int>(nx + 1)));
	fill();
}
/***************************************************************************/
void Zadanie1::fill() {
	for (int j = 0; j <= ny; ++j) {
		for (int i = 0; i <= nx; ++i) {
			T[j][i] = 0;
			nextT[j][i] = 0;
			mask[j][i] = 1;
		}
	}


	// mask
	for (int j = 41; j <= ny; ++j) {
		for (int i = 1; i < 80; ++i)
			mask[j][i] = 0;
	}
	for (int j = 30; j <= 40; ++j) {
		for (int i = 51; i < 80; ++i)
			mask[j][i] = 0;
	}
	for (int j = 0; j < 30; ++j) {
		for (int i = 21; i < 80; ++i)
			mask[j][i] = 0;
	}
	for (int j = 21; j < 30; ++j) {
		for (int i = 80; i < 100; ++i)
			mask[j][i] = 0;
	}
	// T - 25
	for (int j = 40; j <= 50; ++j) {
		mask[j][0] = 1;
		T[j][0] = 25;
	}
	// T - 20
	for (int i = 20; i <= 80; ++i) {
		mask[0][i] = 1;
		T[0][i] = 20;
	}
	// T - 10
	for (int j = 20; j <= 30; ++j) {
		mask[j][nx] = 1;
		T[j][nx] = 10;
	}

	
	// krawedzie pionowe
	for (int j = 0; j < 30; ++j)
		mask[j][20] = -1;
	for (int j = 30; j <= 40; ++j)
		mask[j][50] = -1;
	for (int j = 0; j <= 20; ++j)
		mask[j][80] = -5;
	for (int j = 30; j <= ny; ++j)
		mask[j][80] = -5;

	// krawedzie poziome
	for (int i = 0; i <= 50; ++i)
		mask[40][i] = -3;
	for (int i = 20; i <= 50; ++i)
		mask[30][i] = -7;
	for (int i = 0; i < 80; ++i)
		mask[ny][i] = -7;
	for (int i = 80; i <= nx; ++i) {
		mask[20][i] = -3;
		mask[30][i] = -7;
	}

	// rogi
	mask[40][50] = -2; 
	mask[20][80] = -4;
	mask[30][80] = -6;
	mask[30][50] = -8;
}
/***************************************************************************/
void Zadanie1::exc() {
	double S = 0;
	double prevS = 100;
	int iCounter = 0;
	std::ofstream file;
	std::string s = "dat/zad2";

	nextT = T;

	for (double n = 0; n <= t; n += dt) {
		prevS = 100;
		S = 0;
		T = nextT;
		if (!((int)n % 1000)) {
			file.open(s + std::to_string((int)n) + ".dat");
			for (int j = 0; j <= ny; ++j) {
				for (int i = 0; i <= nx; ++i)
					file << i << " " << j << " " << nextT[j][i] << std::endl;
				file << std::endl;
			}
			file.close();
		}

		while (fabs(S - prevS) / prevS > TOL) {
			prevS = S;
			S = 0;
			for (int j = 0; j <= ny; ++j) {
				for (int i = 0; i <= nx; ++i) {
					switch (mask[j][i]) {
					case 0:
						nextT[j][i] = (1. / 6) * (T[j][i] + 1.25 * (T[j-1][i] + T[j+1][i] +
							T[j][i-1] + T[j][i+1] - (4 * T[j][i]) + nextT[j-1][i] + nextT[j+1][i] +
							nextT[j][i-1] + nextT[j][i+1]));
						break;
					case -1:
						nextT[j][i] = nextT[j][i+1] / (h + 1);
						break;
					case -2:
						nextT[j][i] = nextT[j+1][i+1] / (std::sqrt(2) * h + 1);
						break;
					case -3:
						nextT[j][i] = nextT[j+1][i] / (h + 1);
						break;
					case -4:
						nextT[j][i] = nextT[j+1][i+1] / (std::sqrt(2) * h + 1);
						break;
					case -5:
						nextT[j][i] = nextT[j][i-1] / (h + 1);
						break;
					case -6:
						nextT[j][i] = nextT[j-1][i-1] / (std::sqrt(2) * h + 1);
						break;
					case -7:
						nextT[j][i] = nextT[j-1][i] / (h + 1);
						break;
					case -8:
						nextT[j][i] = nextT[j-1][i+1] / (std::sqrt(2) * h + 1);
						break;
					default:
						break;
					}
					if (mask[j][i] == 0)
						S += fabs(nextT[j][i]);
				}
			}
		}
	}
}
/***************************************************************************/
int main(void) {
	Zadanie1 test = Zadanie1();
	test.exc();
	return 0;
}
