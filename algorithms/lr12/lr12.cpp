#include <vector>
#include <string>
#include "edx-io.hpp"

long n, m, k;
using massiv = std::vector<std::string>;

std::vector<long> index;
massiv A;



void countingradixsort(long i)
{
	std::vector<long> B(n);
	std::vector<unsigned long> C(26);
	for (long j = 0; j < n; j++) 
		C[A[i][index[j]] - 97]++;
	for (long j = 1; j < 26; j++) 
		C[j] += C[j - 1];
	for (long j = n - 1; j >= 0; j--)
		B[--C[A[i][index[j]] - 97]] = index[j];
	index = B;
}


void radixsort(void)
{
	for (long i = m - 1; k > 0; i--, k--)
	{
		countingradixsort(i);
	}
}


int main()
{
	io >> n >> m >> k;
	A.resize(m);
	index.resize(n);
	for (long i = 0; i < n; i++) index[i] = i;
	for (long i = 0; i < m; i++)
	{
		io >> A[i];
	}
	radixsort();
	for (long i = 0; i < n; i++) io << index[i] + 1 << ' ';
}
