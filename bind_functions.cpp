/* Bind functions in C++, a working example.

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

/* The scope is to create two classed with pre-defined
 * static functions, add these functions to a catalog and then
 * use the catalog to trigger all these functions.
 *
 * output:
 
1st: 0
2nd: 0
After the set_Map_all()
1st: 1
2nd: 1
After the clear_Map_all()
1st: 0
2nd: 0
After the set_Vector_all()
1st: 1
2nd: 1
After the clear_Vector_all()
1st: 0
2nd: 0
After the set_Map_all() with 1st removed
1st: 0
2nd: 1
 */

#include <vector>
#include <map>
#include <iostream>
#include <functional>

using namespace std;

class FirstClass {
	public:
		static bool sstatus;
		static void set() { sstatus = true; };
		static void clear() { sstatus = false; };
		static bool check() { return(sstatus); };
};

// A copy of the FirstClass

class SecondClass {
	public:
		static bool sstatus;
		static void set() { sstatus = true; };
		static void clear() { sstatus = false; };
		static bool check() { return(sstatus); };
};

class Manager {
	private:
		// The struct we use to store in the catalog.
		struct record_t {
			string name; // a name, useless with maps.
			function<void()> set;
			function<void()> clear;
		};

		vector<struct record_t> vcatalog; // The catalog as a vector.
		map<string, struct record_t> mcatalog; // The catalog as an associative array.
	public:
		// Add the two set() and clear() functions to both catalogs.
		void add(string s, function<void()> f1, function<void()> f2)
		{
			struct record_t r {s, f1, f2};
			vcatalog.push_back(r); // add it as a vector element.
			mcatalog.insert( pair<string, struct record_t>(s, r)); // a map element.
		};

		/* To remove an element from the vector, first we have to scan it,
		 * find what we need to remove, then erase() it.
		 */
		void remove(string s) { mcatalog.erase(s); }; // remove only from the map.

		// Call All the set() registered in the Map catalog.
		// Using the constant begin/end, no modification allowed.
		void set_mall(void)
		{
			for (auto i = mcatalog.cbegin(); i != mcatalog.cend(); i++) {
				i->second.set();
			}
		};

		// Call all the clear() registered in the Map catalog, in reverse order.
		void clear_mall(void)
		{
			for (auto i = mcatalog.rbegin(); i != mcatalog.rend(); i++) {
				i->second.clear();
			}
		};

		// Call all the set() registered in the Vector catalog.
		void set_vall(void)
		{
			for (auto i = vcatalog.begin(); i != vcatalog.end(); i++) {
				i->set();
			}
		};

		// Call all the clear() registered in the Vector catalog.
		void clear_vall(void)
		{
			for (auto i = vcatalog.begin(); i != vcatalog.end(); i++) {
				i->clear();
			}
		};
};

// allocate the two variables
bool FirstClass::sstatus {false};
bool SecondClass::sstatus {false};

int main () {
	Manager manager; // Instantiate the object

	// add the FirstClass
	manager.add("1st_elem", FirstClass::set, FirstClass::clear);
	// add the SecondClass
	manager.add("2nd_elem", SecondClass::set, SecondClass::clear);

	// Print both statuses
	cout << "1st: " << FirstClass::sstatus << endl;
	cout << "2nd: " << SecondClass::sstatus << endl;

	// Set all using the Map catalog
	manager.set_mall();

	// Print both statuses
	cout << "After the set_Map_all()" << endl;
	cout << "1st: " << FirstClass::sstatus << endl;
	cout << "2nd: " << SecondClass::sstatus << endl;

	// Clear all using the Map catalog
	manager.clear_mall();

	cout << "After the clear_Map_all()" << endl;
	cout << "1st: " << FirstClass::sstatus << endl;
	cout << "2nd: " << SecondClass::sstatus << endl;

	// Set all using the Vector catalog
	manager.set_vall();

	cout << "After the set_Vector_all()" << endl;
	cout << "1st: " << FirstClass::sstatus << endl;
	cout << "2nd: " << SecondClass::sstatus << endl;

	// Clear all using the Vector catalog
	manager.clear_vall();

	cout << "After the clear_Vector_all()" << endl;
	cout << "1st: " << FirstClass::sstatus << endl;
	cout << "2nd: " << SecondClass::sstatus << endl;

	// Remove the FirstClass from the Map catalog
	manager.remove("1st_elem");

	// Set all using the Map catalog
	manager.set_mall();

	// and print it
	cout << "After the set_Map_all() with 1st removed" << endl;
	cout << "1st: " << FirstClass::sstatus << endl;
	cout << "2nd: " << SecondClass::sstatus << endl;

	return 0;
}
