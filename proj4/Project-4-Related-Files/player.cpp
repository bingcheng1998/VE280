#include "player.h"
#include <iostream>

using namespace std;

// --------------------------------Simple----------------------------------

class Simple: public Player
{
public:
	Simple();

	int bet(unsigned int bankroll, unsigned int minimum); 

    bool draw(Card dealer, const Hand &player); 

    void expose(Card c);

    void shuffled();
};

Simple::Simple()
{
}

int Simple::bet(unsigned int bankroll, unsigned int minimum)
{
	return minimum;
}

bool Simple::draw(Card dealer, const Hand &player)
{
	int count = player.handValue().count;
	Spot spot = dealer.spot;

// The first set of rules apply if the player has a “hard count”, i.e., his best total counts an 
//	Ace (if any) for 1, not 11, or if his hand does not contain an Ace.
// • If the player’s hand totals 11 or less, he always hits.
// • If the player’s hand totals 12, he stands if the dealer shows 4, 5, or 6; otherwise he hits.
// • If the player’s hand totals between 13 and 16 inclusive, he stands if the dealer shows a 2
// 		through a 6 inclusive; otherwise he hits.
// • If the player's hand totals 17 or greater, he always stands.

	if (player.handValue().soft == false)
	{
		if(count <= 11) {return true;} 
		if(count == 12 && (spot>=FOUR && spot <=SIX )) {return false;} 
		else if(count == 12 && !(spot>=FOUR && spot <=SIX )) return true;
		if(count <=16 && count >=13 && (spot >= TWO && spot <= SIX)) {return false;} 
		else if(count <=16 && count >=13 && !(spot >= TWO && spot <= SIX)) return true;
		if(count >= 17) return false;
		return false;
	}

	if(count <= 17 ) return true;
	if(count == 18 && ((spot == TWO || spot == SEVEN || spot == EIGHT))) {return false;} 
	else if(count == 18 && !((spot == TWO || spot == SEVEN || spot == EIGHT))) return true;
	if((count >= 19) && count <= 21) return false;

// The second set of rules applies if the player has a “soft count”---his best total includes one 
//	Ace worth 11. (Note that a hand would never count two Aces as 11 each--that's a bust of 22.)
// • If the player’s hand totals 17 or less, he always hits.
// • If the player’s hand totals 18, he stands if the dealer shows a 2, 7, or 8, otherwise he hits.
// • If the player’s hand totals 19 or greater, he always stands.
	
	count -= 10;
	if(count <= 11) {return true;} 
	if(count == 12 && (spot>=FOUR && spot <=SIX )) {return false;} 
	else if(count == 12 && !(spot>=FOUR && spot <=SIX )) return true;
	if(count <=16 && count >=13 && (spot >= TWO && spot <= SIX)) {return false;} 
	else if(count <=16 && count >=13 && !(spot >= TWO && spot <= SIX)) return true;
	if(count >= 17) return false;
	return false;
}

void Simple::expose(Card c)
{
}

void Simple::shuffled()
{
}

static Simple simple;

extern Player *get_Simple(){
	return &simple;
}

// ---------------------------------Counting---------------------------------

class Counting: public Simple
{
	int count;

public:

	Counting();

	int bet(unsigned int bankroll, unsigned int minimum); 

    void expose(Card c);

    void shuffled();
};

Counting::Counting():count(0)
{

}

int Counting::bet(unsigned int bankroll, unsigned int minimum)
{
	if (count >= 2 && bankroll >= minimum * 2)
	{
		return minimum * 2;
	}
	return minimum;
}


void Counting::expose(Card c)
{
	if (c.spot>=TEN)
	{
		count -- ;
	} else if(c.spot>=TWO && c.spot <= SIX){
		count ++ ;
	}
}

void Counting::shuffled()
{
	count = 0;
}

static Counting counting;

extern Player *get_Counting(){
	return &counting;
}


