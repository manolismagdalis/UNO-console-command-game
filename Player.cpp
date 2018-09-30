#include "Player.h"


void Player::play_a_card(Card playedCard, Deck * deck)
{
    std::string c;
    int n;
    while (1)
    {
        std::cout << "\nWhich card does the player want to play? " << std::endl;
        std::cout << "Choose an option: ";
        std::cin >> n;
        //The chosen card is swapped with the last in the player's hand.
        std::vector<Card>::iterator v=vec.begin()+n-1;
        Card temp1;
        temp1=*v;
        *v=vec.back();
        vec.back()=temp1;
        // now check if it matches the card in the top of the opened
        if (playedCard.color==temp1.color || playedCard.number==temp1.number || temp1.color==0)
        {
            deck->insert_card(temp1);
            vec.pop_back();
            if (vec.size()==1) std::cout << "The " << name << " says UNO! " << std::endl;
            return;
        }
        std::cout << "Error: Invalid choice! Please, try again." << std::endl;
    }
}


Card * Player::check_before_playing_card(int * take2, bool * check, Deck * deck)
{
    if (*take2!=0) // This is executed when one or more "Take 2 Cards" are opened before the player's turn.
    {
        int choice;
        std::cout << "\nNow, " << name << " must draw " << (*take2)*2 << " cards. \n(1) Draw ";
        std::cout << (*take2)*2 << " cards, or (2) Play a 'Draw 2 cards' also? " << std::endl;
        std::cin >> choice;
        if (choice==1)
        {
            while (*take2>0)
            {
                draw_a_card(deck->remove_card());
                draw_a_card(deck->remove_card());
                (*take2)--;
            }
            show_cards();
        }
        else if (choice==2)
        {
            std::cout << "Which draw_2_cards do you wanna play? " << std::endl;
            // The number of "Draw 2 Cards" cards' options are presented to the player.
            std::vector<Card>::iterator it = vec.begin();
            int i=0;
            while (it!=vec.end())
            {
                if (vec[i].number==12) std::cout << "(" << i+1 << "): " << vec[i].color << "   " ;
                i++;
                it++;
            }
            std::cout << std::endl;
            std::cout << "Give an option: " ;
            std::cin >> i ;

            std::vector<Card>::iterator p1=vec.begin()+i-1;
            if (p1->number==12)
            {
                Card * temp2 = new Card;
                *temp2=vec.back();
                vec.back()=*p1;
                *p1=*temp2;

                *temp2=vec.back();
                vec.pop_back();

                *check=true;
                std::cout << "Player decides to play a \"Draw 2 cards\" also with color: " << temp2->color << std::endl;
                return temp2;
            }
        }
        return NULL;
    }
    else return NULL;
}


bool Player::freedom_of_choice(bool * check, Deck * deck, Hand ** player, int * rot)
{
    if (*check==true) return true;

    bool f=true;
    int j;
    Card temp=deck->opened.back();
    Card * n = new Card;
    n=can_pc_play(temp);
    
    while (f)
    {
        std::cout << "What do you want to do? (1) Play a card, (2) Draw a card ? ";
        std::cin >> j;
        std::cout << std::endl;

        switch (j)
        {
            case 1: 
            {
                if (n!=NULL)
                {
                    return true;
                }
                else
                {
                    std::cout << "You have no valid card to play. You draw a card.";
                    draw_a_card(deck->remove_card());
                    std::cout << "Now, your cards are the following: " << std::endl;
                    show_cards();
                    f=false;
                    break;
                }
            }                
            case 2:
            {
                draw_a_card(deck->remove_card());
                std::cout << "Now, your cards are the following: " << std::endl;
                show_cards();
                f=false;
                break;
            }
        }
    }
    std::cout << "Now, what do you want to do? (1) Play a card, (2) Pass ? ";


    std::cin >> j;
    std::cout << std::endl;
    n=can_pc_play(temp);

    switch (j)
    {
        case 1: 
        {
            if (n!=NULL)
            {
                return true;
            }
            else
            {
                std::cout << "You have no valid card to play. You pass.";
                if (*rot==1) *player=(*player)->next;
                else *player=(*player)->prev;
                return false;
            }
        }
        case 2:          // In this case, the player drew a card and still has no cards to play, so he is forced to pass.
        {
            if (*rot==1) *player=(*player)->next;
            else *player=(*player)->prev;
            return false;
        }
    }
    return true; //This line of code is only necessary to remove the compiler warning of "control reaches end of non-void function"
}


int Player::choose_what_color()
{
    std::string color;
    std::cout << "What color do you want to turn this card on? " << std::endl;
    std::cin >> color;
    while (1)
    {
        if (color=="red") return 1;
        else if (color=="green") return 2;
        else if (color=="blue") return 3;
        else if (color=="yellow") return 4;
        else std::cout << "No valid option! " << std::endl;
    }
}

Card * Player::can_pc_play(Card playedCard)
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
        // cards in the Player's hand
        return NULL;
    }
}
