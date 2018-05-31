/* Operator overloading

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

#include <iostream>

using namespace std;

class Base {
	public:
		static bool CS; // class bool
		bool s; // obj bool

		// Constuctor, set obj s.
		Base(bool i = false) : s{i} {};

		// set CS
		static void set(bool i) { CS = i; };

		void operator=(bool i) { s = i; CS = i; }
};

bool Base::CS = true; // allocate the class CS

int main() {
	Base a {true};
	Base b; // do not overwrite CS

	cout << "a.s : " << a.s << endl;
	cout << "b.s : " << b.s << endl;
	cout << "a.CS: " << a.CS << endl;
	cout << "b.CS: " << b.CS << endl;

	/* output:
	 a.s : 1
	 b.s : 0
	 a.CS: 1
	 b.CS: 1
	 */

	Base::CS = false; // CS is the same for a and b
	a = false; // using the overloaded '=' sets both s and CS.
	b = true;

	cout << "a.s : " << a.s << endl;
	cout << "b.s : " << b.s << endl;
	cout << "a.CS: " << a.CS << endl;
	cout << "b.CS: " << b.CS << endl;

	/* output:
	 a.s : 0
	 b.s : 1
	 a.CS: 1
	 b.CS: 1
	 */

	return 0;
}
