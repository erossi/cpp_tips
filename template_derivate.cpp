/* Derivate Templates in C++, a working example.

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
 g++ -Wall -pedantic -std=c++14 -g template_derivate.cpp
*/

#include <iostream>
using namespace std;
 
// Template Base Class
template <typename T>
class Base {
	private:
		T pbt_; // Private Base t
	public:
		T bt; // Base t

		Base(T); // Constructor
		void set(T i) { pbt_ = i; }; // set Private Base t
		T get() { return(pbt_); }; // get Private Base t
		void print(); // print() declaration.
};

// Base Constructor, initialize Private Base t and Base t.
template <typename T>
Base<T>::Base(T i) : pbt_{i}
{
	bt = i; // Set Base t.
	cout << "Base Constructor called." << endl;
	print();
}

// Base print variables.
template <typename T>
void Base<T>::print()
{
	cout << " pbt.....: " << pbt_ << endl;
	cout << " bt......: " << bt << endl;
}

// Template Derivate Class
// public level derivate
template <typename T>
class Derivate : public Base<T> {
	private:
		T pdt_; // Private Derivate t
	public:
		T dt; // Derivate t

		Derivate(T); // Constructor

		/* Overloading Base::set(T)
		 * 
		 * having a default (what = true) means
		 * we are declaring both:
		 * set(T); -> Overloading Base::set(T)
		 * and
		 * set(T, bool); -> new function member.
		 */
		void set(T i, bool what = true);

		// Overloading Base::get()
		T get(bool what = true);

		// Overloading Base::print()
		void print();
};

// Derivate Constructor
// call to the Base constructor passing i,
// then initialize Private Derivate t and Derivate t.
template <typename T>
Derivate<T>::Derivate(T i) : Base<T>{i}
{
	/* Private derivate t = Private base t
	 * Call the get() from Base
	 */
	pdt_ = Base<T>::get();

	/* We did not declare any bt derivate, therefore
	 * once this template will be instantiated, the bt data
	 * member will exist inherited from Base.
	 */
	dt = this->bt; // bt will exist once "this->" object will.

	cout << "Derivate constructor called:" << endl;

	// Print do exist in Derivate, we can call it.
	print();
}

// Derivate overloaded set(T) + define set(T, bool)
// what = true -> call the Base::set(T)
template <typename T>
void Derivate<T>::set(T i, bool what)
{
	if (what)
		Base<T>::set(i); // set pbt_
	else
		pdt_ = i; // set pdt_
}

// Derivate overloaded get(T) + define get(T, bool)
// what = true -> call the Base::get(T)
template <typename T>
T Derivate<T>::get(bool what)
{
	if (what)
		return(Base<T>::get()); // pbt_
	else
		return(pdt_); // pdt_
}

// Derivate overloaded print()
template <typename T>
void Derivate<T>::print()
{
	// this->print(); segfault
	Base<T>::print();
	cout << " pdt.....: " << pdt_ << endl;
	cout << " dt......: " << dt << endl;
}

int main() {
	Base<int> i {1};
	Base<double> f {5.5};
	Derivate<int> di {10};
	Derivate<double> df {15.5};

	cout << "Base<int>: set pbt=2" << endl;
	i.set(2);
	i.print();

	cout << "Base<double>: set pbt=6.5" << endl;
	f.set(6.5);
	f.print();

	cout << "Derivate<int>: set pdt=12, pbt=13" << endl;
	di.set(12); // di.set(12, true);
	di.set(13, false);
	di.print();

	cout << "Derivate<double>: set pdt=16.5, pbt=17.5" << endl;
	df.set(16.5, true);
	df.set(17.5, false);
	df.print();

	return 0;
}
