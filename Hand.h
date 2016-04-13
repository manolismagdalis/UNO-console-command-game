#ifndef HAND_H
#define HAND_H

#include "Container.h"
#include "Deck.h"

class Hand: public Container
{
    public:
        std::string name;
        Hand * next;
        Hand * prev;
        void show_cards();
        void draw_a_card(Card);
        void take_two_cards(Hand *, Deck *);
        void check_played_card(Deck *, int*, Hand **, int *);

        virtual void play_a_card(Card, Deck *)=0;
        virtual Card * check_before_playing_card(int *, bool *, Deck *)=0;
        virtual bool freedom_of_choice(bool *, Deck *, Hand **, int *)=0;
        virtual int choose_what_color()=0;
};

#endif // HAND_H
