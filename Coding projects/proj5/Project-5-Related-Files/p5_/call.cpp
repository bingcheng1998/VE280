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
    cout<<"---------------------------输出全部--------------------------"<<endl;
    while(!elist.isEmpty()){
        customers *op = elist.removeFront();
        op->print_all();
    }
    cout<<"---------------------------输出完毕--------------------------"<<endl;

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
	//customers *intermediary;
	bool exist = false;
	for (int j = 0; j < customers_num; ++j)
	{
		customers *cus = ilist.removeBack();
		// if (cus->get_timestamp() == tick)
		// 	cus->print_call();
		if (cus->get_timestamp() <= tick){
			//cus->print_call();
			if ( current -> get_status() == STATUSNUM)
			{
				delete current;
				current = cus;
				//customers_num --;
				//delete cus;
			} else if (cus->get_status() > current->get_status() ){
				//intermediary = cus;
				//cus = current;
				current = cus;
			} else if (cus->get_timestamp() < current -> get_timestamp() || cus->get_status() == current->get_status()){
				current = cus;
			}
			exist = true;
			current_member = current;
			//cout<<"debug 最高级客户：";
			//current_member->print_all();
		}
		//cout<<"debug "<<cus->get_timestamp()<<" "<<i<<endl;
		ilist.insertFront(cus);
		//printAll(ilist);
	}

	if(exist){
		for (int j = 0; j < customers_num; ++j){
			customers *cus = ilist.removeBack();
			if(cus -> get_name() == current_member -> get_name()){

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
	 customers *cus;
	 customers *current_member = new customers(2, "Just_an_interface", status, 0);
	// //cus->print_all();
	 Dlist<customers> ilist;
	 int num_tick = 0;
	// ilist.insertFront(cus);
	// cus = new customers(0, "hilsy", Status(2), 5);
	// ilist.insertFront(cus);
	// printAll(ilist);

	

	int customers_num = 0;
	cin>>customers_num;
	for (int i = 0; i < customers_num; ++i)
	{
		int i_timestamp, i_duration;
		string s_name, s_status;
		cin>> i_timestamp>> s_name>>s_status>>i_duration;
		cus = new customers(i_timestamp, s_name, str2sta(s_status), i_duration);
		ilist.insertFront(cus);
		//printAll(ilist);
	}

	while(!ilist.isEmpty()){
		cout<<"Starting tick #"<<num_tick<<endl;
		num_tick++;
		for (int j = 0; j < customers_num; ++j)
		{
			customers *cus = ilist.removeBack();
			if (cus->get_timestamp() == num_tick-1)
				cus->print_call();
			//cout<<"debug "<<cus->get_timestamp()<<" "<<num_tick-1<<endl;
			ilist.insertFront(cus);
			//printAll(ilist);
		}
		if(current_member->get_duration() == 0){
			if(!get_current(current_member, ilist, num_tick-1, customers_num)) {continue; }
			else {
				cout<<"Answering call from "<<current_member->get_name()<<endl;
				current_member->duration_decrease();
			}
		} else {
			current_member->duration_decrease();
		}
		

	}
	cout<<"Starting tick #"<<num_tick<<endl;
	return 0;

}