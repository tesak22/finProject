#include <iostream>
#include <ctime>
#include <windows.h>
#include <conio.h>
#include <string>

using namespace std;

int width = 3;
int height = 3;
int health = 3;
bool centP = 0;
int* arWidth = new int[width];
int* arHeight = new int[height];
int plToWin = 0;
int pl = 0;

class Point
{

    bool showP; // 0 - not known, 1 - known
    bool goodP; // 0 - not good, 1 - good
    bool choise;

public:
    Point(bool g) : goodP(g) {
        showP = 0; //0
        choise = 0;
    }

    Point() {
        showP = 0;
        goodP = 0;
        choise = 0;
    }

    void klicInfo()
    {
        if (showP == 1)
        {
            return;
        }
        showP = 1;
        if (goodP == 1)
        { 
            pl++;
            return;
        }
        health--;
        return;
    }

    void klicInfoF()
    {
        if (showP == 1)
        {
            return;
        }
        showP = 1;
        if (goodP == 1)
        {
            health--;
            return; 
        }
        return;
    }

    char info()
    {
        if (showP == 1 && choise != 1)
        {
            if (goodP == 1)
            {
                return '@';
            }

            return '*';
        }
        if (choise == 1)
        {
            return ' ';
        }
        return '0';
    }

    void setChoiseT()
    {
        choise = 1;
    }
    void setChoiseF()
    {
        choise = 0;
    }

    char getGood() const
    {
        if (goodP == 1)
        {
            return '@';
        }
        return '*';
    }
};

Point** point = new Point * [width];

void clear() {
    COORD topLeft = { 0, 0 };
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen;
    DWORD written;

    GetConsoleScreenBufferInfo(console, &screen);
    FillConsoleOutputCharacterA(
        console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
    );
    FillConsoleOutputAttribute(
        console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
        screen.dwSize.X * screen.dwSize.Y, topLeft, &written
    );
    SetConsoleCursorPosition(console, topLeft);
}

void startProj()
{
    for (int i = 0; i < width; i++)
    {
        point[i] = new Point[height];
    }
    for (int i = 0; i < width; i++)
    {
        arWidth[i] = 0;
        arHeight[i] = 0;
    }
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            int a = rand() % 2;
            point[i][j] = a;
            if (a == 1)
            {
                plToWin++;
            }
        }
    }
}

void getP()
{
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            if (point[i][j].getGood() == '@')
            {
                arWidth[i]++;
            }
            else
            {
                for (int z = j; z >= 0; z--)
                {
                    if (point[i][z].getGood() == '*')
                    {
                        if (arWidth[i] % 10 == 0)
                        {
                            break;
                        }
                        arWidth[i] *= 10;
                        break;
                    }
                }
            }
        }
        if (arWidth[i] % 10 == 0)
        {
            arWidth[i] /= 10;
        }
    }

    for (int j = 0; j < width; j++)
    {
        for (int i = 0; i < height; i++)
        {
            if (point[i][j].getGood() == '@')
            {
                arHeight[j]++;
            }
            else
            {
                for (int z = i; z >= 0; z--)
                {
                    if (point[i][z].getGood() == '*')
                    {
                        if (arHeight[j] % 10 == 0)
                        {
                            break;
                        }
                        arHeight[j] *= 10;
                        break;
                    }
                }
            }
        }
        if (arHeight[j] % 10 == 0)
        {
            arHeight[j] /= 10;
        }
    }
}

void showGame()
{
    int** arr = new int* [width];
    for (int i = 0; i < width; i++)
    {
        arr[i] = new int[width];
        for (int j = 0; j < width; j++)
        {
            arr[i][j] = 0;
        }
    }
    for (int i = 0; i < width; i++)
    {

        int num = arHeight[i];
        int sum = 1;
        int a = 10;
        int j = 0;

        while (num / a != 0)
        {
            sum++;
            a *= 10;
        }

        while (sum != 0)
        {
            a /= 10;
            arr[i][j] = num / a;

            num %= a;
            j++;
            sum--;
        }

    }

    int max = 0;
    for (int i = 0; i < width; i++)
    {
        int toMax = 1;
        int a = 10;
        int num = arWidth[i];
        while (num / a != 0)
        {
            toMax++;
            a *= 10;
        }
        if (toMax > max)
        {
            max = toMax;
        }
    }

    string spase = "";
    for (int i = 0; i < max + 3; i++)
    {
        spase += " ";
    }

    cout << endl;
    for (int i = 0; i < width; i++)
    {
        bool a = 0;
        cout << spase;
        for (int j = 0; j < width; j++)
        {
            if (arr[j][i] != 0)
            {
                a = 1;
                cout << arr[j][i] << " ";
            }
            else
            {
                cout << "  ";
            }
        }
        if (a == 1)
        {
            cout << endl;
        }
        a = 0;
    }

    cout << endl << spase;
    for (int i = 0; i < (width * 2); i++)
    {
        cout << "-";
    }
    cout << endl;

    for (int i = 0; i < height; i++)
    {
        string s = "";
        int toMax = 0;
        int a = 10;
        int num = arWidth[i];
        while (num / a != 0)
        {
            toMax++;
            a *= 10;
        }
        if (toMax < max)
        {
            int sum = max - toMax;
            for (int i = 0; i < sum; i++)
            {
                s += " ";
            }
        }
        cout << " " << num << s << "|";
        for (int j = 0; j < width; j++)
        {
            cout << point[i][j].info() << " ";
        }
        cout << endl;
    }
}

void Buttons()
{
    int w = 0;
    int h = 0;
    int a = 0;
    point[h][w].setChoiseT();

    while (a == 0)
    {
        cout << "      health: " << health << endl;
        showGame();
        point[h][w].setChoiseF();
        if (health <= 0 || pl == plToWin)
        {
            clear();
            break;
        }
        switch (_getch())
        {
        case 'w':
            if (h != 0)
            {
                h -= 1;
                point[h][w].setChoiseT();
            }
            break;
        case 'd':
            if (w != width - 1)
            {
                w += 1;
                point[h][w].setChoiseT();
            }
            break;
        case 's':
            if (h != height - 1)
            {
                h += 1;
                point[h][w].setChoiseT();
            }
            break;
        case 'a':
            if (w != 0)
            {
                w -= 1;
                point[h][w].setChoiseT();
            }
            break;
        case 'e':
            point[h][w].klicInfo();
            break;
        case 'q':
            point[h][w].klicInfoF();
            break;
        case 'r':
            point[h][w].setChoiseF();
            a = 1;
            break;
        default:
            break;
        }
        
        clear();
    }
}

void main()
{
    srand(time(NULL));
    while (true)
    {
        health = 3;
        clear();
        startProj();
        getP();
        Buttons();
        showGame();
        cout << endl;
        if (health != 0)
        {
            int a;
            cout << "YOU WIN" << endl << "try again(0 - no, 1 - yes)" << endl;;
            cin >> a;
            if (a == 0)
            {
                break;
            }
            height += 5;
            width += 5;
        }
        else
        {
            int a;
            cout << "YOU LOSE" << endl << "try again(0 - no, 1 - yes)" << endl;
            cin >> a;
            if (a == 0)
            {
                break;
            }
            if (height != 5)
            {
                height -= 5;
                width -= 5;
            }
        }
    }
}




