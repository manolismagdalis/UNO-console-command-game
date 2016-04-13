#include "Game.h"

void Game::initiate_game()
{
    while (winner==NULL)
    {
        Card temp = deck.opened.back();

        std::cout << "The following card is open:     ";

        show_the_card(temp.number, temp.color);

        std::cout << "______________________________________________________________________________" << std::endl;

        std::cout << "\nNow it's " << current_player->name << "'s turn!" << std::endl;
        // This if statement can be removed in order to inspect the cards of the rest of the players.
        if (current_player->name=="Player 1")
        {
            current_player->show_cards();
            Hand * n = current_player->next;
            Hand * p = current_player->prev;
            std::cout << n->name << "(next player) has " << n->vec.size() << " cards. " << std::endl;
            std::cout << "\n" << p->name << "(previous player) has " << p->vec.size() << " cards. " << std::endl;
        }
        std::cout << "\nThe deck size is the following: " << deck.vec.size() << std::endl;
        std::cout << std::endl;

        Card * point=new Card;
        // point is null if a "Take 2 Cards" is not played by the previous player or when the player
        // finished drawing cards from the deck. Else, it returns the new "Take 2 Cards" that the
        // player has played on top of a same card.
        point=current_player->check_before_playing_card(&take2cards, &check, &deck);

        // freedom_of_choice returns true when the player decides whether he is going
        // to draw or play or if he already threw a "Take 2 Cards" on top of the previous one.
        // It returns false when the player decides to pass.
        if (current_player->freedom_of_choice(&check, &deck, &current_player, &rotation))
        {
            if (point==NULL) // This means that there are no previous obligations from "Take 2 Cards".
            {
                current_player->play_a_card(deck.opened.back(), &deck);
            }
            else
            {                               // This is executed when the player has thrown a "Take 2 Cards"
                deck.insert_card(*point);  // in which case, it is inserted in the opened pile of the deck
            }
            check=false; // Return the check boolean to its default value, false.
                        //True means the player has played and cannot play one more card.

            if (current_player->vec.empty())
            {
                winner=current_player;
            }
            current_player->check_played_card(&deck, &rotation, &current_player, &take2cards);
        }
    }
    std::cout << "The winner is " << winner->name << "! Congratulations!" << std::endl;
    std::cout << "\n\n Thank you for playing! " << std::endl;
    return;
}
