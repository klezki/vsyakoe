#include <fstream>    
#include <utility> 
#include <list>  
#include <vector>
#include <string>
#include <queue>
#include "edx-io.hpp"
#include <unordered_map>

std::ifstream fin("input.txt");
std::ofstream fout("output.txt");

std::vector<std::string> ss;

using map = std::unordered_map<std::string, unsigned long>;

class quack
{

	std::queue<unsigned short> q;
	
	std::vector<unsigned short> reg;
	
	map labels;

public:
	quack() : reg(26) {}
	

	void add()
	{
		int a, b;
		a = q.front();
		q.pop();
		b = q.front();
		q.pop();
		q.push(a + b);
	}
	
	void subst()
	{
		int a, b;
		a = q.front();
		q.pop();
		b = q.front();
		q.pop();
		q.push(a - b);
	}

	void mult()
	{
		int a, b;
		a = q.front();
		q.pop();
		b = q.front();
		q.pop();
		q.push(a * b);
	}

	void div()
	{
		int a, b;
		a = q.front();
		q.pop();
		b = q.front();
		q.pop();
		if (b) q.push(a / b);
		else q.push(0);
	}

	void mod()
	{
		int a, b;
		a = q.front();
		q.pop();
		b = q.front();
		q.pop();
		if (b) q.push(a % b);
		else q.push(0);
	}
	void getreg(char c)
	{
		reg[c - 97] = q.front();
		q.pop();
	}
	void putreg(char c)
	{
		q.push(reg[c - 97]);
	}
	void printq(void)
	{
		fout << q.front() << '\n';
		q.pop();
	}
	void printc(void)
	{
		fout << char(q.front() % 256);
		q.pop();
	}
	void printreg(char c)
	{
		fout << reg[c - 97] << '\n';
	}
	void printregc(char c)
	{
		fout << char(reg[c - 97] % 256);
	}
	
	unsigned long seeklabel(const std::string& str)
	{
		return labels.find(str)->second;
	}

	unsigned long seeklabelz(unsigned long i)
	{
		if (!reg[ss[i][1] - 97])
		{
			i = seeklabel(ss[i].substr(2, ss[i].size() - 2));
		}
		return i;
	}
	unsigned long seeklabele(unsigned long i)
	{
		if (reg[ss[i][1] - 97] == reg[ss[i][2] - 97])
		{
			i = seeklabel(ss[i].substr(3, ss[i].size() - 3));
		}
		return i;
	}
	unsigned long seeklabelg(unsigned long i)
	{
		if (reg[ss[i][1] - 97] > reg[ss[i][2] - 97])
		{
			i = seeklabel(ss[i].substr(3, ss[i].size() - 3));
		}
		return i;
	}
	void addnum(const std::string& str)
	{
		int temp = std::stoul(str);;
		q.push(temp);
	}
	void addlabel(const std::string& str)
	{
		labels.insert(std::make_pair(str, ss.size() - 1));
	}

};


int main()
{
	char c;
	quack a;
	std::string str;
	while (fin >> str)
	{
		if (str[0] == ':') a.addlabel(str.substr(1, str.size() - 1));
		else ss.push_back(str);
	} 
	for (unsigned long i = 0; i < ss.size(); i++)
	{
		switch (ss[i][0])
		{
		case '+':
			a.add();
			break;
		case '-':
			a.subst();
			break;
		case '*':
			a.mult();
			break;
		case '/':
			a.div();
			break;
		case '%':
			a.mod();
			break;
		case '>':
			a.getreg(ss[i][1]);
			break;
		case '<':
			a.putreg(ss[i][1]);
			break;
		case 'P':
			if (ss[i].size() == 1) a.printq();
			else
			{
				a.printreg(ss[i][1]);
			}
			break;
		case 'C':
			if (ss[i].size() == 1) a.printc();
			else
			{
				a.printregc(ss[i][1]);
			}
			break;
		case 'J':
			i = a.seeklabel(ss[i].substr(1, ss[i].size() - 1));
			break;
		case 'Z':
			i = a.seeklabelz(i);
			break;
		case 'E':
			i = a.seeklabele(i);
			break;
		case 'G':
			i = a.seeklabelg(i);
			break;
		case 'Q':
			i = ss.size();
			break;
		default:
			a.addnum(ss[i]);
		}
	}
	return 0;
}

