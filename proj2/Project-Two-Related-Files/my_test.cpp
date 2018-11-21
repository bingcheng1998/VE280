#include <iostream>
#include "recursive.h"
#include "p2.h"

using namespace std;


int Product(int x, int y){
	return x*y;
}
int Add(int x, int y){
	return x+y;
}

bool odd(int odd){
	if (odd%2 == 0) return false;
	return true;
}

int main(int argc, char const *argv[])
{
	int i = 0;
	list_t listA, listA_answer;
    list_t listB, listB_answer;
	listA = list_make();
    listB = list_make();
    listA_answer = list_make();
    listB_answer = list_make();

    for(i = 5; i>0; i--)
    {
        listA = list_make(i, listA);
        listA_answer = list_make(6-i, listA_answer);
        listB = list_make(i+10, listB);
        listB_answer = list_make(i+10, listB_answer);
    }
    list_print(listA);
    cout << endl;
    list_print(listB);
    cout << endl;
    cout <<"size of listA = " << size(listA)<<endl;
    cout << "sum of listA = " << sum(listA) <<endl;
    cout << "product of listA = " << product(listA) <<endl;
    cout << "accumulate(listA, add, 0) = " << accumulate(listA, Add, 0) << endl;
	cout << "accumulate(listA, product, 1) = " << accumulate(listA, Product, 1) << endl;
	cout<<"listA : ";
	list_print(listA);
    cout << "\n listA~: ";
    list_print(reverse(listA));
    cout << endl;
    list_print(list_make(9, listA));
    cout<<endl;
    list_print(append(listA, listB));
    cout<<endl;
    list_print(filter_odd(append(listA, listB)));
    cout<<endl;
    list_print(filter_even(append(listA, listB)));
    cout<<endl;
    list_print(filter(append(listA, listB), odd));
    cout<<endl;
    list_print(chop(listA, 2));
    cout<<endl;
    list_print(insert_list(listA, listB, 2));
	return 0;
}