#include <fstream>     
#include <vector>
#include "edx-io.hpp"
#include <string>


//std::ifstream fin("input.txt");
//std::ofstream fout("output.txt");

const long P = 2048581;
const short t = 31;

long hash(const std::string& s)
{
	unsigned long long hash = 0;
	for (short i = 0; i < s.size(); i++)
	{
		hash = hash * t + (s[i] - 'a');
	}
	return hash % P;
}

struct list
{
	std::string key;
	std::string value;
	list* before;
	list* after;
	list* next;
	list(const std::string& _key, const std::string& _value) : key(_key), value(_value), after(NULL)
	{
	
	}
};



list* find(const std::vector<list*>& a, const std::string& key)
{
	list* p = a[hash(key)];
	while (p)
	{
		if (p->key == key) break;
		p = p->next;
	}
	return p;
}



void erase(std::vector<list*>& a, const std::string& key , list*& last)
{
	long _hash = hash(key);
	list* p =  a[_hash];
	list* temp = NULL;
	if (p == NULL) return;
	if (p->key == key) 
	{
		if (p == last) last = p->before;
		a[_hash] = p->next;
		if (p->before) p->before->after = p->after;
		if (p->after) p->after->before = p->before;
		delete p;
		return;
	}
	while (p->next)
	{
		if (p->next->key == key)
		{
			temp = p->next;
			if (temp == last) last = temp->before;
			p->next = temp->next;
			if (temp->before) temp->before->after = temp->after;
			if (temp->after) temp->after->before = temp->before;
			delete temp;
			return;
		}
		p = p->next;
	}
}


void freemem(std::vector<list*>& a)
{
	for (size_t i = 0; i < a.size(); i++)
	{
		if (a[i]) delete a[i];
	}
}


list* add(std::vector<list*>& a, list* last, const std::string& key, const std::string& value)
{
	long _hash = hash(key);
	list* p = find(a, key);
	if (p)
	{
		p->value = value;
		return last;
	}
	else
	{
		p = new list(key, value);
		p->next = a[_hash];
		a[_hash] = p;
		p->before = last;
		if (last) last->after = p;
		return p;
	}
}



int main()
{
	std::string key;
	std::string value;
	std::string str;
	std::vector<list*> a(P);
	list* last = NULL;
	list* ptemp;
	long N;
	io >> N;
	for (long i = 0; i < N; i++)
	{
		io >> str;
		switch (str[0])
		{
		case 'p':
			switch (str[1])
			{
			case 'u':
				io >> key >> value;
				last = add(a, last, key, value);
				break;
			case 'r':
				io >> key;
				ptemp = find(a, key);
				if (ptemp) if (ptemp->before) { io << ptemp->before->value << '\n'; break; }
				io << "<none>" << '\n';
				break;
			}
			break;
		case 'd':
			io >> key;
			erase(a, key, last);
			break;
		case 'g':
			io >> key;
			ptemp = find(a, key);
			io << (ptemp ? ptemp->value : "<none>") << '\n';
			break;
		case 'n':
			io >> key;
			ptemp = find(a, key);
			if (ptemp) if (ptemp->after) { io << ptemp->after->value << '\n'; break; }
			io << "<none>" << '\n';
			break;
		}
	}
	freemem(a);
	return 0;
}
