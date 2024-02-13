#include <iostream>
#include <fstream>
#include <cstdlib>
#include <thread>  //for sleep hold map to user can see
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
    int helth = 3;
};
struct bullet
{
    int x;
    int y;
    int damege = 1;
};

void CreatMap(spaceShip *myship, spaceShip *enemyShip, bullet *myBullet, char (*map)[20][20], int gameStatus, int *level);
int Menu();
string LoadFile();
void SaveFile(spaceShip myShip, spaceShip enemyShip, int level);
void Map(char (*map)[20][20]);
void CreatEnemy(int level, spaceShip *enemyShip, char (*map)[20][20]);
void MenuTop(int *level, int helth, int enemyHelth);
void MenuBut(string mesesage);
void ChangePosion(spaceShip *myship, spaceShip *enemyShip, string *error, bullet *myBullet, char (*map)[20][20], int level);
void Attack(spaceShip *myShip, spaceShip *enemyShip, bullet *myBullet, char (*map)[20][20]);
bool CheckGame(spaceShip *myShip, spaceShip *enemyShip);
void Prosses(string info, int *level, spaceShip *myShip, spaceShip *enemyShip);

int main()
{

#pragma region varibles
    string error = " ", info;
    spaceShip myShip, enemyShip;
    bullet myBullet;
    bool flag = true;
    int level = 4;
    char map[20][20]{' '};
    int choice;
#pragma endregion

    choice = Menu();
    if (choice == 2)
    {
        info = LoadFile();
        Prosses(info, &level, &myShip, &enemyShip);
    }
    CreatEnemy(level, &enemyShip, &map);
    // cout<<"level"<<level<<endl<<"XM"<<myShip.x<<endl<<"helth"<<myShip.helth<<endl<<"XE"<<enemyShip.x<<endl<<"YE"<<enemyShip.y<<endl<<"HE"<<enemyShip.helth;
    while (flag)
    {
        CreatMap(&myShip, &enemyShip, &myBullet, &map, choice, &level);
        ChangePosion(&myShip, &enemyShip, &error, &myBullet, &map, level);
        choice = 0;
        flag = CheckGame(&myShip, &enemyShip);
        cout << "heeelsth" << enemyShip.y;
    }

    return 0;
}

int Menu()
{
    int chooise;

    std::cout << Green_TEXT << "                               ________  _________    /\\         _______ \\            /\\            /     /\\         _______    \n";
    std::cout << "                           |             |       /  \\       |       | \\          /  \\          /     /  \\       |       |   \n";
    std::cout << "                           |             |      /    \\      |       |  \\        /    \\        /     /    \\      |       |   \n";
    std::cout << "                           |_______      |     /______\\     |_______|   \\      /      \\      /     /______\\     |_______|       \n";
    std::cout << "                                   |     |    /        \\    |\\           \\    /        \\    /     /        \\    |\\         \n";
    std::cout << "                                   |     |   /          \\   | \\           \\  /          \\  /     /          \\   |  \\     \n";
    std::cout << "                            _______|     |  /            \\  |  \\           \\/            \\/     /            \\  |    \\\n";
    cout << Yellow_TEXT << "                                                                      1- Start New Game" << endl;
    cout << "                                                                      2- Load The Last Game" << endl;
    cout << "                                                                      0-exit" << endl;
    cout << "                                                                      Choose : ";
    cin >> chooise;
    system("cls");
    return chooise;
}

void MenuTop(int *level, int helth, int enemyHelth)
{
    cout << Green_TEXT "                                                                          "
         << " LeveL : " << *level << " Helth : " << helth << " ENEMY HELTH : ";
    for (int i = 0; i < enemyHelth; i++)
    {
        cout << "-";
    }

    cout << endl
         << White_TEXT;
}

void MenuBut(string mesesage)
{
    cout << Yellow_TEXT "                                              for move your Ship use RightArrow (->) & LeftArrow(<-) for Attack use UperArrow (|) " << endl
         << White_TEXT;
    cout << Yellow_TEXT "                                              for save your game and exit game press 'ESc' Button on your keybord " << endl
         << White_TEXT;
    cout << mesesage;
}

void Map(char (*map)[20][20])
{
    // to make a table
    for (int i = 0; i < 20; i++)
    {
        cout << "                                               ";

        for (int j = 0; j < 20; j++)
        {
            cout << Cyan_TEXT " ---";
        }
        cout << endl;
        cout << "                                               ";
        for (int k = 0; k <= 20; k++)
        {
            if (k == 20)
                cout << "|";
            else
            {
                cout << "|" << ' ' << Magenta_TEXT << (*map)[i][k] << Cyan_TEXT << ' ';
            }
        }

        cout << endl;
    }
    cout << "                                               ";
    for (int i = 0; i < 20; i++)
        cout << " ---";
    cout << endl;
}

void ChangePosion(spaceShip *myship, spaceShip *enemyShip, string *error, bullet *mybullet, char (*map)[20][20], int level)
{
    char direction = _getch();
    switch (direction)
    {
    case 'd': // move right
    case 'D':
        (*myship).x = (*myship).x + 1;
        (*enemyShip).y = (*enemyShip).y + 1;
        break;
    case 'a': // move left
    case 'A':
        (*myship).x = (*myship).x - 1;
        (*enemyShip).y += 1;
        break;
    case 'w':
    case 'W':
        Attack(&(*myship), &(*enemyShip), &(*mybullet), &(*map));
        break;
    case 27:
        SaveFile((*myship), (*enemyShip), level);
        exit(0);
    default: // user press wrong key
        *error = "please set your keybord to english or press correct button";
        break;
    }
}

