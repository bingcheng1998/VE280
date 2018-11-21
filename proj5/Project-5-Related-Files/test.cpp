#include <iostream>
#include "dlist.h"
using namespace std;

void printAll(const Dlist<int> &ilist){
    Dlist<int> elist;
    elist = ilist;
    while(!elist.isEmpty()){
        int *op = elist.removeFront();
        cout<<*op<<" ";
    }
    cout<<"\n";
}

int main(int argc, char *argv[])
{
    int result = 0;

    Dlist<int> ilist;
    int *ip = new int(1);
    ilist.insertFront(ip);
    printAll(ilist);
    //cerr<<"sert 1"<<endl;
    ip = ilist.removeFront();
    printAll(ilist);
    if(*ip != 1)
        result = -1;
    delete ip;

    ip = new int(1);
    ilist.insertFront(ip);
    printAll(ilist);

    ip = new int(2);
    ilist.insertFront(ip);
    printAll(ilist);

    ip = new int(3);
    ilist.insertFront(ip);
    printAll(ilist);

    if(!ilist.isEmpty())
        result = -1;

    Dlist<int> elist;
    elist = ilist;

    while(!elist.isEmpty()){
        int *op = elist.removeFront();
        cout<<*op<<" ";
    }

    ip = new int(3);
    elist.insertFront(ip);

    printAll(elist);
    printAll(ilist);

    cout<<"result = "<<result<<endl;
    return result;
}
