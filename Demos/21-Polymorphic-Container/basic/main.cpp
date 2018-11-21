#include <iostream>
#include <cassert>
#include "bigthing_t.h"
#include "list_t.h"
using namespace std;

int main(int argc, char *argv[])
{
	List l;
    cout << "l insert 5 at the front. l is" << endl;
	BigThing *a = new BigThing(5); // Must dynamically allocate the object
	l.insert(a);
    // l is (5)
    l.print();

	List ll;
    cout << "ll insert 4 at the front. ll is" << endl;
	BigThing *b = new BigThing(4);
	ll.insert(b);
    // ll is (4)
    ll.print();

    cout << "Assign ll as a copy of l. ll is" << endl;
	ll = l; // call assignment operator
    // ll is (5)
    ll.print();

    cout << "ll insert 3 at the front. ll is" << endl;
	BigThing *c = new BigThing(3);
	ll.insert(c);
    // ll is (3 5)
    ll.print();

    cout << "do nothing. l is" << endl;
    l.print();

    cout << "Remove the front of ll. ll is" << endl;
	BigThing *d = dynamic_cast<BigThing*>(ll.remove());
	assert(d);
	delete d; // Must delete d!
    ll.print();



    cout << "l insert 4 at the front. l is" << endl;
    BigThing *e = new BigThing(4); // Must dynamically allocate the object
    l.insert(e);
    l.print();

    cout << "Remove the front of l. l is" << endl;
    BigThing *f = dynamic_cast<BigThing*>(l.remove());
    assert(f);
    delete f; // Must delete d!
    l.print();

	return 0;
}
