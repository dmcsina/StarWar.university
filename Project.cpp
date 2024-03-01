#include <iostream>
#include <fstream>
#include <cstdlib>
#include <thread>  //for sleep hold map to user can see
#include <conio.h> //for getch function that working with keybord
#include <vector>
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
    int helth = 0;
    int damege;
    string name;
};
struct bullet
{
    int x;
    int y;
    int damege = 1;
};

void CreatMap(spaceShip *myship, spaceShip *enemyShip, bullet *myBullet, char (*map)[20][20], int gameStatus, int *level, string *error, int *score, int *x, int (*mapSize)[2]);
int Menu();
string LoadFile();
void SaveFile(spaceShip myShip, spaceShip enemyShip, int level, int score, int mapeSize[2], char map[20][20]);
void Map(char (*map)[20][20], int (*mapSize)[2]);
void CreatEnemy(int level, spaceShip *enemyShip, char (*map)[20][20], int score, int hardness, int gameStatus);
void MenuTop(int *level, spaceShip myship, spaceShip enemyship, int score);
void MenuBut(string mesesage);
bool ChangePosion(spaceShip *myship, spaceShip *enemyShip, string *error, bullet *myBullet, char (*map)[20][20], int level, vector<string> history, int (*mapSize)[2], int score);
void ChaneEnemyPosion(char (*map)[20][20], string name, int (*mapSize)[2]);
void Attack(spaceShip *myShip, spaceShip *enemyShip, bullet *myBullet, char (*map)[20][20], int (*mapSize)[2]);
bool CheckGame(spaceShip *myShip, spaceShip *enemyShip, int level);
void Prosses(string info, int *level, spaceShip *myShip, spaceShip *enemyShip, int *score, char (*map)[20][20], int (*mapsize)[2]);
bool Checkposion(int *myShipX, string *error, int (*mapSize)[2]);
void CheckLevel(int *level, spaceShip *enemyShip, char (*map)[20][20], int *score, spaceShip *myship, vector<string> *history, int hardness, int (*mapSize)[2], int gameStatus);
void Low_offHelth(spaceShip *enemyShip, char (*map)[20][20]);
spaceShip CreatMyShip(int score, int (*mapSize)[2]);
int DifficultyMenu();
void SaveGameHistory(vector<string> *history, string name);
void ShowGameHistory(vector<string> history);
void SaveFilehistory(int level, int score ,spaceShip myShip, spaceShip enemyShip);
void SizeMenu(int (*mapSize)[2]);
int Find(string line);
// void CheckShip(spaceShip *myShip);

int main()
{
#pragma region varibles
    string error = "Sina ", info;
    spaceShip myShip, enemyShip;
    bullet myBullet;
    bool flag = true;
    int level = 1;
    char map[20][20]{' '};
    int choice, score = 0;
    int x;
    int mapSize[2];
    vector<string> history(100, " ");
    int hardness = 1;
#pragma endregion
    while (true)
    {
        flag = true;
        choice = Menu();
        if (choice == 1)
        {
            SizeMenu(&mapSize);
            hardness = DifficultyMenu();
            myShip = CreatMyShip(score, &mapSize);
        }

        if (choice == 2)
        {
            // info = LoadFile();
            Prosses(info, &level, &myShip, &enemyShip, &score, &map, &mapSize);
        }
        CreatEnemy(level, &enemyShip, &map, score, hardness, choice);
        cout << "level" << level << endl
             << "XM" << myShip.x << endl
             << "helth" << myShip.helth << endl
             << "XE" << enemyShip.x << endl
             << "YE" << enemyShip.y << endl
             << "HE" << enemyShip.helth;
        while (flag)
        {
            CheckLevel(&level, &enemyShip, &map, &score, &myShip, &history, hardness, &mapSize, choice);
            CreatMap(&myShip, &enemyShip, &myBullet, &map, choice, &level, &error, &score, &x, &mapSize);
            flag = ChangePosion(&myShip, &enemyShip, &error, &myBullet, &map, level, history, &mapSize, score);
            if (flag == false)
            {
                break;
            }

            choice = 0;
            // flag = CheckGame(&myShip, &enemyShip, level);
            cout << "heeelsth" << myShip.helth;
        }
    }

    return 0;
}

