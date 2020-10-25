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

/*! Demonstrate a static catalog for client class callbacks.
 *
 * \warning This code does NOT handle the delete of a registered client,
 * doing so will segfault once the dangling pointer in the catalog is called.
 */

#include <iostream>

using namespace std;

class SleepBase {
	protected:
		static const int size_ {5}; //! fixed size of the catalog
		static int top_; //! registered objects.
		static SleepBase *catalog[];
	public:
		virtual void suspend() const {};
		virtual void resume() const {};
};

int SleepBase::top_ {0}; //! registered objects.
SleepBase* SleepBase::catalog[SleepBase::size_];

class SleepMaster : SleepBase {
	public:
		static void Suspend_all() {
			for (int i = top_; i; i--)
				catalog[i-1]->suspend();
		}

		static void Resume_all() {
			for (int i = 0; i < top_; i++)
				catalog[i]->resume();
		}
};

class SleepClient : SleepBase {
	protected:
		const char* myname;
	public:
		SleepClient(const char* s) : myname{s} {
			cout << "SleepClient " << s << " builded." << endl;

			if (top_ < size_) {
				catalog[top_] = this; // add this object to the catalog
				top_++;
			}
		}
};

class SleepOne : public SleepClient {
	public:
		using SleepClient::SleepClient; // inherit the constructor
		void suspend() const { cout << "SleepOne::suspend " << myname << endl; }
		void resume() const { cout << "SleepOne::resume " << myname << endl; }
};

class SleepTwo : public SleepClient {
	public:
		// inherit and modify the constructor
		SleepTwo(const char* s) : SleepClient(s) {
			cout << "SleepTwo client has just been builded." << endl;
		}

		void suspend() const { cout << "SleepTwo::suspend " << myname << endl; }
		void resume() const { cout << "SleepTwo::resume " << myname << endl; }
};

int main()
{
	SleepMaster base;
	SleepOne s1 {"S1"};
	SleepTwo s2 {"S2"};

	base.Suspend_all();
	base.Resume_all();

	/* the output is:

	   SleepClient S1 builded.
	   SleepClient S2 builded.
	   SleepTwo client has just been builded.
	   SleepTwo::suspend S2
	   SleepOne::suspend S1
	   SleepOne::resume S1
	   SleepTwo::resume S2

	 */

	return(0);
}