void Attack(spaceShip *myShip, spaceShip *enemyShip, bullet *myBullet, char (*map)[20][20])
{
    bool flag = true;
    (*myBullet).x = (*myShip).x;
    (*myBullet).y = 18;
    while (flag == true)
    {
        if ((*map)[(*myBullet).y][(*myBullet).x] == '*')
        {
            (*enemyShip).helth -= 1;
            (*myBullet).y += 1;
            flag = false;
        }
        (*map)[(*myBullet).y][(*myBullet).x] = '^';
        Map(&(*map));
        (*map)[(*myBullet).y][(*myBullet).x] = ' ';
        (*myBullet).y -= 1;
        std::this_thread::sleep_for(std::chrono::milliseconds(150)); // puse to user see map befor refresh
        system("cls");
    }
}

void CreatMap(spaceShip *myship, spaceShip *enemyShip, bullet *myBullet, char (*map)[20][20], int gameStatus, int *level)
{
    system("cls");
    int xe;
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            if ((*map)[i][j] != '*')
            {
                (*map)[i][j] = ' ';
            }
        }
    }

    srand(time(0)); // to make random number
    if (gameStatus == 1)
    {
        (*myship).x = rand() % 20;
    }
    if (gameStatus == 2)
    {
        string info = LoadFile();
        Prosses(info, &(*level), &(*myship), &(*enemyShip));
    }

    (*map)[19][(*myship).x] = '#';

    MenuTop(level, (*myship).helth, (*enemyShip).helth);

    Map(&(*map));
    MenuBut(" ");
}

void CreatEnemy(int level, spaceShip *enemyShip, char (*map)[20][20])
{
    // to make random number
    srand(time(0)); // to make random number
    int firstposion = rand() % 20;

    if (level == 1)
    {
        (*enemyShip).helth = 1;
    }
    if (level == 2)
    {
        while (firstposion > 19)
        {
            int firstposion = rand() % 20;
        }
        (*enemyShip).helth = 2;
    }
    if (level == 3)
    {
        while (firstposion > 17)
        {
            int firstposion = rand() % 20;
        }
        (*enemyShip).helth = 4;
    }
    if (level == 4)
    {
        while (firstposion > 16)
        {
            int firstposion = rand() % 20;
        }
        (*enemyShip).helth = 6;
    }
    (*enemyShip).x = firstposion;
    (*enemyShip).y = 0;
    for (int i = 0; i < level; i++)
    {
        (*map)[0][firstposion + i] = '*';
        for (int j = 0; j < level; j++)
        {
            (*map)[j][firstposion + i] = '*';
        }
    }
}

bool CheckGame(spaceShip *myShip, spaceShip *enemyShip)
{
    system("cls");
    bool check = true;
    if ((*enemyShip).helth == 0)
    {
        std::cout << "|    ||    |   ____   |      |   |  \n";
        std::cout << "|    ||    |    |     |--    |   |  \n";
        std::cout << "|    ||    |    |     |  --  |   |  \n";
        std::cout << " |  |  |  |     |     |   -- |   \n";
        std::cout << "  ||    ||     _|_    |      |   O  \n";
        check = false;
    }
    if ((*myShip).helth == 0 || (*enemyShip).y > 19)
    {
        cout << "  _____    _____    __      __    ____   ____             ____   ____  \n";
        cout << " |        |     |  | __    __ |  |      |    |  |     |  |      |    | \n";
        cout << " |   ___  |_____|  |  __  __  |  |___   |    |   |   |   |____  |____|  \n";
        cout << " |     |  |     |  |    __    |  |      |    |    | |    |      |     | \n";
        cout << " |_____|  |     |  |          |  |____  |____|     -     |____  |      | \n";
        check = false;
    }
    return check;
}

void SaveFile(spaceShip myShip, spaceShip enemyShip, int level)
{
    string info;
    int number = level;
    number = number * 100;
    number = myShip.x + number;
    number = number * 10;
    number += myShip.helth;
    number = number * 100;
    number += enemyShip.x;
    number = number * 100;
    number += enemyShip.y;
    number = number * 10;
    number += enemyShip.helth;
    info = to_string(number);
    ofstream myFile("game.txt");
    myFile << info;
}

void Prosses(string info, int *level, spaceShip *myShip, spaceShip *enemyShip)
{
    int number;
    *level = (info[0]) - '0';
    number = info[1] - '0';
    number = (number * 10) + (info[2] - '0');
    (*myShip).x = number;
    (*myShip).helth = info[3] - '0';
    number = info[4] - '0';
    number = (number * 10) + (info[5] - '0');
    (*enemyShip).x = number;
    number = info[6] - '0';
    number = (number * 10) + (info[7] - '0');
    (*enemyShip).y = number;
    (*enemyShip).helth = info[8] - '0';
}

void ChaneEnemyPosion(spaceShip *enemyShip ,char (*map)[20][20],int level)
{
    for (int i = 0; i < level; i++)
    {
        (*map)[(*enemyShip).x][(*enemyShip).y + i] = '*';
        for (int j = 0; j < level; j++)
        {
            (*map)[(*enemyShip).x][(*enemyShip).y + i] = '*';
        }
    }
}

string LoadFile()
{
    string info;
    ifstream gameText("game.txt");
    getline(gameText, info);
    return (info);
}