#include <fstream>    
#include <utility> 
#include <list>  
#include <vector>
#include <string>
#include <queue>
//#include "edx-io.hpp"
#include <sstream>

std::vector<std::string>::iterator it;
std::ifstream fin("input.txt");
std::ofstream fout("output.txt");

long calc(void)
{
	long opl, opr;
	if (it->size() > 1) return std::stol(*it);
	switch (it->front()) 
	{
	case '+':
		it++;
		opr = calc();
		it++;
		opl = calc();
		return opl + opr;
	case '-':
		it++;
		opr = calc();
		it++;
		opl = calc();
		return opl - opr;
	case '*':
		it++;
		opr = calc();
		it++;
		opl = calc();
		return opl * opr;
	default:
		return it->front() - '0';
	}
}


int main()
{
	long opl, opr, N;
	fin >> N;
	std::vector<std::string> a(N);
	for (long i = N - 1; i >= 0; i--)
	{
		fin >> a[i];
	}
	it = a.begin();
	fout << calc();

	return 0;
}

