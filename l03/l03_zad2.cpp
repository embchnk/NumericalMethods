#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <string>
#include <algorithm>

// Zadanie 2
class Zadanie2 {
public:
	Zadanie2();
	void fill();
	void exc();
	double returnFieldVal(int i, int j);

private:
	std::vector<int> A;
	std::vector<int> B;
	std::vector<int> C;
	std::vector<int> D;
	int x_max, x_min, y_max, y_min;
	double dx, dy, u0, TOL, omega;
	std::vector<std::vector<double> > v;
};
/***************************************************************************/
Zadanie2::Zadanie2()
	: A 		({ 85, 85 })
	, B 		({ 100, 85 })
	, C 		({ 100, 70 })
	, D 		({ 115, 70 })
	, dx 		(1.0)
	, dy 		(1.0)
	, x_max (200)
	, x_min (1)
	, y_max (100)
	, y_min (1)
	, u0 		(1.0)
	, TOL 	(10e-9)
	, omega (1.9)
{
	v =	*(new std::vector<std::vector<double> >(101, std::vector<double>(201)));
	fill();
}
/***************************************************************************/
void Zadanie2::fill() {
	// zerowanie
	for (int i = 0; i < v.size(); ++i) {
		for (int j = 0; j < v[0].size(); ++j)
			v[i][j] = 0;
	}
	// lewy i prawy brzeg
	for (int i = y_min; i <= y_max; ++i) {
		v[i][x_min] = u0 * x_min;
		v[i][x_max] = u0 * x_max;
	}
// 	// dolny brzeg
// 	for (int i = x_min; i <= x_max; ++i)
// 		v[y_min][i] = u0 * x_min;
// 	// górny brzeg
// 	for (int i = x_min; i <= x_max; ++i) {
// 		if (i == A[0]) {
// 			for (int j = A[1]; j <= y_max; ++j)
// 				v[j][A[0]] = u0 * y_max;
// 			for (i; i <= B[0]; ++i)
// 				v[A[1]][i] = u0 * y_max;
// 			i -= 1;
// 			for (int j = C[1]; j <= B[1]; ++j)
// 				v[j][C[0]] = u0 * y_max;
// 			for (i; i <= D[0]; ++i)
// 				v[D[1]][i] = u0 * y_max;
// 			i -= 1;
// 			for (int j = D[1]; j <= y_max; ++j)
// 				v[j][i] = u0 * y_max;
// 		}
// 		v[y_max][i] = u0 * y_max;
// 	}
}
/***************************************************************************/
void Zadanie2::exc() {
	double a = 0.;
	double aPrev = 1.;
	int iCounter = 0;
	std::ofstream file2;
	file2.open("dat/dane4.dat");

	while (fabs(a - aPrev) / aPrev > TOL) {
		// dolny brzeg
		for (int i = x_min; i <= x_max; ++i)
			v[y_min][i] = v[y_min + 1][i];
		// górny brzeg
		for (int i = x_min; i <= x_max; ++i) {
			if (i == A[0]) {
				for (int j = A[1]; j <= y_max; ++j)
					v[j][A[0]] = v[j][A[0] - 1];
				for (i; i <= B[0]; ++i)
					v[A[1]][i] = v[A[1] - 1][i];
				i -= 1;
				for (int j = C[1]; j <= B[1]; ++j)
					v[j][C[0]] = v[j][C[0] - 1];
				for (i; i <= D[0]; ++i)
					v[D[1]][i] = v[D[1] - 1][i];
				i -= 1;
				for (int j = D[1]; j <= y_max; ++j)
			 		v[j][i] = v[j][i + 1];
			 	v[A[1]][A[0]] = 0.5 * (v[A[1] - 1][A[0]] + v[A[1]][A[0] - 1]);
				v[C[1]][C[0]] = 0.5 * (v[C[1] - 1][C[0]] + v[C[1]][C[0] - 1]);
				v[D[1]][D[0]] = 0.5 * (v[D[1] + 1][D[0]] + v[D[1]][D[0] - 1]);
				i = D[0] + 1;
			}
			v[y_max][i] = v[y_max - 1][i];
		}	

		aPrev = a;
		a = 0;
		for (int j = x_min + dx; j < x_max; ++j) {
			for (int i = y_min + dy; i < y_max; ++i) {
				if ((j < A[0] || j > D[0]) ||
						(j >= A[0] && j < B[0] && i < A[1]) || 
						(j >= C[0] && j <= D[0] && i < D[1])) {
					v[i][j] = returnFieldVal(i, j);
					a += (v[i + 1][j] - v[i - 1][j]) * (v[i + 1][j] - v[i - 1][j]) + 
						 (v[i][j + 1] - v[i][j - 1]) * (v[i][j + 1] - v[i][j - 1]);
				}
			}
		}
		a /= 8.;
		++iCounter;
		file2 << iCounter << " " << a << std::endl;
	}

	std::cout << iCounter << std::endl;

	std::ofstream file;
	file.open("dat/dane3.dat");
	for (int i = 1; i < v.size(); ++i) {
		for (int j = 1; j < v[0].size(); ++j)
			file << j << " " << i << " " << v[i][j] << std::endl;;
		file << std::endl;
  }
	file.close();
	file2.close();
}
/***************************************************************************/
double Zadanie2::returnFieldVal(int i, int j) {
	return (1 - omega) * v[i][j] + 0.25 * omega * 
				 (v[i - 1][j] + v[i][j - 1] + v[i + 1][j] + v[i][j + 1]);
}
/***************************************************************************/
int main(void) {
	Zadanie2 test = Zadanie2();
	test.exc();
	return 0;
}