#ifndef COMPUTER_H
#define COMPUTER_H

#include <Hand.h>


// This class generates objects-players that are automatic in response
class Computer: public Hand
{
    public:
        Card * can_pc_play (Card);
        void play_a_card(Card, Deck *);
        Card * check_before_playing_card(int *, bool *, Deck *);
        bool freedom_of_choice(bool *, Deck *, Hand **, int *);
        int choose_what_color();
};

#endif // COMPUTER_H
