#include <iostream>
#include "recursive.h"
#include "p2.h"

using namespace std;
static int k = 0;
list_t listA, listA_answer;
list_t listB, listB_answer;	

void printtrees(){
	k++;
	cout<<"\nThe "<<k<<" th Trees print is:\nlistA:\t";
	list_print(listA);
    cout <<"\nlistB:\t";
    list_print(listB);
    cout << "\nlistA_answer:\t";
    list_print(listA_answer);
    cout << "\nlistB_answer:\t";
    list_print(listB_answer);
    cout << endl;
}

static bool list_equal(list_t l1, list_t l2)
    // EFFECTS: returns true iff l1 == l2.
{
    if(list_isEmpty(l1) && list_isEmpty(l2))
    {
        return true;
    }
    else if(list_isEmpty(l1) || list_isEmpty(l2))
    {
        return false;
    }
    else if(list_first(l1) != list_first(l2))
    {
        return false;
    }
    else
    {
        return list_equal(list_rest(l1), list_rest(l2));
    }    
}    

int main()
{
    int i;
    

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
    cout<<"init state: "<<endl;
	printtrees();
    for(i = 5; i>0; i--)
    {
        listB_answer = list_make(i, listB_answer);
    }
 	printtrees();


    listB = append(listA, listB);
    listA = reverse(listA);

    printtrees();

    if(list_equal(listA, listA_answer) 
        && list_equal(listB, listB_answer))
    {
        cout << "Success!\n";
        return 0;
    }
    else
    {
        cout << "Failed\n";
        return -1;
    }
}
