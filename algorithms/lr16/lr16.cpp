#include <vector>
#include "edx-io.hpp"


int main()
{
	long n, i;
	io >> n;
	std::vector<double> a(n);
	double A;
	io >> A;
	double l = 0;
	double r = A;
	a[0] = A;
	while (r - l > 0.000000001)
	{
		a[1] = (l + r) / 2;
		for (i = 2; i < n; i++)
		{
			a[i] = 2 * a[i - 1] - a[i - 2] + 2;
			if (a[i] < 0)
			{
				l = a[1];
				break;
			}
		}
		if (i != n) continue;
		r = a[1];
	}
	io << a[n - 1];
	return 0;
}
