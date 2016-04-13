#ifndef GAME_H
#define GAME_H

#include "Computer.h"
#include "Player.h"

// The extern keyword is used because this function is defined in Necessary_Functions.h
extern void show_the_card(int, int);

/* This class organizes players and performs the necessary procedures for the game */
class Game
{
    public:
        friend void show_the_card(Card temp);
        Deck deck;
        Player player1;
        Computer player2;
        Computer player3;
        // The following is declared as a pointer to an object of class Hand, so it can be
        // freely transformed either in pointer of a Player class object or a Computer class object.
        Hand * current_player;
        Hand * winner;
        bool check; // This boolean is used to check if a player has played.
        int take2cards;
        int rotation;     // 0 for left, 1 for right

        // Inside the constructor, the players are linked to each other, the deck is shuffled and each player
        // draws 7 cards from the deck. Finally, one card is drawn from the deck is placed in the opened pile
        // of the deck.
        Game()
        {
            std::cout << std::endl;
            std::cout << "___________________________________________________________________" << std::endl;
            std::cout << "|                                                                  |" << std::endl;
            std::cout << "|                    Welcome to a game of UNO!                     |" << std::endl;
            std::cout << "|        Now each player draws 7 cards from the closed deck.       |" << std::endl;
            std::cout << "|______________________shuffling the deck._________________________|" << std::endl;
            std::cout << "\n\n\n";
            deck.shuffle_the_deck();
            deck.open_one_card();
            player1.name="Player 1" ;
            player2.name="Computer 2" ;
            player3.name="Computer 3" ;
            take2cards=0;
            current_player = &player1;
            player1.next=&player2;
            player1.prev=&player3;
            player2.next=&player3;
            player2.prev=&player1;
            player3.next=&player1;
            player3.prev=&player2;
            winner=NULL;
            check=false;

            for (int i=0; i<7; i++)
            {
                player1.draw_a_card(deck.remove_card());
                player2.draw_a_card(deck.remove_card());
                player3.draw_a_card(deck.remove_card());
            }
            rotation=1;
            //This is executed when the first card is "Draw 2 Cards" in which case, the first player takes 2 cards
            //or has the right to also play a "Draw 2 Cards" if he has one.
            if (deck.opened.back().number==12)
            {
                take2cards=1;
            }
        }
        void initiate_game();
};

#endif // GAME_H
