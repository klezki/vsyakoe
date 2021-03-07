#include "edx-io.hpp"  
#include <vector>
#include <string>
#include <fstream>  

std::ifstream fin("input.txt");
std::ofstream fout("output.txt");
std::vector<unsigned long long> ind(26, -1);
std::vector<unsigned long long> num(26);
unsigned long long N = 0;


int main()
{
	std::string s;
	std::getline(fin, s, '\n');
	unsigned long long i = 0;
	unsigned long long reali = 0;
	char ch;
	for (; i < s.size(); i++, reali++)
	{
		while (s[i] == ' ') i++;
		//if (s[i] == ' ') { fout << "error"; exit(0); }
		ch = s[i] - 97;
		if (ind[ch] == -1)
		{
			ind[ch] = reali;
			num[ch]++;
		}
		else
		{
			N += (reali - ind[ch] / num[ch] - 1) * (num[ch] - 1) + reali - ind[ch] / num[ch] - ind[ch] % num[ch] - 1;
			ind[ch] += reali;
			num[ch]++;
		}
	}
	fout << N;
	return 0;
}
