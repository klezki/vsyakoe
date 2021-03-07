#include <fstream>     
#include <vector>
#include <functional>
#include <algorithm>


std::ifstream fin("input.txt");
std::ofstream fout("output.txt");

const long P = 25000033;
std::hash<unsigned long long> _hash2;
const short c1 = 3, c2 = 7;

//long find(const std::vector<long long>& a, const long long key)   // linear (best)
//{
//	long hash = key % P;
//	for (long i = 0; i < P && a[hash] != -1; i++)
//	{
//		if (a[hash] == key) return -1;
//		hash = (hash + 1) % P;
//	}
//	return hash;
//}


//long find(const std::vector<long long>& a, const long long key)  //quad 
//{
//	long q = 1;
//	long hash = key % P;
//	if (a[hash] != -1)
//	{
//		if (a[hash] == key) return -1;
//	}
//	else return hash;
//	long i = (hash + c1 + c2) % P;
//	while (a[i] != -1 && i != hash)
//	{
//		if (a[i] == key) return -1;
//		i = (i + 2 * c2 * q++ + c1 + c2) % P; // i = hash + c1*q + c2*q^2
//	}
//	return i;
//}


long find(const std::vector<long long>& a, const long long key)  //2hash (worst)
{

	long hash1 = key % P;
	if (a[hash1] != -1)
	{
		if (a[hash1] == key) return -1;
	}
	else return hash1;
	long hash2 = _hash2(key) % P;
	if (hash2 == 0) hash2 = 1;
	long i = (hash1 + hash2) % P;
	while (a[i] != -1 && i != hash1)
	{
		if (a[i] == key) return -1;
		i = (i + hash2) % P;
	}
	return i;
}




void fill(long long& n)
{
	n = -1;
}


int main()
{
	long i;
	short A, Ac, Ad;
	long long B, Bc, Bd, X;
	std::vector<long long> a(P);
	std::for_each(a.begin(), a.end(), fill);
	long N;
	fin >> N >> X >> A >> B;
	fin >> Ac >> Bc >> Ad >> Bd;
	for (N; N > 0; N--)
	{
		i = find(a, X);
		if (i == -1)
		{
			A = (A + Ac) % 1000;
			B = (B + Bc) % 1000000000000000;
		}
		else
		{
			if (a[i] != -1) { fout << "error" << '\n';  exit(0); }
			a[i] = X;
			A = (A + Ad) % 1000;
			B = (B + Bd) % 1000000000000000;
		}
		X = (X * A + B) % 1000000000000000;
	}
	fout << X << ' ' << A << ' ' << B;
	return 0;
}
