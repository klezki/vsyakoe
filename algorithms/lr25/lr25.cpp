#include "edx-io.hpp"  
#include <vector>
#include <string>


const long x = 127;

unsigned long long hash(const std::string& s, long n)
{
	unsigned long long hash = 0;
	for (long i = 0; i < n; i++)
	{
		hash = hash * x + s[i];
	}
	return hash;
}



void buildp(std::vector<long>& P, const std::string& t)
{
	P[0] = 0;
	long j = 0;
	long i = 1;
	while (i < t.size())
	{
		if (t[j] == t[i]) P[i++] = ++j;
		else
		{
			if (j == 0) P[i++] = 0;
			else j = P[j - 1];
		}
	}
}




int main()
{
	std::string t;
	std::string p;
	io >> p;
	io >> t;
	if (p.size() > t.size())
	{
		io << 0;
		return 0;
	}

	std::vector<long> index;
	std::vector<long> P(p.size());
	buildp(P, p);


	long i, j;
	i = 0;
	j = 0;
	while (i < t.size())
	{ 
		if (j == p.size())
		{
			index.push_back(i - p.size());
			j = P[j - 1];
		}
		if (p[j] == t[i])
		{
			i++;
			j++;
		}
		else
		{
			if (j == 0) i++;
			else j = P[j - 1];
		}
	}
	if (j == p.size())
	{
		index.push_back(i - p.size());
		j = P[j - 1];
	}

	io << index.size() << '\n';
	for (i = 0; i < index.size(); i++)
	{
		io << index[i] + 1 << ' ';
	}
	return 0;
}
