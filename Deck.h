#ifndef DECK_H
#define DECK_H

#include "Container.h"


class Deck: public Container
{
    public:
        friend int myrandom(int i);
        std::vector<Card> opened; //This is the stack of opened cards of the deck
        /* Inside the Deck constructor, we fill the deck with cards and we open the top closed card */
        Deck()
        {
            Card temp;
            for (int i=0; i<12; i++)
            {
                temp.number = i+1;
                for (int j=0; j<4; j++)
                {
                    temp.color = j+1;
                    vec.push_back(temp);
                    vec.push_back(temp);
                }
            }

            temp.number = 0;
            for (int i=0; i<4; i++)
            {
                temp.color=i+1;
                vec.push_back(temp);
            }
            temp.color=0;
            for (int j=0; j<2; j++)
            {
                temp.number = j+13;
                for (int i=0; i<4; i++)
                {
                    vec.push_back(temp);
                }
            }
        }
        void open_one_card();
        Card remove_card();
        void insert_card(Card);
        void shuffle_the_deck();
};

#endif // DECK_H
