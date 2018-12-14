#include <iostream>
#include "dlist.h"
#include <string>
#include <cassert>
using namespace std;


enum Status {
	REGULAR, SILVER, GOLD, PLATINUM, STATUSNUM
};

const char *StatusNames[] = {"regular", "silver", "gold", "platinum", "ERROR_HAPPEND"};

class customer_duration_less_than_zero{
	// OVERVIEW: an exception class
};

class customers
{
	// OVERVIEW: contains a customer
private:
	int timestamp;
	string name;
	Status status;
	int duration;
public:
	customers(int t, string n, Status s, int d): timestamp(t), name(n), status(s), duration(d) {}
	int get_timestamp() { return timestamp; }
	string get_name() {return name; }
	Status get_status() {return status; }
	int get_duration() {return duration; }
	void duration_decrease();
	void print_call() const;
	void print_all() const;
	//~customers();
};

void customers::print_call() const
// EFFECTS print a full call.
{
	cout<<"Call from "<<name<<" a "<<StatusNames[status]<<" member"<<endl;
}

void customers::print_all() const
// EFFECTS print all messages of a member.
{
	cout<<"Call from "<<name<<" a "<<StatusNames[status]<<" member from "<<timestamp<<" with duration "<<duration<<endl;
}

void customers::duration_decrease()
// MODIFIES duration.
// EFFECTS decrease duration by one until it is eqaul to zero.
{
	if(duration>0) {duration--;}
	else {
		customer_duration_less_than_zero c;
		throw(c);
	}
}


void printAll(const Dlist<customers> &ilist)
// EFFECTS print all menbers in the ilist.
{
    Dlist<customers> elist;
    elist = ilist;
    cout<<"---------------------------print all--------------------------"<<endl;
    while(!elist.isEmpty()){
        customers *op = elist.removeFront();
        op->print_all();
    }
    cout<<"---------------------------finish print-----------------------"<<endl;

}

Status str2sta(const string status)
// EFFECTS return the status by string.
{
	for (int i = 0; i < STATUSNUM; ++i)
	{
		if(status == StatusNames[i]){
			return Status(i);
		}
	}
	return Status(STATUSNUM);
}

bool get_current(customers*& current_member, Dlist<customers> &ilist, const int tick, int &customers_num)
// MODIFIES current_member, ilist, customers_num
// EFFECTS get the most significant member "current_member" 
// 		   from "ilist", then decrease "customers_num" by one
//		   if there exist that "current_member". Or do nothing.
{
	customers *current = new customers(tick, "interface_in_get_current", STATUSNUM, 0);
	bool exist = false;
	for (int j = 0; j < customers_num; ++j)
	{
		customers *cus = ilist.removeBack();
		if (cus->get_timestamp() <= tick){
			//cus->print_call();
			if ( current -> get_status() == STATUSNUM)
			{
				delete current;
				current = cus;
			} else if (cus->get_status() > current->get_status() ){
				current = cus;
			} else if (cus->get_timestamp() < current -> get_timestamp() || cus->get_status() == current->get_status()){
				current = cus;
			}
			exist = true;
			current_member = current;
		}
		ilist.insertFront(cus);
		//printAll(ilist);
	}

	if(exist){
		for (int j = 0; j < customers_num; ++j){
			customers *cus = ilist.removeBack();
			if(cus -> get_name() == current_member -> get_name()){
				//delete cus;
				break;
			}
			else ilist.insertFront(cus);
		}
		customers_num --;
	}
	
	return exist;
}

int main(int argc, char *argv[]) {
	 Status status = Status(0);
	 customers *i_cus;
	 customers *current_member = new customers(2, "Just_an_interface", status, 0);
	 Dlist<customers> ilist;
	 int num_tick = 0;
	// printAll(ilist);

	int customers_num = 0;
	cin>>customers_num;
	//get all the messages from the file, and put them into Dlist.
	for (int i = 0; i < customers_num; ++i)
	{
		int i_timestamp, i_duration;
		string s_name, s_status;
		cin>> i_timestamp>> s_name>>s_status>>i_duration;
		i_cus = new customers(i_timestamp, s_name, str2sta(s_status), i_duration);
		ilist.insertFront(i_cus);
	}
	//get all the calls from dlist, them answer the highest customer.
	while(!ilist.isEmpty() ){
		cout<<"Starting tick #"<<num_tick<<endl;
		num_tick++;
		for (int j = 0; j < customers_num; ++j)
		{
			customers *cus = ilist.removeBack();
			if (cus->get_timestamp() == num_tick-1)
				cus->print_call();
			ilist.insertFront(cus);
		}
		if(current_member->get_duration() == 0){
			delete current_member;
			if(!get_current(current_member, ilist, num_tick-1, customers_num)) {continue; }
			else {
				cout<<"Answering call from "<<current_member->get_name()<<endl;
				current_member->duration_decrease();
			}
			//cerr<<"customers_num"<<customers_num<<endl;
		} else {
			current_member->duration_decrease();
		}
	}
	for (int i = 0; i < current_member->get_duration()+1; ++i)
	{
		cout<<"Starting tick #"<<num_tick<<endl;
		num_tick++;
	}
	delete current_member;
	return 0;

}