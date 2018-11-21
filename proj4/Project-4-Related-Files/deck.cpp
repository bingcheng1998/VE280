#include "deck.h"
#include <iostream>

using namespace std;

//#define PRINT_DECK    // print all the 52 cards for debug usage.
//#define CHECK_DECK    // check all the 52 cards to ensure that there is no duplication for debug usage.

static void print_deck(Card* card ,int n)
// REQUIRE: n>0.
// EFFECTS: print first n piece of cards from 52 pieces
{
#ifdef PRINT_DECK
    cout<<"print all "<<n+1<<" piece of cards----"<<endl;
    for (int i = 0; i < n; ++i)
    {
        cout<<"(["<<i<<"] "<<SuitNames[card[i].suit]<<", "<<SpotNames[card[i].spot]<<")\t";
        if((i+1)%5 == 0 && i != n) cout<<endl;
    }
    cout<<"\n🖨 print finished--------------------"<<endl;
#endif
}

static void check(Card* deck)
// REQUIRE: deck must has 52 piece of cards.
// EFFECTS: check all the 52 cards to ensure that there is no duplication for debug usage.
{
#ifdef CHECK_DECK
    int card[SUIT_SIZE][SPOT_SIZE];
    for (int i = 0; i < SPOT_SIZE; ++i)
    {
        for (int j = 0; j < SUIT_SIZE; ++j)
        {
            card[j][i] = 0;
        }
    }
    for (int i = 0; i < DeckSize; ++i)
    {
        for (int j = 0; j < SUIT_SIZE; ++j)
        {
            for (int k = 0; k < SPOT_SIZE; ++k)
            {
                if (deck[i].spot == Spot(k) && deck[i].suit == Suit(j))
                {
                    card[j][k] ++;
                }
            }
        }
    }
    for (int i = 0; i < SPOT_SIZE; ++i)
    {
        for (int j = 0; j < SUIT_SIZE; ++j)
        {
            if(card[j][i]!=1) {
                const Spot spot = Spot(i);
                const Suit suit = Suit(j);
                cout<<"verification failed! Poker cards have duplicate card: ["<<(suit)<<"，"<<(spot)<<"] with number: "<<card[j][i]<<endl;
                exit(0);
            }
        }
    }
    cout<<"Verification success! The playing card is a complete 52 cards."<<endl;
#endif
}


Deck::Deck():next(0)
{
    for (int j = 0; j < SUIT_SIZE; ++j)
    {
        for (int i = 0; i < SPOT_SIZE; ++i)
        {
            deck[i+j*SPOT_SIZE].spot = Spot(i);
            deck[i+j*SPOT_SIZE].suit = Suit(j);
        }
    }
    next = 0;
    check(deck);
    print_deck(deck, 52); //check all 
}

void Deck::reset()
{
    Deck();
}

void Deck::shuffle(int n)
{
    cout<<"cut at "<< n <<endl;
    Card deck_new[DeckSize];
    int left = 0, right = n;
    int shuffled = min(n, DeckSize-n);
    bool L = false;
    for (int i = 0; i < shuffled*2; ++i)
    {
        if (L) {
            deck_new[i] = deck[left];
            left ++;
        } else {
            deck_new[i] = deck[right];
            right ++;
        }
        L = !L;
    }
    if (n > DeckSize - n)
    {
        for (int i = 0; i < n - (DeckSize - n); ++i)
        {
            deck_new[shuffled*2+i] = deck[shuffled+i];
        }
    } else if (n < DeckSize - n) 
    {
        for (int i = 0; i < (DeckSize - n) - n; ++i)
        {
            deck_new[shuffled*2+i] = deck[2*shuffled+i];
        }
    }

    for (int i = 0; i < DeckSize; ++i)
    {
        deck[i] = deck_new[i];
    }
    check(deck);
    print_deck(deck, 52); //check all 
    next = 0;
}



Card Deck::deal()
{
    Card card = deck[next];
    next++;
    if(cardsLeft() == 0){
        DeckEmpty deckEmpty;
        throw(deckEmpty);
    }
    return card;
}

int Deck::cardsLeft()
{
    return DeckSize - next;
}







