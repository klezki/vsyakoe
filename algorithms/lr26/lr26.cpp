#include <vector>
#include <list>
#include <string>
#include "edx-io.hpp"  


short digits(short n)
{
	short p = 10;
	for (short i = 1; i < 5; i++)
	{
		if (p > n) return i;
		p *= 10;
	}
}



std::string s;
std::vector<short> P;
std::vector<short> len;
std::vector<short> num;
std::vector<short> count;

void buildp(const std::string& t)
{
	P[0] = 0;
	short minlen = 2 + len[t.size() - 1];
	short minnum = 1;
	short mincount = 1;
	short curnum = 0;
	short curcount = 0;
	short curlen = 0;
	short j = 0;
	short i = 1;
	short k = 1;
	while (i < t.size())
	{
		if (t[j] == t[i]) P[i++] = ++j;
		else
		{
			if (j == 0) P[i++] = 0;
			else j = P[j - 1];
		}
		if (i > k)
		{
			/*if (P[k] != 0 && P[k] % (i - P[k]) == 0)
			{
				curcount = i - P[k];
				curnum = P[k] / curcount + 1;
				curlen = 1 + curcount + 1 + digits(curnum) + len[t.size() - curcount * curnum];
				if (2 + k + len[t.size() - (k + 1)] < curlen)
				{
					curnum = 1;
					curcount = k + 1;
					curlen = 2 + k + len[t.size() - (k + 1)];
				}
				if (minlen > curlen)
				{
					minnum = curnum;;
					mincount = curcount;
					minlen = curlen;
				}
			}
			else
			{
				if (2 + k + len[t.size() - (k + 1)] < minlen)
				{
					minnum = 1;
					mincount = k + 1;
					minlen = 2 + k + len[t.size() - (k + 1)];
				}
			}*/
			curcount = i - P[k];
			curnum = P[k] / curcount + 1;
			curlen = 1 + curcount + 1 + digits(curnum) + len[t.size() - curcount * curnum];
			if (2 + k + len[t.size() - (k + 1)] < curlen)
			{
				curnum = 1;
				curcount = k + 1;
				curlen = 2 + k + len[t.size() - (k + 1)];
			}
			if (minlen > curlen)
			{
				minnum = curnum;;
				mincount = curcount;
				minlen = curlen;
			}
			k++;
		}
	}
	len[t.size()] = minlen;
	num[t.size()] = minnum;
	count[t.size()] = mincount;
}



int main()
{
	std::string aa;
	io >> s;
	P.resize(s.size());
	len.resize(s.size() + 1);
	num.resize(s.size() + 1);
	count.resize(s.size() + 1);
	len[0] = 1;
	num[0] = 0;
	count[0] = 0;
	short i;
	for (i = 1; i <= s.size(); i++)
	{
		buildp(s.substr(s.size() - i, i));
	}
	i--;
	while (i > 0)
	{
		aa += s.substr(s.size() - i, count[i]);
		if (num[i] > 1)
		{
			aa += '*';
			aa += std::to_string(num[i]);
		}
		aa += '+';
		i -= count[i] * num[i];
	}
	aa.pop_back();
	io << aa;
	return 0;
}
