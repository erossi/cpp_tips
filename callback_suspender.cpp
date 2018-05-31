/* Callback object functions in C++.

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
#include <set>

/* The Class1 will have only the static function suspend().
 * No instantiation is foreseen for this class.
 */
class Class1 {
	public:
		static void suspend(void) {
			std::cout << "C1 suspend" << std::endl;
		}
};

/* The Class2 have the static function suspend() which in turn is going to
 * call all the my_suspend() of each object of the class.
 */
class Class2 {
	private:
		const char* name; // The name of the object.
		void my_suspend(void); // The local suspend() of the object.
	public:
		/* The list of all the object created. */
		static std::set< Class2* > instances;
		Class2(const char*); // Constructor with the name.
		static void suspend(void); // The static suspend().
};

// Simple implementation of the object's suspend.
void Class2::my_suspend(void)
{
	// Print the name of the object.
	std::cout << name << " suspend" << std::endl;
}

// Constructor with the object name as parameter.
Class2::Class2 (const char* s): name{s}
{
	// Add this object to the static list of all the
	// objects of this Class.
	Class2::instances.insert(this);
}

// Static Class2 suspend()
void Class2::suspend(void)
{
	// for each element of the list.
	for (auto& i : Class2::instances)
		i->my_suspend(); // call the object's suspend
}

// Setup the class2 object's list.
std::set< Class2* > Class2::instances;

int main()
{
	Class2 c2a {"C2 obj a"}; // Create the 1st object with the name.
	Class2 c2b {"C2 obj b"};

	Class1::suspend(); // the 1st suspend.
	Class2::suspend(); // the 2nd suspend, which in turn call all the my_suspend().

	/* Run output is:

	   C1 suspend
	   C2 obj b suspend
	   C2 obj a suspend

	   */

	return(0);
}