int Menu()
{
    int chooise;
    system("cls");
    std::cout << Green_TEXT << "                                     ________  _________    /\\         _______ \\            /\\            /     /\\         _______    \n";
    std::cout << "                                     |             |       /  \\       |       | \\          /  \\          /     /  \\       |       |   \n";
    std::cout << "                                     |             |      /    \\      |       |  \\        /    \\        /     /    \\      |       |   \n";
    std::cout << "                                     |_______      |     /______\\     |_______|   \\      /      \\      /     /______\\     |_______|       \n";
    std::cout << "                                             |     |    /        \\    |\\           \\    /        \\    /     /        \\    |\\         \n";
    std::cout << "                                             |     |   /          \\   | \\           \\  /          \\  /     /          \\   |  \\     \n";
    std::cout << "                                      _______|     |  /            \\  |  \\           \\/            \\/     /            \\  |    \\\n";
    cout << Yellow_TEXT << "                                                                     ------------------------" << endl;
    cout << "                                                                     |  1- Start New Game    |" << endl;
    cout << "                                                                     | 2- Load The Last Game |" << endl;
    cout << "                                                                     | 0-Exit                |" << endl;
    cout << "                                                                     | Choose :              |" << endl;
    cout << "                                                                     ------------------------" << endl;
    cin >> chooise;
    system("cls");
    return chooise;
}

void SizeMenu(int (*mapSize)[2])
{
    do
    {
        system("cls");
        cout << "                                          Chose Size Map : " << endl;
        cout << "                                          Axis X: ";
        cin >> (*mapSize)[0];
        cout << endl;
        cout << "                                          Axis Y: ";
        cin >> (*mapSize)[1];

    } while ((*mapSize)[0] > 20 & (*mapSize)[1] > 20);
}

int DifficultyMenu()
{
    int hardness;
    cout << "                                                                                -------------------------------" << endl;
    cout << "                                                                                | choose difficulty of game : |" << endl;
    cout << "                                                                                | 1-Easy (Spwan One enemy)    |" << endl;
    cout << "                                                                                | 1-Hard (Spawn two enemy)    |" << endl;
    cout << "                                                                                -------------------------------" << endl;
    cin >> hardness;
    return hardness;
}

void MenuTop(int *level, spaceShip myship, spaceShip enemyship, int score)
{
    cout << Green_TEXT "                                                                          "
         << " LeveL : " << *level << "Score " << score <<"myshidame"<<myship.damege<< " Helth : " << myship.helth << " ENEMY HELTH : ";
    for (int i = 0; i < enemyship.helth; i++)
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
    cout << Yellow_TEXT "                                              for save your game and go to main Menu game press 'ESc' Button on your keybord " << endl
         << White_TEXT;
    cout << RED_TEXT << "                                                                        " << mesesage << White_TEXT;
}

