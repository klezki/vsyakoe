#include <fstream>                                  
#include <iostream> 
#include <vector>
#include <utility> 
#include <string>
#include <random>



std::ifstream fin("input.txt");
std::ofstream fout("output.txt");
using massiv = std::vector<long int>;
void quicksort(massiv&, long, long);
long int k1, k2;
std::random_device rd;
std::default_random_engine generator(rd());
std::uniform_int_distribution<long  unsigned> distribution(0, 4294967295UL);
int main()
{
	long int n, A, B, C, a1, a2;
	fin >> n >> k1 >> k2;
	fin >> A >> B >> C >> a1 >> a2;
	massiv a(n);
	a[0] = a1;
	a[1] = a2;
	for (long i = 2; i < n; i++) a[i] = A * a[i - 2] + B * a[i - 1] + C;
	quicksort(a, 0, n - 1);
	for (long i = k1 - 1; i < k2; i++) fout << a[i] << ' ';
	return 0;
}

void quicksort(massiv& a, long l, long r)
{
	long int i = l;
	long int j = r;
	long int pivot = a[(i + j) / 2];
	//long int pivot = a[distribution(generator) % (r + 1) + l];
	while (i <= j)
	{
		while (a[i] < pivot) i++;
		while (a[j] > pivot) j--;
		if (i <= j)
		{
			std::swap(a[i], a[j]);
			i++;
			j--;
		}
	}
	if (j + 1 >= k1) if (j > l) quicksort(a, l, j);
	if (i < r) quicksort(a, i, r);
	if (r + 1 >= k2)
	{
		for (i = k1 - 1; i < k2; i++) fout << a[i] << ' ';
		exit(0);
	}
}
