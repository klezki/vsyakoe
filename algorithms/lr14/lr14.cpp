#include <fstream>     
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
#include "edx-io.hpp"




struct priority_queue
{

	inline long parent(long i) { return (i - 2) / 2 + (i - 2) % 2; }
	inline long left(long i) { return 2 * i + 1; }
	inline long right(long i) { return 2 * i + 2; }

	std::vector<long> heap;

	std::vector<long> indexes;                                            //index[i] - индекс в строке i
	                                                                      //

	std::vector<long> strings;                                            //string[i] - строка по индексу i
	                                                                      //
	
	priority_queue() {};

	priority_queue(long n) : indexes(n + 1), strings(n + 1) {};
	
	void decr(long val, long index)
	{
		long i = index, p;
		heap[i] = val;
		while (i > 1 && heap[i] < heap[p = parent(i)])
		{
			std::swap(heap[i], heap[p]);
			std::swap(indexes[strings[i]], indexes[strings[p]]);
			std::swap(strings[i], strings[p]);
			i = p;
		}
		if (i == 1)
		{
			if (heap[1] < heap[0])
			{
				std::swap(heap[0], heap[1]);
				std::swap(indexes[strings[0]], indexes[strings[1]]);
				std::swap(strings[0], strings[1]);
			}
		}
	}
	
	
	void push(long val)
	{
		heap.push_back(LONG_MAX);
		decr(val, heap.size() - 1);
	}
	
	
	void pop(void)
	{
		std::swap(heap[0], heap[heap.size() - 1]);
		std::swap(indexes[strings[0]], indexes[strings[heap.size() - 1]]);
		std::swap(strings[0], strings[heap.size() - 1]);

		heap.pop_back();
		heapify();
	}
	


	void heapify(void)
	{
		long i = 0, min, l , r;
		while (1)
		{
			l = left(i);
			r = right(i);
			if (l < heap.size() && heap[l] < heap[i])
			{
				min = l;
			}
			else min = i;
			if (r < heap.size() && heap[r] < heap[min])
			{
				min = r;
			}
			if (min == i) return;
			std::swap(heap[i], heap[min]);
			std::swap(indexes[strings[i]], indexes[strings[min]]);
			std::swap(strings[i], strings[min]);
			i = min;
		}

	}



};


int main()
{
	long n, temp, ind;
	char c;
	io >> n;
	priority_queue a(n);
	for (long i = 1; i <= n; i++)
	{
		io >> c;
		switch (c)
		{
		case 'A':
			a.indexes[i] = a.heap.size();
			a.strings[a.heap.size()] = i;
			io >> temp;
			a.push(temp);
			break;
		case 'X':
			if (a.heap.empty()) io << '*' << '\n';
			else 
			{
				io << a.heap.front() << '\n';
				a.pop();
			}
			break;
		case 'D':
			io >> ind >> temp;
			a.decr(temp, a.indexes[ind]);
			break;
		}

	}
	return 0;
}
