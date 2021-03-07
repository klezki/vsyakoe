#include <vector>
#include "edx-io.hpp"



void findfirstlast (std::vector<long>& a, long key)
{
	long l = -1;
	long r = a.size();
	long m;
	while (r > l + 1)
	{
		m = (l + r) / 2;
		if (a[m] < key) l = m;
		else r = m;
	}
	if (r < a.size() && a[r] == key) io << r + 1 << ' ';
	else 
	{
		io << -1 << ' ' << -1 << '\n';
		return;
	}
	l = -1;
	r = a.size();
	while (r > l + 1)
	{
		m = (l + r) / 2;
		if (a[m] <= key) l = m;
		else r = m;
	}
	if (l >= 0 && a[l] == key) io << l + 1 << '\n';
}


int main()
{
	long n, m;
	io >> n;
	std::vector<long> a(n);
	for (long i = 0; i < n; i++) io >> a[i];
	io >> m;
	for (long i = 0; i < m; i++)
	{
		io >> n;
		findfirstlast(a, n);
	}
	return 0;
}

