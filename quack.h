#ifndef _QUACK_H_
#define _QUACK_H_
#include <ostream>
#include <iomanip>

class Quack
{
public:
	static const char	YOUR_NAME[];		// used for printing out my name
	static const bool	PREMIUM_VERSION;	

	Quack(int capacity, int growBy = 0);
		// capacity: # of slots in array
		// growBy:   # of slots to add to array when it grows, 0 means "don't grow"
	~Quack(void);
	bool pushFront(const char ch);		// push an item onto the front
	bool pushBack(const char ch);		// push an item onto the back
	bool popFront(char& ch);			// pop an item off the front
	bool popBack(char& ch);				// pop an item off the back
	void rotate(int r);					// "rotate" the stored items (see note below)
	void reverse(void);					// reverse the order of the stored items
	int	itemCount(void);				// return the current number of stored items

	void initArray(void)								// initialize contents of array
	{
		for (int i = 0; i < capacity; i++)
			items[i] = '\0';
	}

	void printArray(std::ostream& out)					// print contents of array
	{
		unsigned char	ch;

		out << "[ ";
		for (int i = 0; i < capacity; i++) {
			ch = items[i];
			if (ch == '-')								// print in hex, because using '-' for '\0'
				goto printHex;
			else if (ch >= '!' && ch <= '}')			// ASCII text character
				out << ch << ' ';
			else if (ch == '\0')						// print '\0' as '-'
				out << "- ";
			else										// print everything else as hex
				goto printHex;
			continue;

		printHex:	
			out << std::setw(2) << std::setfill('0') << std::hex << ch << ' ';
			}
		out << ']' << std::endl;
	}

private:
	char	*items;						// pointer to storage for circular array,
										// each item in the array is a char

	int		capacity;					// # of slots in array
	char	*frontPtr;					// front of quack
	char	*midPtr;					// the middle	
	char	*backPtr;					// back of quack
	char	*current;
	int		count;						// # of items currently in the array
	int		top;
	int		back;
	int		growth;						//how much to grow by

	void grow(void)
	{

	//to grow array

	char * temp = new char[capacity + growth];

	for (int idx = 0; idx < count; idx++)
	{
		temp[idx] = items[idx];
	}

	// delete old array
	delete[] items;

	//point to new array
	items = temp;

	*backPtr = items[count]; 
	*frontPtr = items[top + 1];

	capacity = capacity + growth - 1; 

	back = capacity - 1; 
 	}

public:
	friend std::ostream& operator<<(std::ostream& out, Quack *q);
};

#endif
