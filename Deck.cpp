#include "Deck.h"

// The extern keyword is used because this function is defined in Necessary_Functions.h
extern int myrandom (int i);


// This happens only in the beginning of the game. A card is removed from the closed cards,
// and is inserted in the opened cards.
// If the top closed card is +4 or Change_Color, then put it swap it with a card in random
// position inside the deck and open this one instead. The reason, this function is not
// embedded in the constructor is because, in the constructor, the deck is not yet shuffled.
void Deck::open_one_card()
{
    std::vector<Card>::iterator last = vec.end()-1;
    std::vector<Card>::iterator middle;
    int i;
    Card temp;
    while ( last->number==13 || last->number==14 )
    {
        std::cout << "The first card was \"+4\" or \"Change Color\" so another card is chosen.. " << std::endl;
        i=rand() % 108;
        middle=vec.begin()+i-1;
        temp=*last;
        *last=*middle;
        *middle=temp;
        last=vec.end()-1;
    }
    opened.push_back(*last);
    vec.pop_back();
    return;
}

/* A card is removed from the deck only from the top of the pile of closed cards */
Card Deck::remove_card()
{
    Card temp;
    temp = vec.back();
    vec.pop_back();
    return temp;
}

/* A new card is inserted in the deck. The insertion to the deck happens ONLY in the pile of opened cards */
void Deck::insert_card(Card temp)
{
    opened.push_back(temp);
    return;
}


/** This happens only once in every game, in the beginning. For that reason,
it may be moved in the Deck's constructor **/
void Deck::shuffle_the_deck()
{
    random_shuffle( vec.begin() , vec.end(), myrandom);
    return;
}

