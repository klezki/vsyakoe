#include <fstream>     
#include <vector>
#include <string>
#include <queue>
#include <algorithm>




std::ifstream fin("input.txt");
std::ofstream fout("output.txt");


struct ohbabyatriple
{
	long key;
	long l;
	long r;
	long balance;
};



long height(std::vector<ohbabyatriple>& a, long i)
{
	long left, right;
	if (a[i].l != -1) left = height(a, a[i].l);
	else left = 0;
	if (a[i].r != -1) right = height(a, a[i].r);
	else right = 0;
	a[i].balance = right - left;
	if (left > right) return left + 1;
	else return right + 1;
}



int main()
{
	long N;
	fin >> N;
	if (N == 0)
	{
		fout << N;
		return 0;
	}
	std::vector<ohbabyatriple> a(N);
	for (long i = 0; i < N; i++)
	{
		fin >> a[i].key;
		fin >> a[i].l;
		a[i].l--;
		fin >> a[i].r;
		a[i].r--;
	}
	height(a, 0);
	for (long i = 0; i < N; i++)
	{
		fout << a[i].balance << '\n';
	}

	return 0;
}
