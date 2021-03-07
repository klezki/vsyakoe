#include <fstream>     
#include <vector>
#include <string>
#include <queue>
#include <algorithm>



long size;

std::ifstream fin("input.txt");
std::ofstream fout("output.txt");


struct ohbabyaquadriple
{
	long key;
	long l;
	long r;
	long pops;
};



long find(std::vector<ohbabyaquadriple>& a, long key)
{
	long i = 0;
	while (i != -1 && key != a[i].key)
	{
		if (key < a[i].key) i = a[i].l;
		else  i = a[i].r;
	}
	return i;
}


void countdel(std::vector<ohbabyaquadriple>& a, long i)
{
	if (a[i].l != -1) countdel(a, a[i].l);
	if (a[i].r != -1) countdel(a, a[i].r);
	size--;
	return;
}

void deleteq(std::vector<ohbabyaquadriple>& a, long i)
{
	if (i == -1) return;
	if (i == 0)
	{
		size = 0;
		return;
	}
	if (a[a[i].pops].l == i) a[a[i].pops].l = -1;
	else a[a[i].pops].r = -1;
	long j = i;
	countdel(a, i);
}





int main()
{
	long N;
	fin >> N;
	size = N;
	std::vector<ohbabyaquadriple> a(N);
	a[0].pops = -1;
	for (long i = 0; i < N; i++)
	{
		fin >> a[i].key;
		fin >> a[i].l;
		a[i].l--;
		if (a[i].l != -1) a[a[i].l].pops = i;
		fin >> a[i].r;
		a[i].r--;
		if (a[i].r != -1) a[a[i].r].pops = i;
	}
	fin >> N;
	for (long i = 0; i < N; i++)
	{
		long key;
		fin >> key;
		deleteq(a, find(a, key));
		fout << size << '\n';
	}

	return 0;
}
