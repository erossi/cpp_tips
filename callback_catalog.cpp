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

/*! Same as the static derived example, but with managed catalog.
 *
 * This example should be able to handle the un-registering of a client member.
 */

#include <iostream>

using namespace std;

class SleepBase {
	protected:
		static const int size_ { 5 }; //! fixed size of the catalog
		static unsigned int top_; //! registered objects.
		static SleepBase *catalog[];
	public:
		virtual void suspend() const {};
		virtual void resume() const {};
};

// Global variables
unsigned int SleepBase::top_ { 0 }; //! registered objects.
SleepBase* SleepBase::catalog[SleepBase::size_];

// Master class
class SleepMaster : SleepBase {
	public:
		static void Suspend_all() {
			cout << "Suspend All: catalog[" << top_ << "/" <<
				size_ << "]" << endl;

			for (unsigned int i = top_; i; i--)
				catalog[i-1]->suspend();
		}

		static void Resume_all() {
			cout << "Resume All: catalog[" << top_ << "/" <<
				size_ << "]" << endl;

			for (unsigned int i = 0; i < top_; i++)
				catalog[i]->resume();
		}
};

// Client class
class SleepClient : SleepBase {
	protected:
		const char* sleep_name;
		int sleep_index { 0 }; // the index in the catalog.
		bool sleep_registered { false };
	public:
		SleepClient(const char* s) : sleep_name { s } {
			cout << "Client " << sleep_name << " builded, ";

			// if the catalog does have space left.
			if (top_ < size_) {
				sleep_index = top_; // register my index
				catalog[top_] = this; // add me to the catalog
				sleep_registered = true;
				top_++;
				cout << "registered at index " <<
					sleep_index << "/" << size_ << endl;
			} else {
				cout << "catalog FULL, not registered." << endl;
			}
		}

		~SleepClient() {
			// if I'm in the catalog, remove me
			// and shrink the catalog.
			// \note I can be the index 0 of the catalog.
			if (sleep_registered) {
				cout << "Removing index: " <<
					sleep_index << "/" << size_ << endl;

				// if I'm not the last in the array
				if (top_ - sleep_index > 1) {
					// shift the array
					for (unsigned int i = sleep_index; i < top_; i++)
						catalog[i] = catalog[i+1];
				}

				top_--;
			} else {
				cout << "Index " << sleep_index <<
					"/" << top_ << " not registered!" << endl;
			}
		}
};


class SleepOne : public SleepClient {
	public:
		using SleepClient::SleepClient; // inherit the constructor

		void suspend() const { cout << sleep_name << " suspended." << endl; }
		void resume() const { cout << sleep_name << " resumed." << endl; }
};

class SleepTwo : public SleepClient {
	public:
		// inherit and modify the constructor
		SleepTwo(const char* s) : SleepClient(s) {
			cout << "Custom SleepTwo client build." << endl;
		}

		void suspend() const { cout << sleep_name << " suspend(2)." << endl; }
		void resume() const { cout << sleep_name << " resumed(2)." << endl; }
};

void addme()
{
	SleepOne s1 {"S1-addme"};
	SleepTwo s2 {"S2-addme"};

	cout << "Destroy addme objects." << endl;
}

int main()
{
	SleepMaster base;
	SleepOne s1 {"S1"};
	SleepTwo s2 {"S2"};
	SleepOne s3 {"S1-2"};
	SleepTwo s4 {"S2-2"};

	base.Suspend_all();
	base.Resume_all();

	addme();

	base.Suspend_all();
	base.Resume_all();

	/* the output is:

Client S1 builded, registered at index 0/5
Client S2 builded, registered at index 1/5
Custom SleepTwo client build.
Client S1-2 builded, registered at index 2/5
Client S2-2 builded, registered at index 3/5
Custom SleepTwo client build.
Suspend All: catalog[4/5]
S2-2 suspend(2).
S1-2 suspended.
S2 suspend(2).
S1 suspended.
Resume All: catalog[4/5]
S1 resumed.
S2 resumed(2).
S1-2 resumed.
S2-2 resumed(2).
Client S1-addme builded, registered at index 4/5
Client S2-addme builded, catalog FULL, not registered.
Custom SleepTwo client build.
Destroy addme objects.
Index 0/5 not registered!
Removing index: 4/5
Suspend All: catalog[4/5]
S2-2 suspend(2).
S1-2 suspended.
S2 suspend(2).
S1 suspended.
Resume All: catalog[4/5]
S1 resumed.
S2 resumed(2).
S1-2 resumed.
S2-2 resumed(2).
Removing index: 3/5
Removing index: 2/5
Removing index: 1/5
Removing index: 0/5

	 */

	return(0);
}
