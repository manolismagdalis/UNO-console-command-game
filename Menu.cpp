#include "Menu.h"

void Menu::processMenu(){

    int nMenuChoice = 0;

    std::cout << "--- Welcome to the UNO Game! ---\n\n";

    // Keep the program running until they choose to exit
    while (nMenuChoice != 4) {
        std::cout << "---Main Menu---\n";
        std::cout << "1. Start Game\n";
        std::cout << "2. Rules\n";
        std::cout << "3. Set Players\n";
        std::cout << "4. Quit\n";
        std::cout << "\nPick a choice: ";
        std::cin >> nMenuChoice;
        // Switch based on user input
        switch (nMenuChoice)
        {

            // Case of starting the game play
        case 1:
        {
            Game a_game;
            a_game.initiate_game();
            break;
        }

            // Case of UNO Rules
        case 2:
        {
            std::cout << "--- HOW TO PLAY UNO ---" << std::endl;
            std::cout << "Rules:" << std::endl
                << "1. Play a card by entering the number on the left of the card." << std::endl
                << "2. A card can only be played if the color, the number or the title of the card is same as the card on the pile." << std::endl
                << "3. Draw a card if you cannot play any card, or you want to have more cards just fun." << std::endl
                << "4. There are some special cards (action cards):" << std::endl
                << "\nSkip: In game name \"Lose_Turn\".\nWhen you play this card the next player will be skipped for this round." << std::endl
                << "\nReverse: In game name \"Change_Turns\".\nWhen you play this card you reverse the order of the players "<< std::endl
                << "(for example if it was 1->2->3->4->1, after this card it will be 1->4->3->2->1)." << std::endl
                << "\nDraw Two: In game name \"Draw_2_Cards\".\nWhen you play this card the next player has to draw 2 cards from the draw pile."<< std::endl
                << "Exception: if the next player has a \"Draw_2_Cards\" card he/she can play it instead of drawing 2 cards," << std::endl
                << "this will make the next player of him/her draw 4 cards (if the next player has a \"Draw_2_Cards\" card too he/she can"  << std::endl
                << "play it instead of drawing 2 cards, this will make the next player of him draw 6 cards etc)." << std::endl
                << "\nWild: In game name \"ChClr\".\nThis card can be placed on any card." << std::endl
                << "When you play this card you have to state which color it will represent for the next player."<< std::endl
                << "You must write the color you want (red, green, blue or yellow)."<< std::endl
                << "\nWild Draw Four: In game name \"+4\".\nThis card acts like \"ChClr\" except that the next player also has to draw four cards."<< std::endl << std::endl;
            break;
        }
            // Case of Setting Players and Computer Players
        case 3:
        {
            int players_number, computers_number;
            std::cout <<"You can select a game with 2 to 4 players (some or all of them could be computer players).\nWrite the number of the players you want to take part in this game.\n";
            bool z;
            bool k;
            z=false;
            k=false;

            while (z=true)
            {
                std::cin >> players_number;
                if (players_number>=2 && players_number<=4)
                {
                    std::cout<<"How many of these players you want to be computer players? (Write the number)\n";
                    while (k=true)
                    {
                       std::cin>> computers_number;
                        if (computers_number<=players_number)
                        {
                            k=true;
                            break;
                        }
                        else
                        {
                            std::cout<<"Invalid number of players. Please choose a number of computer players between 0 and "<<players_number<<"\n";
                        }
                    }
                    z=true;
                    break;
                }
                else
                {
                    std::cout<<"Invalid number of players. Please choose a number of players between 2 and 4.\n";
                }

            }
            break;
        }

            // Quit condition
        case 4:
        {
            break;
        }

            // Invalid selection
        default:
        {
            std::cout << "Invalid Menu Choice!\n";
            break;
        }
        }
    }
};
