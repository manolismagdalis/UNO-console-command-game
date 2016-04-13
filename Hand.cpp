#include "Hand.h"

// The extern keyword is used because this function is defined in Necessary_Functions.h
extern void show_the_card(int, int);


void Hand::show_cards()
{
    std::vector<Card>::iterator v = vec.begin();
    Card temp;
    std::cout << "\n\n";
    int i=1;
    while (v!=vec.end())
    {
        temp=*v;
        std::cout << "(" << i << ") ->" ;
        show_the_card(temp.number, temp.color);
        i++;
        v++;
    }
    std::cout << "\n\n" ;
    return;
}

// Draws a card from the closed deck
void Hand::draw_a_card(Card temp)
{
    vec.push_back(temp);
    return;
}


void Hand::take_two_cards(Hand * player, Deck * deck)
{
    for (int i=0; i<2; i++)
    {
        player->draw_a_card(deck->remove_card());
    }
    return;
}


// Here, the program checks what should be done with the turn. For example,
// if a Change_Rotation card is played, the rotation of turns is changed.
// Then, for the case in which a "Take 4 Cards" is played (which is of color black)
// we change the card before it is thrown on the pile of open cards, to match certain criteria
void Hand::check_played_card(Deck * deck, int * rot, Hand ** player, int * take2)
{
    Card temp = deck->opened.back();
    if(temp.number==11)
    {
        if (*rot==1)
        {
            *rot=0;
            *player=(*player)->prev;
        }
        else
        {
            *rot=1;
            *player=(*player)->next;
        }
    }
    else
    {
        if (*rot==1)
        {
            *player=(*player)->next;
        }
        else
        {
            *player=(*player)->prev;
        }
        // The rest of the special cards are checked
        if (temp.number==10) // 10 represents the special card "Lose_next_player's_turn
        {
            if (*rot==1)
            {
                *player=(*player)->next;
            }
            else
            {
                *player=(*player)->prev;
            }
        }
        else if (temp.number==12) // 12 represents the special card "Take 2 Cards"
        {
            (*take2)++;
        }
        // In the case of a black card, it is changed in the desired color before it is thrown
        // on the pile of opened cards
        else if (temp.number==13 || temp.number==14)  // 13 represents "Change Color" and 14 represents "Take 4 Cards"
        {
            Card wild;
            wild.color=choose_what_color();
            if (temp.number==14)
            {
                std::cout << "\nThe " << (*player)->name << " takes 4 cards! " << std::endl;
                for (int g=0; g<2; g++)
                {
                    take_two_cards(*player, deck);
                }
            }
            // The number of a black card is not really a concept, so it is changed to something impossible
            wild.number=50;
            deck->opened.push_back(wild);
        }
    }
    return;
}
