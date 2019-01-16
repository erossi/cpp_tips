/* Tips in C++.

              DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
                    Version 2, December 2004

 Copyright (C) 2004 Sam Hocevar <sam@hocevar.net>

 Everyone is permitted to copy and distribute verbatim or modified
 copies of this license document, and changing it is allowed as long
 as the name is changed.

            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
   TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION

  0. You just DO WHAT THE FUCK YOU WANT TO.

Compile with:
 g++ -Wall -pedantic -std=c++14 -g <ThisFilename.cpp>

*/

/*
 * Scope: define a normal class and use it as a static
 * member of another class.
 *
 * The first class allocates an array of int used as a buffer.
 * The second class which define the previous class as a static
 * member, allocate it with an out of class definition.
 *
 * Finally instantiate objects of these classes.
 */

#include <iostream>

using namespace std;

// First class
class SimpleBufferManager {
	private:
		int* buffer_; // the buffer
		const size_t size_; // the size of the buffer
	public:
		SimpleBufferManager(size_t buffersize = 5);
		~SimpleBufferManager() { delete[] buffer_; };
		size_t size(void) { return size_; };
		void add(unsigned int, int);
		int get(unsigned int);
};

// The constructor with the default size of the buffer.
SimpleBufferManager::SimpleBufferManager(size_t buffersize) : size_{buffersize}
{
	buffer_ = new int[size_];
}

// add a value to the buffer
void SimpleBufferManager::add(unsigned int position, int value)
{
	if (position < size_)
		buffer_[position] = value;
}

// get a value from the buffer
int SimpleBufferManager::get(unsigned int position)
{
	if (position < size_)
		return buffer_[position];
	else
		return 0;
}

// The second class
class StaticBufferManager {
	private:
		static SimpleBufferManager sbm_;
	public:
		static size_t size(void) { return sbm_.size(); };
		static void add(unsigned int p, int v) { sbm_.add(p, v); };
		static int get(unsigned int p) { return sbm_.get(p); };
};

// out of class allocation of the buffer (static)
SimpleBufferManager StaticBufferManager::sbm_ {5};

int main()
{
	// test the normal object.
	SimpleBufferManager buffer {5};
	size_t s {buffer.size()};

	// test the static object.
	StaticBufferManager Sbuffer1;
	StaticBufferManager Sbuffer2;

	// fill in all the buffers
	for (size_t i=0; i<s; i++) {
		// add a number to the buffer
		buffer.add(i, (int)(i*2));

		// even/odd numbers goes into different
		// objects.
		if (i%2)
			Sbuffer1.add(i, (int)(i*3));
		else
			Sbuffer2.add(i, (int)(i*3));
	}

	// get back
	for (size_t i=0; i<s; i++) {
		cout << "O: " << buffer.get(i);
		cout << " SBM: " << StaticBufferManager::get(i);
		cout << " SB1: " << Sbuffer1.get(i);
		cout << " SB2: " << Sbuffer2.get(i);
		cout << endl;
	}

	/* the output is:

	O: 0 SBM: 0 SB1: 0 SB2: 0
	O: 2 SBM: 3 SB1: 3 SB2: 3
	O: 4 SBM: 6 SB1: 6 SB2: 6
	O: 6 SBM: 9 SB1: 9 SB2: 9
	O: 8 SBM: 12 SB1: 12 SB2: 12

	 */

	return(0);
}
