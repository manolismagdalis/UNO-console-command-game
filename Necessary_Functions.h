#ifndef NECESSARY_FUNCTIONS_H
#define NECESSARY_FUNCTIONS_H

using namespace std;

int myrandom (int i)
{
    int k=rand() % i;
    return k;
}

void show_the_card(int number, int color)
{
    cout << "|_";
    switch (number)
    {
        case 10: cout << "Lose_Turn";
            break;
        case 11: cout << "Change_Turns";
            break;
        case 12:
            {
                cout << "Draw_2_Cards";
                //take2cards++;
            }
            break;
        case 13: cout << "ChClr";
            break;
        case 14: cout << "+4";
            break;
        case 50: cout << "__";
            break;
        default: cout << number;
            break;
    }
    switch (color)
    {
        case 0: cout << "_|    ";
            break;
        case 1: cout << "_red_|    " ;
            break;
        case 2: cout << "_green_|    " ;
            break;
        case 3: cout << "_blue_|    " ;
            break;
        case 4: cout << "_yellow_|    " ;
            break;
    }

    cout << endl;
    return;
}

#endif // NECESSARY_FUNCTIONS_H
