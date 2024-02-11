#include <iostream>
#include <fstream>
#include <cstdlib>
#include <conio.h> //for getch function that working with keybord
#define RED_TEXT "\033[1;31m"
#define Green_TEXT "\033[0;32m"
#define Yellow_TEXT "\033[0;33m"
#define White_TEXT "\033[0;37m"
#define Magenta_TEXT "\033[0;35m"
#define Cyan_TEXT "\033[0;36m"


using namespace std;

struct spaceShip
{
    int x;
    int y;
    int helth=3;
};
void CreatMap(spaceShip *myship, char (*map)[20][20], int gameStatus, int *level);
int Menu();
int LoadFile();
void CreatEnemy(int level, char (*map)[20][20]);
void MenuTop(int *level, int helth);
void MenuBut(string mesesage);
void ChangePosion(spaceShip *myship,string *error);

int main()
{

#pragma region varibles
    string error = " ";
    spaceShip myShip;
    int level;
    char map[20][20]{' '};
    int choice;
#pragma endregion
    level = LoadFile();
    choice = Menu();
    while (true)
    {
    CreatMap(&myShip, &map, choice, &level);
    ChangePosion(&myShip,&error);
     choice=0;   
    }
    
    return 0;
}

int Menu()
{
    int chooise;
    
    std::cout <<Green_TEXT<<"                               ________  _________    /\\         _______ \\            /\\            /     /\\         _______    \n";
    std::cout << "                               |             |       /  \\       |       | \\          /  \\          /     /  \\       |       |   \n";
    std::cout << "                               |             |      /    \\      |       |  \\        /    \\        /     /    \\      |       |   \n";
    std::cout << "                               |_______      |     /______\\     |_______|   \\      /      \\      /     /______\\     |_______|       \n";
    std::cout << "                                       |     |    /        \\    |\\           \\    /        \\    /     /        \\    |\\         \n";
    std::cout << "                                       |     |   /          \\   | \\           \\  /          \\  /     /          \\   |  \\     \n";
    std::cout << "                                _______|     |  /            \\  |  \\           \\/            \\/     /            \\  |    \\\n";
    cout <<Yellow_TEXT<< "                                                                      1- Start New Game" << endl;
    cout << "                                                                      2- Load The Last Game" << endl;
    cout << "                                                                      0-exit" << endl;
    cout << "                                                                      Choose : ";
    cin >> chooise;
    system("cls");
    return chooise;
}

void MenuTop(int *level, int helth)
{
    cout<<Green_TEXT"                                                                          "<<" LeveL : "<<*level <<" Helth : "<<helth<<endl<<White_TEXT;

}

void MenuBut(string mesesage)
{
    cout<<Yellow_TEXT"                                              for move your Ship use RightArrow (->) & LeftArrow(<-) for Attack use UperArrow (|) "<<endl<<White_TEXT;
    cout<<mesesage;
}

void ChangePosion(spaceShip *myship,string *error)
{
    char direction = _getch();
    switch (direction)
    {
    case 'd': // move right
    case 'D':
        (*myship).x = (*myship).x + 1;
        break;
    case 'a': // move left
    case 'A':
        (*myship).x = (*myship).x - 1;
        break;
    default: // user press wrong key
        *error = "please set your keybord to english or press correct button";
        break;
    }
}

void CreatMap(spaceShip *myship, char (*map)[20][20], int gameStatus, int *level)
{
    system("cls");
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            (*map)[i][j] = ' ';
        }
    }
    srand(time(0)); // to make random number
    if (gameStatus == 1)
    {
        (*myship).x = rand() % 20;
    }
    (*map)[19][(*myship).x] = '#';
    CreatEnemy(*level, &(*map));
    MenuTop(level,myship->helth);
    // to make a table
    for (int i = 0; i < 20; i++)
    {
        cout << "                                               ";

        for (int j = 0; j < 20; j++)
        {
            cout <<Cyan_TEXT " ---";
        }
        cout << endl;
        cout << "                                               ";
        for (int k = 0; k <= 20; k++)
        {
            if (k == 20)
                cout << "|";
            else
            {
                cout << "|" << ' ' <<Magenta_TEXT<< (*map)[i][k]<<Cyan_TEXT << ' ';
            }
        }

        cout << endl;
    }
    cout << "                                               ";
    for (int i = 0; i < 20; i++)
        cout << " ---";
    cout<<endl;
    MenuBut(" ");
}

void CreatEnemy(int level, char (*map)[20][20])
{
    // to make random number
    int firstposion = rand() % 20;
    if (level == 1)
    {
        (*map)[0][firstposion] = '*';
    }
}

int LoadFile()
{
    string level;
    ifstream gameText("game.txt");
    getline(gameText, level);
    return stoi(level);
}