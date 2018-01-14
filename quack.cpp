#include "quack.h"

using namespace std;

const char	Quack::YOUR_NAME[]{"Bowen Johnson"};

const bool	Quack::PREMIUM_VERSION{true};

Quack::Quack(int capacity, int growBy) :
	items{new char[capacity]},
	capacity{capacity},
	frontPtr{new char}, 
	midPtr{new char},
	backPtr{new char},
	current{new char},
	count{0},
	top{-1},
	back{capacity - 1},
	growth{growBy}

{
	initArray();	// you are required to call this function here, and
					// it must be the first thing in the constructor body
}

Quack::~Quack(void)
{
	delete[] items;
	delete frontPtr;
	delete midPtr;
	delete backPtr;
	delete current;
}

// items are pushed to successively LOWER slots in the circular array
// (except for when the beginning of the array "wraps around" to the end)
bool Quack::pushFront(const char ch)
{
	int idx = 0;
	
	if ( count == capacity )
	{
		grow();
	}
	
	*backPtr = items[count]; //changed from back - 1
	while ( idx < count )
	{
		if ( idx == top + 1 )
		{
			*current = items[top+1];
			items[top + 1] = *backPtr;
		}

		*midPtr = items[++idx];
		items[idx] = *current;

		if (idx != back  ) 
		{
			*current = items[++idx];
			items[idx] = *midPtr;
		}
	}
	
	++count;
	items[top + 1] = ch;
	return true;
}

// items are pushed to successively HIGHER slots in the circular array
// (except for when the end of the array "wraps around" to the beginning)
bool Quack::pushBack(const char ch)
{
    if ( count == capacity )
	{
		grow();
	}


	items[count] = ch;
	count++;
	return true;
}

bool Quack::popFront(char& ch)
{
	ch = items[top + 1];

	for ( int idx = 0; idx < count; idx++ )
	{
		items[idx] = items[idx + 1];
	}
	count--;

	return true;
}

bool Quack::popBack(char& ch)
{

	ch = items[--count];
	return true;
}

void Quack::rotate(int r)
{
	int idx = 0;

	while (r > 0) 
	{
		*frontPtr = items[top + 1];

		for ( int idx = 0; idx < count ; idx++ ) 
		{
			items[idx] = items[idx + 1];
		}
		items[count - 1] = *frontPtr; 
		r--;
	}

	while (r < 0 )
	{
		if (idx == top + 1)
		{
			*backPtr = items[count - 1]; 
			*current = items[top + 1];
			items[top + 1] = *backPtr;
		}
		
		*midPtr = items[++idx];
		items[idx] = *current;

		if (idx == count - 1) 
		{
			items[count - 1] = *current; 
			idx = 0;
			r++; 
			continue;
		}
		else
		{
			*current = items[++idx];
			items[idx] = *midPtr;
			
			if (idx == count - 1) 
			{
				idx = 0;
				r++;
				continue;
			}
		}
	}
}

void Quack::reverse(void)
{
	int x = 0;
	*frontPtr = items[top + 1];
	*backPtr = items[ back - 1];

	for ( int idx = 0; idx < count / 2; idx++)
	{
		items[x] = items[idx];
		items[idx] = items[count - idx - 1];
		items[count - idx - 1] = *items;
	}

	items[top + 1] = *backPtr;
	items[back - 1] = *frontPtr;

	*backPtr = items[back - 1];
	*frontPtr = items[ top + 1];
}

int	Quack::itemCount(void)
{
	return count;		
}

ostream& operator<<(ostream& out, Quack *q)
{
	if (q->count == 0 )
	{
		out << "quack: empty" << endl << endl;
}
	else
	{
		out << endl << "quack: ";
		for (int idx = 0; idx < q->count; idx++ )
		{
			if ( idx < q->count - 1 )
			{
				out << q->items[idx] << ", ";
			}
			else
			{
				out << q->items[idx];
			}
		}
		out << endl << endl; 
	}

	return out;
}
