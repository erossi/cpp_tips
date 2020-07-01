#include <iostream>
#include <stdint.h>

using namespace std;

class Buffer {
	public:
		static uint8_t *buffer;
};

class Test1 {
	public:
		Buffer b;
		Test1();
};

class Test2 {
	public:
		Buffer b;
		Test2();
};

uint8_t* Buffer::buffer = (uint8_t*) malloc(5);

Test1::Test1 () {
	b.buffer[0] = 't';
	b.buffer[1] = '1';
	b.buffer[2] = 0;

	cout << "Build: ";

	for (uint8_t i = 0; i < 2; i++)
		printf("%c", *(b.buffer + i));

	cout << endl;
}

Test2::Test2 () {
	b.buffer[0] = 't';
	b.buffer[1] = '2';
	b.buffer[2] = 0;

	cout << "Build: ";

	for (uint8_t i = 0; i < 2; i++)
		printf("%c", *(b.buffer + i));

	cout << endl;
}

int main()
{
	Test1 t1;
	Test2 t2;

	cout << "Buffer: ";

	for (uint8_t i = 0; i < 2; i++)
		printf("%c", *(Buffer::buffer + i));

	cout << endl;
	return(0);
}
