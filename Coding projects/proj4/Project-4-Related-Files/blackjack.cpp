#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <cassert>

#include "player.h"
#include "rand.h"
#include "deck.h"

using namespace std;

#define CUTNUMBER 7 //number of random cut

int player_wins(const Hand &h_player, const Hand &h_dealer, bool hit_happened);
// EFFECTS: retrun true if player wins

int total_count(Hand hand);
// EFFECTS: return the totol count to make it < 21 or bust.

string card2str(Card card);
// EFFECTS: return the string of card for debug and print.

void file_shuffle(Deck &deck, char* file_name);
// REQUIRE: deck must has 52 piece of cards.
// EFFECTS: shuffle deck with file.

void random_shuffle(Deck &deck);
// REQUIRE: deck must has 52 piece of cards.
// EFFECTS:shuffle cards with random cut in CUTNUMBER times

int main(int argc, char *argv[]) {
	Deck deck;
	assert(argc > 3);
	int input_file = false;
	if(argc > 5) input_file = true;
	int bankroll = atoi(argv[1]);
	int min_bet = atoi(argv[2]);
	int hands = atoi(argv[3]);
	string s_simple = "simple";		// I assume if it's not simple, it must be counting. To avoid broken.
	string argv_4 = argv[4];
	bool simple_player = false;
	if(s_simple == argv_4) simple_player = true; 
	if (input_file)
	{
		file_shuffle(deck, argv[5]);
	} else {
		random_shuffle(deck);
	}
	Player *player;
	if (simple_player)
	{
		player = get_Simple();
	} else 
	{
		player = get_Counting();
	}
	int hands_real = 0;
	for (int i = 0; i < hands; ++i)
	{
		bool hit_happened = false;
		
		Hand h_player, h_dealer;
		Card dealer;
		Card up_dealer;

		Card card;

		if(player->bet(bankroll, min_bet) > bankroll) break;
		hands_real = i+1;
		cout<<"# Hand "<<i+1<<" bankroll "<<bankroll<<endl;
		if (deck.cardsLeft()<20)
		{
			random_shuffle(deck);
			player->shuffled();
		}
		int bet_this_round = player->bet(bankroll, min_bet);
		cout<<"# Player bets "<<bet_this_round<<endl;
		//simple->bet(bankroll, min_bet);
		try {
			card = deck.deal();
			cout<<"Player dealt "<<card2str(card)<<endl;
			h_player.addCard(card);
			player->expose(card);

			up_dealer = deck.deal();
			cout<<"Dealer dealt "<<card2str(up_dealer)<<endl;
			h_dealer.addCard(up_dealer);
			player->expose(up_dealer);

			card = deck.deal();
			cout<<"Player dealt "<<card2str(card)<<endl;
			h_player.addCard(card);
			player->expose(card);

			bool hit = player->draw(up_dealer, h_player);
			
			dealer = deck.deal();
			h_dealer.addCard(dealer);
			// check whether player will hit for cards
			while(hit)
			{
				hit_happened = true;
				card = deck.deal();
				cout<<"Player dealt "<<card2str(card)<<endl;
				h_player.addCard(card);
				player->expose(card);
				hit = player->draw(up_dealer, h_player);
			}
		}
		catch (DeckEmpty n){cerr<<"Empty!"<<endl;}		//to make sure the deck is not empty.

		if (total_count(h_player) > 21 || (total_count(h_player) == 21 && hit_happened == false))
		{
			
		} else {
			cout<<"Player's total is "<<total_count(h_player)<<endl;
			cout<<"Dealer's hole card is "<<card2str(dealer)<<endl;
			player->expose(dealer);
			while(h_dealer.handValue().count<17 || ((h_dealer.handValue().count>21 && h_dealer.handValue().count - 10 <17) && h_dealer.handValue().soft)){
				dealer = deck.deal();
				cout<<"Dealer dealt "<<card2str(dealer)<<endl;
				player->expose(dealer);
				h_dealer.addCard(dealer);
			}
			cout<<"Dealer's total is "<<total_count(h_dealer)<<endl;
		}
		int p_wins = player_wins(h_player, h_dealer, hit_happened);
		h_player.discardAll();
		h_dealer.discardAll();
		if( p_wins == 2){
			bankroll += (bet_this_round *3)/2;
		} else if(p_wins < 0){
			bankroll -= bet_this_round;
		} else if(p_wins == 1){
			bankroll += bet_this_round;
		}
	}
	cout<<"# Player has "<<bankroll<<" after "<<hands_real<<" hands"<<endl;
}

int total_count(Hand hand){
	if(!hand.handValue().soft) return hand.handValue().count;
	if(hand.handValue().count<=21) return hand.handValue().count;
	return hand.handValue().count-10;
}

int player_wins(const Hand &h_player, const Hand &h_dealer, bool hit_happened){
	//cout<<"DEBUG: D: "<< total_count(h_dealer) <<", P: "<< total_count(h_player)<<endl;
	if(total_count(h_player) == 21 && hit_happened == false){
		cout << "# Player dealt natural 21\n";
		return 2;
	}
	if(total_count(h_player)>21) {
		cout<<"Player's total is "<<total_count(h_player)<<endl;
		cout << "# Player busts\n";
		return -1;
	} 
	if (total_count(h_dealer)>21)
	{
		cout << "# Dealer busts\n";
		return 1;
	}
	if (total_count(h_dealer) > total_count(h_player))
	{
		cout << "# Dealer wins\n";
		return -1;
	}
	if (total_count(h_dealer) < total_count(h_player))
	{
		cout << "# Player wins\n";
		return 1;
	}
	cout << "# Push\n";
	return 0;
}

void file_shuffle(Deck &deck, char* file_name){
	ifstream i_file;
	i_file.open(file_name);
	int shuffle_point_length = 0;
	if (i_file.fail()) {
	cout<<"Error: Cannot open file "<< file_name<<" !"<<endl; 
		exit(0);
	}
	cout << "# Shuffling the deck\n";
	string line;
	getline(i_file, line);
	istringstream iStream;
	iStream.str(line);
	while(iStream){
		int shuffle_point;
		iStream >> shuffle_point;
		if (!iStream) break;
		shuffle_point_length++;
		deck.shuffle(shuffle_point);
	}
	assert(shuffle_point_length>-1);
	i_file.close();
}

void random_shuffle(Deck &deck){
	cout << "# Shuffling the deck\n";
	for (int i = 0; i < CUTNUMBER; ++i)
	{
		deck.shuffle(get_cut());
	}
}

string card2str(Card card){
	ostringstream card_stream;
	card_stream<<SpotNames[card.spot]<<" of "<<SuitNames[card.suit];
	return card_stream.str();
}







































