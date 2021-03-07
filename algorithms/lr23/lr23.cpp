#include "edx-io.hpp"  
#include <vector>
#include <string>


std::string pripiska(65, 'a');
long N = 0;

long hash(const std::string& s, short t)
{
	long hash = 0;
	for (short i = 0; i < s.size(); i++)
	{
		hash = hash * t + s[i];
	}
	return hash;
}


void inverse_add(std::string& str)
{
	std::string newstr(str.size(), 'a');
	for (short i = 0; i < str.size(); i++)
	{
		if (str[i] == 'a') newstr[i] = 'b';
	}
	str += newstr;
}

void inverse(std::string& str, short pos, short count)
{
	for (short i = pos; i < pos + count; i++)
	{ 
		if (str[i] == 'a') str[i] = 'b';
		else str[i] = 'a';
	}
}



void inverse_print(std::string& str, short pos, short count)
{
	N--;
	inverse(str, pos, count);
	io << str << pripiska << '\n';
	inverse(str, pos, count);
	if (N == 0) exit(0);
}

void normal_print(std::string& str)
{
	N--;
	io << str << pripiska << '\n';
	if (N == 0) exit(0);
}




void printr(std::string& str)
{
	short l = str.size();
	short pos;
	short count = str.size();
	io << str << pripiska << '\n';
	//io << str << '\n';
	N++;
	while (count > 32)
	{
		pos = 0;
		while (pos + count <= l)
		{
			inverse(str, pos, count);
			io << str << pripiska << '\n';
			//io << str << '\n';
			N++;
			inverse(str, pos, count);
			pos += count;
		}
		count = count / 2;
	}

}




void printl(std::string& str)
{
	std::string s1(str.substr(0, str.size() / 2));
	std::string s2(str.substr(str.size() / 2, str.size() / 2));
	short l = s1.size();
	short pos;
	short count = s1.size();
	//io << pripiska << s1;
	io << s1;
	printr(s2);
	while (count > 32)
	{
		pos = 0;
		while (pos + count <= l)
		{
			inverse(s1, pos, count);
			//io << pripiska << s1;
			io << s1;
			printr(s2);
			inverse(s1, pos, count);
			pos += count;
		}
		count = count / 2;
	}

}


const short chunk = 128;

void printpr(std::string& str, short count)
{
	if (count == chunk)
	{
		normal_print(str);
		inverse_print(str, 0, chunk);
		return;
	}
	count -= chunk;
	printpr(str, count);
	inverse(str, count, chunk);
	printpr(str, count);
	inverse(str, count, chunk);
}



void print(std::string& str)
{
	long i = chunk;
	normal_print(str);
	inverse_print(str, 0, chunk);
	while (1)
	{
		inverse(str, i, chunk);
		printpr(str, i);
		inverse(str, i, chunk);
		i += chunk;
	}
}




int main()
{
	std::string s("a");
	while (s.size() < 2048)
	{
		inverse_add(s);
	}
	/*long a = hash(s, 3);
	inverse(s, 0, chunk);
	long b = hash(s, 3);*/
	io >> N;
	print(s);
	return 0;
}

