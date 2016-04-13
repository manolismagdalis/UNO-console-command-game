#include "Computer.h"

// The extern keyword is used because this function is defined in Necessary_Functions.h
extern void show_the_card(int, int);

Card * Computer::can_pc_play(Card playedCard)
{
    std::vector<Card>::iterator v=vec.begin();
    std::vector<Card> candidates;  // A vector of candidate cards to be played, is created
    int i=0;
    while (v!=vec.end())
    {
        if (v->color==playedCard.color || v->number==playedCard.number)
        {
            candidates.push_back(*v);
        }
        v++;
        i++;
    }
    // Now, the minimum card in candidates is found, if the candidates vector is not empty
    Card * m = new Card;
    m->color=6;
    m->number=12;
    v=candidates.begin();
    i=0;
    while (!candidates.empty() && v!=candidates.end())
    {
       if (v->number <= m->number)
       {
            m=&(*v);
       }
       v++;
       i++;
    }

    if (i!=0)  // i!=0 means that the candidates vector has at least one card.
    {
        return m; // Whether the Card is of color 6 and number 12, is not a concern for now
    }
    else // if there are no candidates, a black card is searched instead.
    {
        v=vec.begin();
        while (v!=vec.end())
        {
            if (v->number==13)
            {
                return &(*v);
            }
            v++;
        }
        v=vec.begin();
        while (v!=vec.end())
        {
            if (v->number==14)
            {
                return &(*v);
            }
            v++;
        }
        // If the function has reached this point, it means that there are no candidates and no black
        // cards in the Computer Player's hand
        return NULL;
    }
}

void Computer::play_a_card(Card playedCard, Deck * deck)
{
    std::vector<Card>::iterator v=vec.begin();
    std::vector<Card> candidates;
    int i=0;
    while (v!=vec.end())
    {
        if (v->color==playedCard.color || v->number==playedCard.number)
        {
            candidates.push_back(*v);
        }
        v++;
        i++;
    }

    Card * m = new Card;
    m->color=6;
    m->number=20;
    v=candidates.begin();

    while (!candidates.empty() && v!=candidates.end())
    {
        if (v->number <= m->number)
        {
            m=&(*v);
        }
        v++;
    }

    std::vector<Card>::iterator m1=vec.begin();
    if (candidates.empty()) // In this case, there is no colored card in the candidates, and a black card is found.
    {
        //A search is performed to find the minimum special card.
        m->number=14;  // The maximum number, a special card can have.
        m->color=0;
        v=vec.begin();
        while (v!=vec.end())
        {
            if (v->number <= m->number && v->color==0)
            {
                m1 = v;
            }
            v++;
        }
    }
    else // Now that a card that is a possible candidate exists, we must find its position in the Computer Player's hand.
    {
        bool s=false; // A flag that will notify us when the card's position is found
        while (m1!=vec.end() && s!=true)
        {
            if (m1->number==m->number && m1->color==m->color)
            {
                s=true;
            }
            m1++;
        }
        m1--;
    }
    //The card that is going to be played, is swapped with the last card in the hand.
    //Because we cannot have a null vector iterator, we build an one-element vector
    //and instantiate our iterator to point to this element.
    std::vector<Card> temporary;
    Card temporary2;
    temporary2.number=0;
    temporary2.color=0;
    temporary.push_back(temporary2);

    std::vector<Card>::iterator temp1=temporary.begin();
    *temp1=vec.back();
    vec.back()=*m1;
    *m1=*temp1;
    //Now, the last card in the hand is the card that is going to be played.
    //It is inserted in the opened pile of the deck and it is removed from the hand
    deck->insert_card(vec.back());
    std::cout << name << " decides to play a card. \n" ;
    std::cout << std::endl;
    vec.pop_back();

    if (vec.size()==1) std::cout << "\nThe " << name << " says UNO! " << std::endl;
    return;
}

// This function returns NULL if a "Take 2 Cards" is not played in the previous turn
Card * Computer::check_before_playing_card(int * take2, bool * check, Deck * deck)
{
    if (*take2!=0) // This is executed when one or more "Take 2 Cards" are opened before the player's turn.
    {
        std::cout << "\nNow, " << name << " must draw " << (*take2)*2 << " cards." << std::endl;
        std::vector<Card>::iterator v=vec.begin();
        //The Computer player tries to find a "Take 2 Cards" to throw, to avoid drawing 2 cards itself.
        while (v!=vec.end())
        {
            if (v->number==12)
            {
                Card * temp=new Card;
                *temp=*v;
                *v=vec.back();
                vec.back()=*temp;

                vec.pop_back();
                std::cout << "Computer decides to play a : " ;
                show_the_card(temp->number, temp->color);
                std::cout << " also." << std::endl;

                if (vec.size()==1) std::cout << "\nThe " << name << " says UNO! " << std::endl;
                *check=true;  // Computer player just played. This is to ensure it will not play one more card.

                return temp;
            }
            v++;
        }
        //if it continues here, that means that the computer has no "Take 2 Cards" cards in its hand.
        //so, it must draw the corresponding number of cards from the deck.
        while (*take2>0)
        {
            draw_a_card(deck->remove_card());
            draw_a_card(deck->remove_card());
            (*take2)--;
        }
        show_cards();
        return NULL;
    }
    else return NULL;
}


bool Computer::freedom_of_choice(bool * check, Deck * deck, Hand ** player, int * rot)
{
    if (*check==true) return true;
    // If check is true, the Computer player have already played a card (a "Take 2 cards")
    // and it is not allowed to play another card.

    Card temp=deck->opened.back();
    Card * n = new Card;
    n=can_pc_play(temp);  // Here it is checked if there is a possible card to be played by the Computer player.
    if (n==NULL)          // n=NULL means that it has no cards to play, so it must draw one from the closed deck.
    {
        std::cout << "The " << name << " draws a card from the deck. " << std::endl;
        draw_a_card(deck->remove_card());
    }
    else return true;

    n=can_pc_play(temp); // It is then rechecked. This code can be reduced to check only the last card.
    if (n==NULL)
    {
        std::cout << "The " << name << " chooses to pass. " << std::endl;
        if (*rot==1) *player=(*player)->next;
        else *player=(*player)->prev;
        return false;
    }
    else return true;

}

// This function returns the number that represents the color that the player wants to change using a black card.
// An array is created. This array contains the number of cards for each color in the hand. The array's index
// represents the number which in turn represents the color of a card.
int Computer::choose_what_color()
{
    int colors[5]={0};
    std::vector<Card>::iterator v=vec.begin();
    while (v!=vec.end())
    {
        colors[v->color]++;
        v++;
    }
    int m=0; // This is the maximum variable. It is used to find in which color the Computer player has the most cards.
    int i=1;
    int j=-1;  //we cannot declare j as 0 because j=0 is a possible value and it represents a black card
    while (i<5)
    {
        if (colors[i]>m)
        {
            m=colors[i];
            j=i;
        }
        i++;
    }
    if (m==0)  // This means that the array is filled only with black cards in which case, the color does not concern us.
    {
        j=rand()%4+1;
    }
    return j;
}
