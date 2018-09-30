#ifndef PLAYER_H
#define PLAYER_H

#include <Hand.h>

/* This class generates objects-players that have a choice on which card to play. */
class Player: public Hand
{
    public:
        void play_a_card(Card, Deck*);
        Card * check_before_playing_card(int *, bool *, Deck *);
        Card * can_pc_play (Card);
        bool freedom_of_choice(bool *, Deck *, Hand **, int *);
        int choose_what_color();
};

#endif // PLAYER_H
