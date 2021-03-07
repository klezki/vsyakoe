#include <fstream>     
#include <vector>
#include <string>
#include <queue>
#include <algorithm>




std::ifstream fin("input.txt");
std::ofstream fout("output.txt");


struct ohbabyaquadriple
{
	long key;
	long l;
	long r;

	ohbabyaquadriple() : l(-1), r(-1)
	{

	};
};



bool find(std::vector<ohbabyaquadriple>& a, long i, long min, long max)
{
	if (i == -1)
	{
		return true;
	}
	if (a[i].key <= min || a[i].key >= max)
	{
		return false;
	}
	return find(a, a[i].l, min, a[i].key) && find(a, a[i].r, a[i].key, max);
}





int main()
{
	long N;
	fin >> N;
	if (N == 0)
	{
		fout << "YES";
		return 0;
	}
	std::vector<ohbabyaquadriple> a(N);
	for (long i = 0; i < N; i++)
	{
		fin >> a[i].key;
		fin >> a[i].l;
		a[i].l--;
		fin >> a[i].r;
		a[i].r--;
	}
	fout << (find(a, 0, LONG_MIN, LONG_MAX) ? "YES" : "NO");

	return 0;
}
