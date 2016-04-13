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
    while (f)
    {
        std::cout << "What do you want to do? (1) Play a card, (2) Draw a card ? ";
        std::cin >> j;
        std::cout << std::endl;

        switch (j)
        {
            case 1: return true;
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


    switch (j)
    {
        case 1: return true;
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
