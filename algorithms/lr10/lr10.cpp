#include <fstream>                                  
#include <iostream> 
#include <vector>
#include <utility> 
#include <stdlib.h> 



std::ifstream fin("input.txt");
std::ofstream fout("output.txt");
using massiv = std::vector<std::pair<long int, long int>>;
long int k;
bool is_sorted(massiv& a, long n)
{
	long i, temp;
	for (i = 0; i < n; i++)
	{
		if (!(temp = abs(a[i].second - i))) continue;
		if (temp % k)
		{
			if (a[i + temp % k].first == a[i].first) if (!((a[i + temp % k].second - i) % k))
			{
				i += temp % k;
				continue;
			}
			return false;
		}
	}
	return true;
}

void quicksort(massiv& a, long l, long r)
{
	long int i = l;
	long int j = r;
	//std::pair<long int, long int>& pivot = a[(i + j) / 2];
	long int pivot = a[(i + j) / 2].first;
	//long int pivot = a[distribution(generator) % (r + 1) + l];
	while (i <= j)
	{
		while (a[i].first < pivot)
		{
			i++;
		}
		//if (a[i].first == pivot.first && a[i].second < pivot.second) std::swap(a[i].second, pivot.second);
		while (a[j].first > pivot) j--;
		if (i <= j)
		{
			if(a[i].first != a[j].first)std::swap(a[i], a[j]);
			i++;
			j--;
		}
	}
	if (j > l) quicksort(a, l, j);
	if (i < r) quicksort(a, i, r);
}

int main()
{

	long int n;
	fin >> n >> k;
	if (k == 1) {
		fout << "YES"; return 0;
	}
	massiv a(n);
	for (long i = 0; i < n; i++) 
	{
		fin >> a[i].first;
		a[i].second = i;
	}
	quicksort(a, 0, n - 1);
	if (is_sorted(a, n)) fout << "YES";
	else fout << "NO";
	return 0;
}

/*
bool is_sorted(massiv& a, long n)
{
	long i;
	for (i = 1; i < n; i++) if (a[i] < a[i - 1]) return false;
	return true;
}
int main()
{

	long int n, k;
	fin >> n >> k;
	if (k == 1) {
		fout << "YES"; return 0;
	}
	massiv a(n);
	for (long i = 0; i < n; i++) fin >> a[i];
	for (long i = 0; i + k < n; i++)
	{
		for (long j = i; j + k < n; j+=k)
		{
			if (a[i] > a[j + k]) {
				std::swap(a[i], a[j + k]);
			}
		}
	}
	if (is_sorted(a, n)) fout << "YES";
	else fout << "NO";
	return 0;
}



*/
