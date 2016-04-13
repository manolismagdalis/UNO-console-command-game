#ifndef CARD_H
#define CARD_H

struct Card
{
    int color;    // 1=red, 2=green, 3=blue, 4=yellow, 0=black
    int number;   // 10=lose_turn, 11=change_rotation, 12=take_2_cards, 13=change_color, 14=take_4_cards
};

#endif // CARD_H
