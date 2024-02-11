#include <iostream>
#include <fstream>
#include <cstdlib>
#include <thread> //for sleep hold map to user can see
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
struct bullet
{
    int x;
    int y;
    int damege=1;
};

void CreatMap(spaceShip *myship,spaceShip *enemyShip,bullet *myBullet, char (*map)[20][20], int gameStatus, int *level);
int Menu();
int LoadFile();
void Map(char (*map)[20][20]);
void CreatEnemy(int level, spaceShip *enemyShip);
void MenuTop(int *level, int helth);
void MenuBut(string mesesage);
void ChangePosion(spaceShip *myship,string *error,bullet *myBullet,char (*map)[20][20]);
void Attack(spaceShip *myShip,bullet *myBullet,char (*map)[20][20]);

int main()
{

#pragma region varibles
    string error = " ";
    spaceShip myShip,enemyShip;
    bullet myBullet;
    int level;
    char map[20][20]{' '};
    int choice;
#pragma endregion
    level = LoadFile();
    choice = Menu();
    CreatEnemy(level,&enemyShip);
    while (true)
    {
    CreatMap(&myShip,&enemyShip,&myBullet, &map, choice, &level);
    ChangePosion(&myShip,&error,&myBullet,&map);
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

void Map(char (*map)[20][20])
{
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
}

void ChangePosion(spaceShip *myship,string *error,bullet *mybullet,char (*map)[20][20])
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
    case 'w':
    case 'W':
        Attack(&(*myship),&(*mybullet),&(*map));
    default: // user press wrong key
        *error = "please set your keybord to english or press correct button";
        break;
    }
}

void Attack(spaceShip *myShip,bullet *myBullet,char (*map)[20][20])
{
    (*myBullet).x=(*myShip).x;
    (*myBullet).y=18;
    while((*myBullet).y>=0)
    {
        (*map)[(*myBullet).y][(*myBullet).x]='^';
        Map(&(*map));
        (*map)[(*myBullet).y][(*myBullet).x]=' ';
        (*myBullet).y-=1;
        std::this_thread::sleep_for(std::chrono::milliseconds(400)); // puse to user see map befor refresh
        system("cls");
    }
}

void CreatMap(spaceShip *myship,spaceShip *enemyShip,bullet *myBullet, char (*map)[20][20], int gameStatus, int *level)
{
    system("cls");
    int xe;
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
    (*map)[0][(*enemyShip).x]='*';
    
    MenuTop(level,myship->helth);
    Map(&(*map));
    MenuBut(" ");
}

void CreatEnemy(int level, spaceShip *enemyShip)
{
    // to make random number
    int firstposion = rand() % 20;
    if (level == 1)
    {
        (*enemyShip).x=firstposion;
        (*enemyShip).helth=1;
    }
}

int LoadFile()
{
    string level;
    ifstream gameText("game.txt");
    getline(gameText, level);
    return stoi(level);
}