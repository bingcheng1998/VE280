#include <iostream>
#include "deck.h"
#include "card.h"
using namespace std;

void print_deck(Card card, int i){
cout<<"\n"<<"⤵️ 发牌：(["<<i+1<<"] "<<SuitNames[card.suit]<<", "<<SpotNames[card.spot]<<") ";
}

int main(int argc, char *argv[]) {
	Deck deck;
	cout<<"切牌"<<endl;
	deck.shuffle(52);
	//Deck();
	for (int i = 0; i < 10; ++i)
	{
		print_deck(deck.deal(), i);
		cout<<"\t 剩余牌数量："<<deck.cardsLeft();
	}
	cout<<endl;
}