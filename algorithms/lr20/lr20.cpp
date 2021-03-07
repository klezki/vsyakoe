#include <fstream>     
#include <vector>
#include <list>


std::ifstream fin("input.txt");
std::ofstream fout("output.txt");

const long P = 2048581;



struct list
{
	const unsigned long long key;
	list* next;
	list(const unsigned long long& ey) : key(ey)
	{

	}
};



bool find(const std::vector<list*>& a, const unsigned long long& key)
{
	list* p = a[key % P];
	while (p)
	{
		if (p->key == key) return true;
		p = p->next;
	}
	return false;
}



void erase(std::vector<list*>& a, const unsigned long long& key)
{
	list* p =  a[key % P];
	list* temp = NULL;
	if (p == NULL) return;
	if (p->key == key) 
	{
		a[key % P] = p->next;
		delete p; 
		return;
	}
	while (p->next)
	{
		if (p->next->key == key)
		{
			temp = p->next;
			p->next = temp->next;
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

int main()
{
	char c;
	std::vector<list*> a(P);
	list* ptemp;
	unsigned long long temp;
	long N;
	fin >> N;
	for (long i = 0; i < N; i++)
	{
		fin >> c;
		switch (c)
		{
		case 'A':
			fin >> temp;
			if (!find(a, temp))
			{
				ptemp = new list(temp);
				ptemp->next = a[temp % P];
				a[temp % P] = ptemp;
			}
			break;
		case 'D':
			fin >> temp;
			erase(a, temp);
			break;
		case '?':
			fin >> temp;
			fout << (find(a, temp) ? 'Y' : 'N') << '\n';
			break;
		}
	}
	freemem(a);
	return 0;
}