void Map(char (*map)[20][20], int (*mapSize)[2])
{
    // to make a table
    for (int i = 0; i < (*mapSize)[1]; i++)
    {
        cout << "                                               ";

        for (int j = 0; j < (*mapSize)[0]; j++)
        {
            cout << Cyan_TEXT " ---";
        }
        cout << endl;
        cout << "                                               ";
        for (int k = 0; k <= (*mapSize)[0]; k++)
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
    for (int i = 0; i < (*mapSize)[0]; i++)
        cout << " ---";
    cout << endl;
}

spaceShip CreatMyShip(int score, int (*mapSize)[2])
{
    spaceShip myShip;
    if (score == 0)
    {
        srand(time(0));
        myShip.x = (rand() % 7) + 4;
        myShip.y = (*mapSize)[1] - 1;
        myShip.helth = 3;
        myShip.damege = 1;
        myShip.name = "jonior";
    }
    if (score > 15)
    {
        myShip.helth = 4;
        myShip.damege = 2;
        myShip.name = "vice captain";
        myShip.y = (*mapSize)[1] - 1;
    }
    if (score > 20)
    {
        myShip.helth = 5;
        myShip.damege = 3;
        myShip.name = "captain";
        myShip.y = (*mapSize)[1] - 1;
    }

    return myShip;
}

bool ChangePosion(spaceShip *myship, spaceShip *enemyShip, string *error, bullet *mybullet, char (*map)[20][20], int level, vector<string> history, int (*mapSize)[2], int score)
{
    *error = " ";
    char direction = _getch();
    switch (direction)
    {
    case 'd': // move right
    case 'D':
    {
        Attack(&(*myship), &(*enemyShip), &(*mybullet), &(*map), &(*mapSize));
        if (Checkposion(&((*myship).x), &(*error), &(*mapSize)))
        {
            (*myship).x += 1;
            ChaneEnemyPosion(&(*map), (*enemyShip).name, &(*mapSize));
        }
    }
    break;
    case 'a': // move left
    case 'A':
    {
        Attack(&(*myship), &(*enemyShip), &(*mybullet), &(*map), &(*mapSize));
        if (Checkposion(&((*myship).x), &(*error), &(*mapSize)))
        {
            (*myship).x -= 1;
            ChaneEnemyPosion(&(*map), (*enemyShip).name, &(*mapSize));
        }
    }
    break;

    case 'w':
    case 'W':
        Attack(&(*myship), &(*enemyShip), &(*mybullet), &(*map), &(*mapSize));
        ChaneEnemyPosion(&(*map), (*enemyShip).name, &(*mapSize));
        break;
    case 27:
        SaveFile((*myship), (*enemyShip), level, score, (*mapSize), (*map));
        system("cls");
        SaveFilehistory(level,score,(*myship),(*enemyShip));
        cout << "                                           your game is saved "<<endl;
        ShowGameHistory(history);
        for (int i = 0; i < (*mapSize)[0]; i++)
        {
            for (int j = 0; j < (*mapSize)[1]; j++)
            {
                (*map)[i][j] = ' ';
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(6000));
        return false;
        
        // exit(0);
    default: // user press wrong key
        *error = "please set your keybord to english or press correct button";
        break;
    }
    return true;
}

void Attack(spaceShip *myShip, spaceShip *enemyShip, bullet *myBullet, char (*map)[20][20], int (*mapSize)[2])
{
    bool flag = true;
    (*myBullet).x = (*myShip).x;
    (*myBullet).y = ((*mapSize)[1]) - 2;
    // while (flag == true)
    // {
    // if ((*map)[(*myBullet).y][(*myBullet).x] == '*')
    // {

    //     (*myBullet).y += 1;
    //     flag = false;
    // }
    for (int i = 0; i < ((*mapSize)[0] - 1); i++)
    {
        if ((*map)[0][i] == '^')
        {
            (*map)[0][i] = ' ';
        }
    }
    for (int i = 1; i < ((*mapSize)[1] - 1); i++)
    {
        for (int j = 1; j < ((*mapSize)[0] - 1); j++)
        {

            if ((*map)[i][j] == '^')
            {
                if ((*map)[i - 1][j] != '*')
                {
                    (*map)[i - 1][j] = '^';
                    (*map)[i][j] = ' ';
                }
                if ((*map)[i - 1][j] == '*')
                {
                    (*enemyShip).helth -= (*myShip).damege;
                }
            }
        }
    }

    (*map)[(*myBullet).y][(*myBullet).x] = '^';
    // Map(&(*map));
    // (*map)[(*myBullet).y][(*myBullet).x] = ' ';
    // (*myBullet).y -= 1;
    // std::this_thread::sleep_for(std::chrono::milliseconds(150)); // puse to user see map befor refresh
    // system("cls");
    // }
}

void CreatMap(spaceShip *myship, spaceShip *enemyShip, bullet *myBullet, char (*map)[20][20], int gameStatus, int *level, string *error, int *score, int *x, int (*mapSize)[2])
{
    system("cls");
    int xe;
    for (int i = 0; i < (*mapSize)[1]; i++)
    {
        for (int j = 0; j < (*mapSize)[0]; j++)
        {
            if ((*map)[i][j] != '*' && (*map)[i][j] != '^')
            {
                (*map)[i][j] = ' ';
            }
        }
    }

    srand(time(0)); // to make random number
    if (gameStatus == 1)
    {
        (*myship).x = (rand() % 7) + 4;
    }
    // CheckShip(&(*myship));
    if (gameStatus == 2)
    {
        // string info = LoadFile();
        // Prosses(info, &(*level), &(*myship), &(*enemyShip));
    }
    if ((*myship).name == "jonior")
    {
        (*map)[(*mapSize)[1] - 1][(*myship).x] = '#';
    }
    if ((*myship).name == "vice captain")
    {
        (*map)[(*mapSize)[1] - 1][(*myship).x] = '%';
    }
    if ((*myship).name == "captain")
    {
        (*map)[(*mapSize)[1] - 1][(*myship).x] = '$';
    }

    // (*map)[19][(*myship).x] = '#';

    MenuTop(level, (*myship),(*enemyShip), (*score));
    Map(&(*map), &(*mapSize));
    MenuBut(*error);
}

void CreatEnemy(int level, spaceShip *enemyShip, char (*map)[20][20], int score, int hardness, int gameStatus)
{
    // to make random number
    srand(time(0)); // to make random number
    int firstposion, randEnemy;
    for (int i = 0; i < hardness; i++)
    {
        if (hardness == 1)
        {
            firstposion = (rand() % 7) + 4;
        }
        if (hardness == 2)
        {
            firstposion = (rand() % ((i * 6) + 6)) + 3;
        }
        int sina = 4;
        if (score > 0)
        {
            sina = 1;
        }
        if (score > 10)
        {
            sina = 2;
        }
        if (score > 20)
        {
            sina = 3;
        }
        if (score > 30)
        {
            sina = 4;
        }
        if (gameStatus == 1 ||gameStatus == 0 )
        {
            randEnemy = (rand() % sina) + 1;
            (*enemyShip).x = firstposion;
            (*enemyShip).y = 0;
        }
        if (gameStatus == 2)
        {
            if ((*enemyShip).name == "very tiny")
            {
                randEnemy = 1;
            }
            if ((*enemyShip).name == "tiny")
            {
                randEnemy = 2;
            }
            if ((*enemyShip).name == "big")
            {
                randEnemy = 3;
            }
            if ((*enemyShip).name == "very big")
            {
                randEnemy = 4;
            }
            firstposion=(*enemyShip).x;
        }

        if (randEnemy == 1)
        {
            (*enemyShip).helth = 1;
            (*enemyShip).name = "very tiny";
        }
        if (randEnemy == 2)
        {
            // while (firstposion > 19)
            // {
            //     int firstposion = rand() % 20;
            // }
            (*enemyShip).helth = 2;
            (*enemyShip).name = "tiny";
        }
        if (randEnemy == 3)
        {
            // while (firstposion > 17 && score < 60)
            // {
            //     int firstposion = rand() % 20;
            // }
            (*enemyShip).helth = 4;
            (*enemyShip).name = "big";
        }
        if (randEnemy == 4)
        {
            // while (firstposion > 16)
            // {
            //     int firstposion = rand() % 20;
            // }
            (*enemyShip).helth = 6;
            (*enemyShip).name = "very big";
        }

        for (int i = 0; i < randEnemy; i++)
        {
            (*map)[0][firstposion + i] = '*';
            for (int j = 0; j < randEnemy; j++)
            {
                (*map)[j][firstposion + i] = '*';
            }
        }
    }
}

void ChaneEnemyPosion(char (*map)[20][20], string name, int (*mapSize)[2])
{
    int count;
    if (name == "very tiny")
    {
        count = 1;
    }
    if (name == "tiny")
    {
        count = 2;
    }
    if (name == "big")
    {
        count = 3;
    }
    if (name == "very big")
    {
        count = 4;
    }

    int counter = 0;
    for (int i = 0; i < (*mapSize)[1]; i++)
    {
        for (int j = 0; j < (*mapSize)[0]; j++)
        {
            if ((*map)[i][j] == '*')
            {
                (*map)[i][j] = ' ';
                (*map)[i + count][j] = '*';
                counter++;
            }
            if (counter == (count))
            {
                break;
            }
        }
    }
}

void Low_offEnemyHelth(spaceShip *myShip, char (*map)[20][20])
{
    for (int i = 0; i < 20; i++)
    {

        if ((*map)[18][i] = '*')
        {
        }
    }
}

bool Checkposion(int *myShipX, string *error, int (*mapSize)[2])
{
    if (*myShipX >= ((*mapSize)[0] - 1))
    {
        *myShipX -= 1;
        *error = " You Can't Go RIGHT Anymore";
        return false;
    }
    if (*myShipX <= 0)
    {
        *myShipX += 1;
        *error = " You Can't Go LEFT Anymore";

        return false;
    }
    return true;
}

void CheckLevel(int *level, spaceShip *enemyShip, char (*map)[20][20], int *score, spaceShip *myship, vector<string> *history, int hardness, int (*mapSize)[2], int gameStatus)
{
    if ((*enemyShip).helth <= 0)
    {
        // (*level)++;
        if ((*enemyShip).name == "very tiny")
        {
            *score += 2;
        }
        if ((*enemyShip).name == "tiny")
        {
            *score += 4;
        }
        if ((*enemyShip).name == "big")
        {
            *score += 6;
        }
        if ((*enemyShip).name == "very big")
        {
            *score += 8;
        }
        for (int i = 0; i < (*mapSize)[1]; i++)
        {
            for (int j = 0; j < (*mapSize)[0]; j++)
            {
                if ((*map)[i][j] == '*')
                {
                    (*map)[i][j] = ' ';
                }
            }
        }
        (*enemyShip).helth = 0;
        SaveGameHistory(&(*history), (*enemyShip).name);
        CreatEnemy(*level, &(*enemyShip), &(*map), *score, hardness, gameStatus);
    }
    if (*score > 20 &(*level)<4)
    {
        (*myship).helth = 4;
        (*myship).damege = 2;
        (*myship).name = "vice captain";
    }
    if (*score > 40& (*level)<5)
    {
        (*myship).helth = 5;
        (*myship).damege = 3;
        (*myship).name = "captain";
    }
    *level = (*score / 10) + 1;
    for (int i = 0; i < (*mapSize)[1] - 1; i++)
    {

        if ((*map)[((*mapSize)[1]) - 1][i] == '*')
        {
            for (int w = ((*mapSize)[1]) - 1; w > ((*mapSize)[1]) - 5; w--)
            {
                for (int j = ((*mapSize)[0]); j > 0; j--)
                {
                    if ((*map)[w][j] == '*')
                    {
                        (*map)[w][j] = ' ';
                    }
                }
            }

            (*myship).helth -= 1;
            CreatEnemy(*level, &(*enemyShip), &(*map), *score, hardness, gameStatus);
        }
    }
}

bool CheckGame(spaceShip *myShip, spaceShip *enemyShip, int level)
{
    system("cls");
    bool check = true;
    if ((*enemyShip).helth == 0 & level == 10000)
    {
        std::cout << "|    ||    |   ____   |      |   |  \n";
        std::cout << "|    ||    |    |     |--    |   |  \n";
        std::cout << "|    ||    |    |     |  --  |   |  \n";
        std::cout << " |  |  |  |     |     |   -- |   \n";
        std::cout << "  ||    ||     _|_    |      |   O  \n";
        check = false;
    }
    if ((*myShip).helth == 0)
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

void SaveFile(spaceShip myShip, spaceShip enemyShip, int level, int score, int mapeSize[2], char map[20][20])
{
    for (int i = 0; i < mapeSize[1]; i++)
    {
        for (int j = 0; j < mapeSize[0]; j++)
        {
            if (map[i][j] == '*')
            {
                (enemyShip).x=j; 
                (enemyShip).y=i; 
            }
        }
    }
    int count = 0;
    ofstream myFile("game.txt");
    myFile << "level:" << level << endl
           << "score:" << score << endl
           << "myshipX:" << myShip.x << endl
           << "helth:" << myShip.helth << endl
           << "myshipname:" << myShip.name << endl
           << "myshipdamege:" << myShip.damege << endl
           << "enemyhelth:" << enemyShip.helth << endl
           << "enemyshipx:" << enemyShip.x << endl
           << "enemyshipy:" << enemyShip.y << endl
           << "enemyshipname:" << enemyShip.name << endl
           << "mapx:" << mapeSize[0] << endl
           << "mapy:" << mapeSize[1] << endl;
    for (int i = 0; i < mapeSize[1]; i++)
    {
        for (int j = 0; j < mapeSize[0]; j++)
        {
            if (map[i][j] == '^')
            {
                count++;
                myFile << "bolet" << count << ":" << i << j << endl;
            }
        }
    }
}

void Prosses(string info, int *level, spaceShip *myShip, spaceShip *enemyShip, int *score, char (*map)[20][20], int (*mapsize)[2])
{
    // cout<<"level";

    int count = 0, number;
    string name;
    ifstream myFile("game.txt");
    while (getline(myFile, info))
    {

        number = Find(info);
        switch (count)
        {
        case 0:
            (*level) = number;
            break;
        case 1:
            *score = number;
            break;
        case 2:
            (*myShip).x = number;
            break;
        case 3:
            (*myShip).helth = number;
            break;
        case 4:
            if (number == 1)
            {
                (*myShip).name = "jonior";
            }
            if (number == 2)
            {
                (*myShip).name = "vice captain";
            }
            if (number == 3)
            {
                (*myShip).name = "captain";
            }

            break;
        case 5:
            (*myShip).damege = number;
            break;
        case 6:
            (*enemyShip).helth = number;
            break;
        case 7:
            (*enemyShip).x = number;
            break;
        case 8:
            (*enemyShip).y = number;
            break;
        case 9:
            if (number == 1)
            {
                (*enemyShip).name = "very tiny";
            }
            if (number == 2)
            {
                (*enemyShip).name = "tiny";
            }
            if (number == 3)
            {
                (*enemyShip).name = "big";
            }
            if (number == 4)
            {
                (*enemyShip).name = "very big";
            }
            break;
        case 10:
            (*mapsize)[0] = number;
        case 11:
            (*mapsize)[1] = number;
            break;
        default:
            break;
        }
        count++;
    }
    // count = 0;
    // while (getline(myFile, info, ':'))
    // {
    //     getline(myFile, info);

    //     count++;
    //     if (count > 9)
    //     {
    //         if (info.size() == 3)
    //         {
    //             number = stoi(info);
    //             (*map)[number / 100][number % 100] = '^';
    //         }
    //     }
    // }
}

void SaveGameHistory(vector<string> *history, string name)
{
    (*history).push_back(name);
}

void ShowGameHistory(vector<string> history)
{
    int count[4]{0};
    for (int i = 0; i < history.size(); i++)
    {
        if (history[i] == "very tiny")
        {
            count[0]++;
        }
        else if (history[i] == "tiny")
        {
            count[1]++;
        }
        else if (history[i] == "big")
        {
            count[2]++;
        }
        else if (history[i] == "very big")
        {
            count[3]++;
        }
    }
    int total = count[0] + count[1] + count[2] + count[3];
    cout << "                           "
         << " Game History :" << endl;
    cout << "                           "
         << " you Destory => "
         << " very tiny" << count[0] << " tiny " << count[1] << " big " << count[2] << "very big" << count[3] << endl;
    cout << "                           "
         << " total distory Enemy :" << total << endl;
}

void SaveFilehistory(int level, int score,spaceShip myShip, spaceShip enemyShip)
{
    string info;
    int lineCount = 1;
    ifstream myFile("gamehistory.txt");
    while (getline(myFile, info))
    {
        lineCount++;
    }
    // string lins[lineCount];
    // int i=0;
    // while (getline(myFile, info))
    // {
    //     lins[i]=info;
    //     i++;
    // }
    // lins[i+1]="game"+lineCoun+" LeveL :"+level+" Score :"<<score<<"Heal"<<heal;
    if (lineCount>1)
    {
        lineCount--;
    }
    
    myFile.close();
    ofstream historyFile("gamehistory.txt", std::ios::app);
    historyFile << endl
                << " game : " << lineCount << " LeveL :" << level << " Score :" << score << "My Ship Heal " << myShip.helth<<"My Ship Name"<<myShip.name<<"enemyship helth"<<enemyShip.helth << endl;
}

string LoadFile()
{
    string info;
    ifstream gameText("game.txt");
    getline(gameText, info);
    return (info);
}

int Find(string line)
{
    string afterColon;
    size_t colonPos = line.find(':'); // پیدا کردن موقعیت اولین کاراکتر ':'

    if (colonPos != std::string::npos)
    {                                           // اگر کاراکتر ':' یافت شد
        afterColon = line.substr(colonPos + 1); // استخراج بخش بعد از کاراکتر ':'
    }
    cout << afterColon;
    if (afterColon == "jonior")
    {
        return 1;
    }
    if (afterColon == "vice captain")
    {
        return 2;
    }
    if (afterColon == "captain")
    {
        return 3;
    }
    if (afterColon == "very tiny")
    {
        return 1;
    }
    if (afterColon == "tiny")
    {
        return 2;
    }
    if (afterColon == "big")
    {
        return 3;
    }
    if (afterColon == "very big")
    {
        return 4;
    }

    int number = stoi(afterColon);
    // int number;
    return number;
}