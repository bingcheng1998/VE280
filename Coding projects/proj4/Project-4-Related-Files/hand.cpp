#include "hand.h"
#include <iostream>
#include <cassert>
using namespace std;


Hand::Hand()
{
    curValue.soft = false;
    curValue.count = 0;
}

void Hand::discardAll()
{
    curValue.soft = false;
    curValue.count = 0;
}

void Hand::addCard(Card c)
{
    assert(c.spot < SPOT_SIZE);
    if (c.spot < JACK)
    {
        curValue.count += (c.spot+2);
    } else if(c.spot < ACE){
        curValue.count += 10;
    } else if(!curValue.soft){
        curValue.count += 11;
        curValue.soft = true;
    } else {
        curValue.count += 1;
    }
}

HandValue Hand::handValue() const
{
    return curValue;
}