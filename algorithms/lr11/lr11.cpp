#include <fstream>                                  
#include <iostream> 
#include <vector>
#include <utility> 
#include <stdlib.h> 
#include <list> 



std::ifstream fin("input.txt");
std::ofstream fout("output.txt");
using massiv = std::vector<unsigned long>;


massiv countingradixsort(massiv& A, massiv& B, std::vector<unsigned long>& C, int mode)
{
	for (long i = 0; i < 256; i++) C[i] = 0;
	long long n = A.size();
	long i;
	if (mode == 1) for (i = 0; i < n; i++) C[unsigned char(A[i])]++;
	if (mode == 2) for (i = 0; i < n; i++) 
		C[unsigned char(A[i] >> 8)]++;
	if (mode == 3) for (i = 0; i < n; i++) C[unsigned char(A[i] >> 16)]++;
	if (mode == 4) for (i = 0; i < n; i++) C[unsigned char(A[i] >> 24)]++;
	for (long i = 1; i < 256; i++) C[i] += C[i - 1];
	if (mode == 1) for (i = n - 1; i >= 0; i--) B[--C[unsigned char(A[i])]] = A[i];
	if (mode == 2) for (i = n - 1; i >= 0; i--) B[--C[unsigned char(A[i] >> 8)]] = A[i];
	if (mode == 3) for (i = n - 1; i >= 0; i--) B[--C[unsigned char(A[i] >> 16)]] = A[i];
	if (mode == 4) for (i = n - 1; i >= 0; i--) B[--C[unsigned char(A[i] >> 24)]] = A[i];
	return B;
}


massiv& radixsort(massiv& a)
{
	long long n = a.size();
	massiv* pb = new massiv(n);
	std::vector<unsigned long>* pc = new std::vector<unsigned long>(256);
	std::vector<unsigned long>& C = *pc;
	massiv& B = *pb;
	a = countingradixsort(a, B, C, 1);
	a = countingradixsort(a, B, C, 2);
	a = countingradixsort(a, B, C, 3);
	a = countingradixsort(a, B, C, 4);
	delete &B , &C;
	return a;
}



int main()
{
	long long n, m = 0;
	//char ch[4];
	//n = 1600000000;
	//ch[0] = n << 56 >> 56;
	//ch[1] = n << 48 >> 56;
	//ch[2] = n << 40 >> 56;
	//ch[3] = n << 32 >> 56;
	//m = m | (long long(ch[3]) << 24);
	//m = m | (long long(ch[2]) << 16);
	//m = m | (long long(ch[1]) << 8);
	//m = m | ch[0];         //0 - 255
	fin >> n >> m;
	std::vector<unsigned long> a(n), b(m);
	for (long i = 0; i < n; i++)
	{
		fin >> a[i];
	}
	for (long i = 0; i < m; i++)
	{
		fin >> b[i];
	}
	massiv c(n*m);
	long long k = 0;
	for (long i = 0; i < n; i++)
	{
		for (long j = 0; j < m; j++)
		{
			c[k++] = a[i] * b[j];
		}
	}
	massiv& C = radixsort(c);
	k = (C.size() - 1) / 10;
	n = 0;
	m = 0;
	while (k >= 0)
	{
		m += C[n];
		n += 10;
		k--;
	}
	fout << m;
	return 0;
}
