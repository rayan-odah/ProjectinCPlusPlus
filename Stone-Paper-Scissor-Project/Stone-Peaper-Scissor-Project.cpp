#include <iostream>  
#include <cmath>  


using namespace std;

enum enChoice { Stone = 1, Paper = 2, Scissor = 3 };
enum enwhowin { user = 1, computer = 2, Draw = 3 };
int ReadNumbersFromUser(string Message, int from, int to)
{
    int Number = 0;

    do
    {
        cout << Message << endl;
        cin >> Number;
    } while (Number < from || Number > to);

    return Number;
}
int Randomchoice(int From, int To)
{

    int randNum = rand() % (To - From + 1) + From;
    return randNum;
}

enChoice getchoice(int choice)
{

    if (choice == 1)
        return enChoice::Stone;
    if (choice == 2)
        return enChoice::Paper;
    if (choice == 3)
        return enChoice::Scissor;

}

void getinputs(enChoice& userchoice, enChoice& computerchoice) {


    userchoice = getchoice(ReadNumbersFromUser("Your Choice :[1]:Stone, [2]:Paper, [3]:Scissor ? ", 1, 3));
    computerchoice = getchoice(Randomchoice(1, 3));

}
enwhowin computervsuser(enChoice userchoice, enChoice computerchoice) {

    if (userchoice == computerchoice)
        return enwhowin::Draw;
    else if (userchoice == enChoice::Paper && computerchoice == enChoice::Stone)
        return enwhowin::user;
    else if (userchoice == enChoice::Stone && computerchoice == enChoice::Scissor)
        return enwhowin::user;
    else if (userchoice == enChoice::Scissor && computerchoice == enChoice::Paper)
        return enwhowin::user;
    else
        return enwhowin::computer;
}
string whathechoice(int input) {
    switch (input) {
    case 1:
        return "Stone";
    case 2:
        return "Paper";
    case 3:
        return "Scissor";
    }
}


void gamedata(int gameround, int drawcounter, int Computerwincounter, int Userwincounter) {

    cout << "\t________________________________________________________________" << endl;

    cout << "\n\t\t\t" << "+++ " << "G a m e  O v e r " << " +++" << endl;
    cout << "\t________________________________________________________________" << endl;
    cout << "\n\t_________________________ [ Game Results ] _________________________" << endl;
    cout << "\n\tGame Rounds       : " << gameround << endl;
    cout << "\tPlayer won times  : " << Userwincounter << endl;
    cout << "\tComputer won times: " << Computerwincounter << endl;
    cout << "\tDraw times        : " << drawcounter << endl;

    if (Userwincounter > Computerwincounter) {
        cout << "\tFinal Winner  : " << "Player" << endl;
        system("color 2F");
    }
    else if (Userwincounter < Computerwincounter) {
        cout << "\tFinal Winner  : " << "Computer" << endl;
        system("color 4F");
        cout << "\a";
    }
    else
        system("color 6F");

    cout << "\t_________________________________________________________________" << endl;

}


void mainop() {

    int manygamerounds = ReadNumbersFromUser("How Many Rounds 1 to 10 ", 1, 10);
    enChoice userchoice;
    enChoice computerchoice;
    int drawcounter = 0, Computerwincounter = 0, Userwincounter = 0;

    for (int counter = 1; counter <= manygamerounds; counter++) {

        cout << "\nRound" << " [" << counter << "] " << "begins:" << endl;
        getinputs(userchoice, computerchoice);
        cout << "_______________" << "Round" << " [" << counter << "] " << "____________________" << endl;
        cout << "\nPlayer 1 Choice: " << whathechoice(userchoice) << endl;
        cout << "Computer Choice: " << whathechoice(computerchoice) << endl;

        switch (computervsuser(userchoice, computerchoice)) {
        case enwhowin::Draw:
            cout << "Round Winner     :" << "[" << "No Winner" << "]" << endl;
            drawcounter++;
            system("color 6F");
            break;

        case enwhowin::user:
            cout << "Round Winner     :" << "[" << "Player win" << "]" << endl;
            Userwincounter++;

            system("color 2F");
            break;
        case (enwhowin::computer):

            cout << "Round Winner     :" << "[" << "computer" << "]" << endl;
            Computerwincounter++;
            system("color 4F");
            cout << "\a";

            break;

        }

        cout << "_________________________________" << endl;


    }

    gamedata(manygamerounds, drawcounter, Computerwincounter, Userwincounter);




}


int main() {
    srand((unsigned)time(NULL));


    char PlayorNo = 'Y';
    do {

        system("cls");
        system("color 0F");

        mainop();
        cout << "\n\t\t\tdo you want play again Y/N ? ";
        cin >> PlayorNo;

    } while (PlayorNo == 'Y' || PlayorNo == 'y');


}
