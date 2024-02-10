#include <iostream>

using namespace std;

void CreatMap(int *shipX, int *shipY, int (*map)[20][20]);
int Menu();

struct spaceShip
{
    int x;
    int y;
    int helth;
};

int main()
{

#pragma region varibles
    string error = " ";
    spaceShip myShip;
    int map[20][20]{};
    int choice;
#pragma endregion
    choice = Menu();
    CreatMap(&myShip.x, &myShip.y, &map);
    return 0;
}

int Menu()
{
    int chooise;
    std::cout << "                               ________  _________    /\\         _______ \\            /\\            /     /\\         _______    \n";
    std::cout << "                               |             |       /  \\       |       | \\          /  \\          /     /  \\       |       |   \n";
    std::cout << "                               |             |      /    \\      |       |  \\        /    \\        /     /    \\      |       |   \n";
    std::cout << "                               |_______      |     /______\\     |_______|   \\      /      \\      /     /______\\     |_______|       \n";
    std::cout << "                                       |     |    /        \\    |\\           \\    /        \\    /     /        \\    |\\         \n";
    std::cout << "                                       |     |   /          \\   | \\           \\  /          \\  /     /          \\   |  \\     \n";
    std::cout << "                                _______|     |  /            \\  |  \\           \\/            \\/     /            \\  |    \\\n";
    cout << "                                                                      1- Start New Game" << endl;
    cout << "                                                                      2- Load The Last Game" << endl;
    cout << "                                                                      0-exit" << endl;
    cout << "                                                                      Choose : ";
    cin >> chooise;
    return chooise;
}

void CreatMap(int *shipX, int *shipY, int (*map)[20][20])
{
    // #pragma region varible
    //     srand(time(0)); // to make random number

    //     int x; // to hold the position of user
    //     int y; // to hold the position of user
    //     int ship[2];
    // #pragma endregion
    //     // to give a value to indexes of array
    //     for (int i = 0; i < 10; i++)
    //     {

    //         for (int j = 0; j < 10; j++)
    //             *map[i][j] = ' ';
    //     }
    //     if (*shipY == -1)
    //     {
    //         // to create  spaceships randomly
    //         for (int i = 0; i <= 10; i++)
    //         {

    //             int x = rand() % 10;
    //             int y = rand() % 10;

    //             if (*map[x][y] == ' ')
    //             {
    //                 if (i < 10)
    //                 {
    //                     *map[x][y] = '*';
    //                     enemySpaceshipPosision[0][i] = x;
    //                     enemySpaceshipPosision[1][i] = y;
    //                 }
    //                 else if (i == 10)
    //                 {
    //                     spaceship[x][y] = '#';
    //                     *shipX = x;
    //                     *shipY = y;
    //                     x1 = x;
    //                     y1 = y;
    //                 }
    //             }
    //             else
    //                 i--; // to restart the process
    //         }
    //     }
    //     else
    //     {

    //         for (int i = 0; i < 10; i++)
    //         {
    //             x = enemySpaceshipPosision[0][i];
    //             y = enemySpaceshipPosision[1][i];
    //             if (x == -1 && y == -1)
    //             {

    //                 spaceship[x][y] = ' ';
    //             }
    //             else
    //                 spaceship[x][y] = '*';
    //         }
    //         x = *shipX;
    //         y = *shipY;
    //         spaceship[x][y] = '#';
    //         if (boolet[0] >= 0 && boolet[1] >= 0)
    //         {
    //             spaceship[boolet[0]][boolet[1]] = '-';
    //         }
    //     }
    // to make a table
    for (int i = 0; i < 20; i++)
    {
        cout << "                                               ";

        for (int j = 0; j < 20; j++)
        {
            cout << " ---";
        }
        cout << endl;
        cout << "                                               ";
        for (int k = 0; k <= 20; k++)
        {
            if (k == 20)
                cout << "|";
            else
            {
                cout << "|" << ' ' << ' ' << ' ';
            }
        }

        cout << endl;
    }
    cout << "                                               ";
    for (int i = 0; i < 20; i++)
        cout << " ---";
}
