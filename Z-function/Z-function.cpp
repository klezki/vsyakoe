#include "edx-io.hpp"  
#include <vector>
#include <string>




void buildz(std::vector<long>& z, const std::string& s)
{
	long l = 0, r = 0;
	long i, j = 0;
	z[0] = 0;
	for (i = 1; i < s.size(); i++)
	{
		if (i >= r)
		{
			j = 0;
			while (i + j < s.size() && s[i + j] == s[j]) j++;
			l = i;
			r = i + j;
			z[i] = j;
		}
		else
		{
			if (z[i - l] < r - i) z[i] = z[i - l];
			else 
			{
				j = r - i;
				while (i + j < s.size() && s[i + j] == s[j]) j++;
				l = i;
				r = i + j;
				z[i] = j;
			}
		}
	}
}



int main()
{
	std::string s;
	io >> s;
	std::vector<long> z(s.size());
	buildz(z, s);
	for (long i = 1; i < z.size(); i++)
	{
		io << z[i] << ' ';
	}
	return 0;
}
