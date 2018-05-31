/* Vector handling test.

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

#include <vector>
#include <iostream>

using namespace std;

int main() {
	vector<int> v; // the vector

	v.assign( 8, 99 ); // replace v with 8 copies of 99
	v[2] = 2; // replace at specific index
	v[3] = 3;
	v.push_back(4); // append to the vector
	v.push_back(5);

	cout << "Vector: ";

	for( unsigned int i = 0; i < v.size(); i++ )
		cout << v[i] << " ";

	cout << endl;


	cout << "The first, v.at(2) and the last: ";
	cout << v.front() << " " << v.at(2) << " " << v.back() << endl;

	cout << "Usign iterators: ";
	vector<int>::iterator iter;

	for( iter = v.begin(); iter != v.end(); iter++ )
		cout << *iter << " ";

	cout << endl;
}

/* output:

Vector: 99 99 2 3 99 99 99 99 4 5 
The first, v.at(2) and the last: 99 2 5
Usign iterators: 99 99 2 3 99 99 99 99 4 5 

*/
