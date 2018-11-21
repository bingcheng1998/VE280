#include <iostream>
#include "dlist.h"
using namespace std;

#define COMMANDSNUM 11

bool is_int(const string s)
// EFFECTS return true if "s" is a int string
{
	if(s.length() == 1 && s.c_str()[0]<='9' && s.c_str()[0]>='0') return true;
	if(s.length() >1){
		if((s.c_str()[0]<='9' && s.c_str()[0]>='0') || s.c_str()[0] == '-'){
			for(unsigned int i = 1; i< s.length(); i++){
				if(s.c_str()[i]>'9' || s.c_str()[i]<'0') return false;
			} return true;
		}
	} return false;
}

int command_type(const string s)
// EFFECTS return -1 if s is not a command, else return 
//		the number of operands that commmand needs
{
	string commands[COMMANDSNUM] = 
	{"+", "-", "*", "/", "r", "n", "d", "p", "c", "a", "q"};
	for(int i =0; i<COMMANDSNUM; i++){
		if(s == commands[i]){
			if(i <= 4) return 2;
			if(i <= 7) return 1;
			return 0;
		}
	}
	return -1;
}

int _add(int a, int b){ return a+b;}

int _minus(int a, int b){ return b - a;}

int _multiply(int a, int b){ return a*b;}

int _devide(int a, int b){ return b/a;}

void two_operands (Dlist<int> &ilist, int *first, int *second, int (*fn)(int, int))
// MODIFIES ilist, first, second
// EFFECTS calculate fn(first, second), then insert it to ilist.
{
	int *two = new int(fn(*first, *second));
	delete first;
	delete second;
	ilist.insertFront(two);
}

void printAll(const Dlist<int> &ilist)
// EFFECTS print the hole ilist
{
    Dlist<int> elist;
    elist = ilist;
    while(!elist.isEmpty()){
        int *op = elist.removeFront();
        cout<<*op<<" ";
        delete op;
    }
    cout<<"\n";
}

int main(int argc, char *argv[]) {
	Dlist<int> ilist;
	string s = "w";
	int *ip, *first, *second;
	while(s != "q")
	//if "q" detected, end the program.
	{
		cin >> s;
		if(is_int(s)){
			ip = new int(atoi(s.c_str()));
    		ilist.insertFront(ip);
		}
		else if(command_type(s) == 0)
		// when operands needed is 0
		{
			if(s == "a"){
				printAll(ilist);
			} else if(s == "c"){
				while(! ilist.isEmpty()){
					ip = ilist.removeFront();
					delete ip;
				}
			}
		} else if(command_type(s) == 1)
		// when operands needed is 1
		{
			if(! ilist.isEmpty()){
				first = ilist.removeFront();
				if(s == "n"){
					*first = -*first;
					ilist.insertFront(first);
				} else if(s == "d"){
					int * copy_first = new int(*first);
					ilist.insertFront(first);
					ilist.insertFront(copy_first);
				} else if(s == "p"){
					cout<<*first<<endl;
					ilist.insertFront(first);
				}
			} else{
			 cout << "Not enough operands\n";
			 ilist.insertFront(first);
			}
		} else if(command_type(s) == 2)
		// when operands needed is 2
		{
			if(! ilist.isEmpty()){
				first = ilist.removeFront();
				if(! ilist.isEmpty()){
					second = ilist.removeFront();
					if(s == "+"){
						two_operands (ilist, first, second, _add);
					} else if(s == "-"){
						two_operands (ilist, first, second, _minus);
					} else if (s == "*"){
						two_operands (ilist, first, second, _multiply);
					} else if (s == "/"){
						if(*first == 0){cout << "Divide by zero\n";} else
						two_operands (ilist, first, second, _devide);
					} else if (s=="r"){
						ilist.insertFront(first);
						ilist.insertFront(second);
					}
				} else {
					cout << "Not enough operands\n";
					ilist.insertFront(first);
				}
			} else {
				cout << "Not enough operands\n";
			}
		} else {
			cout << "Bad input\n";
		}
	}
	return 0;
}
