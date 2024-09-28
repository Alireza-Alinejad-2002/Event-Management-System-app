//--------------------------------------- Header Files ---------------------------------------
#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <fstream>
using namespace std;
//--------------------------------------- Definition of Global Items ---------------------------------------
struct time
{
    int year;
    int month;
    int day;
    int hour;
    int minute;
};
struct recordstory
{

    char title[30];
    char place[25];
    char note[800];
    struct time tim;
};
struct incomes
{
    char explain[30];
    int in;
    int sum;
    int quantity;
};
struct expenses
{
    char explain[30];
    int ex;
    int sum;
    int quantity;
};
struct recordmethod
{
    struct incomes inc[100];
    struct expenses exp[100];
    struct time tim[2];
};
string X;
int metcount = 0, stcount = 0, position = 25;
struct recordstory rec[128];
struct recordmethod met[128];
//--------------------------------------- gotoxy function ---------------------------------------
void gotoxy(int x, int y)
{
    COORD pos;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    if (INVALID_HANDLE_VALUE != hConsole)
    {
        pos.X = x;
        pos.Y = y;

        SetConsoleCursorPosition(hConsole, pos);
    }
}
//--------------------------------------- Save To Files ---------------------------------------
void Save(void)
{
    FILE *frecstory, *frecmethod, *fpassword, *fstcount, *fmetcount;
    int sizex = (X.size());
    //----------------------------- To save story  -----------------------------
    frecstory = fopen("record_story.dat", "wb");
    if (frecstory)
    {
        fwrite(rec, sizeof(rec), 1, frecstory);
        fclose(frecstory);
    }
    //----------------------------- To save method  -----------------------------
    frecmethod = fopen("record_method.dat", "wb");
    if (frecmethod)
    {
        fwrite(met, sizeof(met), 1, frecmethod);
        fclose(frecmethod);
    }
    //----------------------------- To save password  -----------------------------
    ofstream output("password.txt", ios::out | ios::binary);
    output.write(reinterpret_cast<char *>(&sizex), sizeof(int));
    output.write(X.c_str(), sizex);
    X = "";
    sizex = 0;
    output.flush();
    output.close();
    //----------------------------- To save stcount  -----------------------------
    fstcount = fopen("story_count.txt", "w");
    if (fstcount)
    {
        putw(stcount, fstcount);
        fclose(fstcount);
    }
    //----------------------------- To save metcount  -----------------------------
    fmetcount = fopen("method_count.txt", "w");
    if (fmetcount)
    {
        putw(metcount, fmetcount);
        fclose(fmetcount);
    }
}
//--------------------------------------- Load From Files ---------------------------------------
void Load(void)
{
    FILE *frecstory, *frecmethod, *fpassword, *fstcount, *fmetcount;
    char *temp;
    int sizex = (X.size());
    //----------------------------- To load story  -----------------------------
    frecstory = fopen("record_story.dat", "rb");
    if (frecstory)
    {
        fread(rec, sizeof(rec), 1, frecstory);
        fclose(frecstory);
    }
    //----------------------------- To load method  -----------------------------
    frecmethod = fopen("record_method.dat", "rb");
    if (frecmethod)
    {
        fread(met, sizeof(met), 1, frecmethod);
        fclose(frecmethod);
    }
    //----------------------------- To load password -----------------------------
    ifstream input("password.txt", ios::in | ios::binary);
    input.read(reinterpret_cast<char *>(&sizex), sizeof(int));
    temp = new char[sizex];
    input.read(temp, sizex);
    X.assign(temp, sizex);
    //----------------------------- To load stcount  -----------------------------
    fstcount = fopen("story_count.txt", "r");
    if (fstcount)
    {
        stcount = getw(fstcount);
        fclose(fstcount);
    }
    //----------------------------- To load metcount  -----------------------------
    fmetcount = fopen("method_count.txt", "r");
    if (fmetcount)
    {
        metcount = getw(fmetcount);
        fclose(fmetcount);
    }
}
//--------------------------------------- Login ---------------------------------------
int login()
{
    string pass = "";
    char ch;
    gotoxy(position + 15, 3);
    cout << ":::    NOTEBOOK   :::";
    gotoxy(position + 17, 8);
    cout << "Enter Password:";
    ch = getch();
    while (ch != 13)
    { // character 13 is "Enter" (ASCII CODE)
        pass.push_back(ch);
        cout << '*';
        ch = getch();
    }
    if (pass == X)
    {
        gotoxy(position + 17, 15);
        cout << "Access Granted";
        gotoxy(position + 10, 16);
        system("PAUSE");
        system("CLS");
        int main();
    }
    else
    {
        system("CLS");
        login();
    }
    return 0;
}
//--------------------------------------- Add Story ---------------------------------------
void addstory(void)
{
    system("CLS");
    int i;
    for (i = 5; i < 200; i++)
    {
        gotoxy(i, 5);
        cout << "#";
    }
    gotoxy(5, 2);
    cout << "Title :  ";
    gotoxy(5, 3);
    cout << "Time :       /    /       (  :  )";
    gotoxy(5, 4);
    cout << "Place : ";
    getchar();
    gotoxy(13, 2);
    gets(rec[stcount].title);
    gotoxy(13, 3);
    cin >> rec[stcount].tim.year;
    gotoxy(20, 3);
    cin >> rec[stcount].tim.month;
    gotoxy(25, 3);
    cin >> rec[stcount].tim.day;
    gotoxy(32, 3);
    cin >> rec[stcount].tim.hour;
    gotoxy(35, 3);
    cin >> rec[stcount].tim.minute;
    getchar();
    gotoxy(13, 4);
    gets(rec[stcount].place);
    gotoxy(position + 84, 40);
    cout << "(press 'Enter' to exit)";
    gotoxy(0, 7);
    gets(rec[stcount].note);
    stcount++;
}
//--------------------------------------- Add Method ---------------------------------------
void addmethod(void)
{
    system("CLS");
    int i, j, max;
    met[metcount].inc->sum = 0;
    met[metcount].exp->sum = 0;
    gotoxy(position, 20);
    cout << "How many Incomes do yo want to add ?!  ";
    cin >> met[metcount].inc->in;
    gotoxy(position, 23);
    cout << "How many expenses do yo want to add ?!  ";
    cin >> met[metcount].exp->ex;
    system("CLS");
    for (i = 5; i < position + 120; i++)
    {
        gotoxy(i, 4);
        cout << "#";
    }
    gotoxy(position + 3, 2);
    cout << "From      /    /     to       /    /    ";
    gotoxy(position - 34, 6);
    cout << "<< Incomes >>";
    gotoxy(position + 64, 6);
    cout << "<< Expenses >>";
    for (i = 5; i < position + 120; i++)
    {
        gotoxy(i, 8);
        cout << "#";
    }
    // Horizental separator line under the Row, Quntity ($) & Explanation
    for (i = 5; i < position + 120; i++)
    {
        gotoxy(i, 10);
        cout << "_";
    }
    // Incomes subsets
    gotoxy(6, 9);
    cout << "Row";
    gotoxy(12, 9);
    cout << "Quntity ($)";
    gotoxy(48, 9);
    cout << "Explanation";
    for (j = 1; j <= 2 * (met[metcount].inc->in) + 2; j++)
    {
        if (j <= met[metcount].inc->in)
        {
            gotoxy(6, 2 * j + 9);
            cout << j;
        }
        if (j % 2 == 0 && j > 3)
        {
            for (i = 5; i < position + 18; i++)
            {
                gotoxy(i, j + 8);
                cout << "-";
            }
        }
        gotoxy(10, j + 8);
        cout << "|";
        gotoxy(24, j + 8);
        cout << "|";
    }
    // Expenses subsets
    gotoxy(position + 21, 9);
    cout << "Row";
    gotoxy(position + 27, 9);
    cout << "Quntity ($)";
    gotoxy(position + 66, 9);
    cout << "Explanation";
    for (j = 1; j <= 2 * (met[metcount].exp->ex) + 2; j++)
    {
        if (j <= met[metcount].exp->ex)
        {
            gotoxy(position + 21, 2 * j + 9);
            cout << j;
        }
        if (j % 2 == 0 && j > 3)
        {
            for (i = position + 20; i < position + 120; i++)
            {
                gotoxy(i, j + 8);
                cout << "-";
            }
        }
        gotoxy(position + 25, j + 8);
        cout << "|";
        gotoxy(position + 39, j + 8);
        cout << "|";
    }
    // max in, ex
    max = ((met[metcount].inc->in) > (met[metcount].exp->ex) ? (met[metcount].inc->in) : (met[metcount].exp->ex));
    // main Vertical separator line
    for (j = 5; j < 2 * max + 16; j++)
    {
        gotoxy(position + 18, j);
        cout << "##";
    }
    // ................ Inputs ................
    getchar();
    // get time
    i = 0;
    for (i = 0; i < 2; i++)
    {
        gotoxy((position + 8) + 20 * i, 2);
        cin >> met[metcount].tim[i].year;
        gotoxy((position + 15) + 20 * i, 2);
        cin >> met[metcount].tim[i].month;
        gotoxy((position + 20) + 20 * i, 2);
        cin >> met[metcount].tim[i].day;
    }
    // get incomes
    i = 0;
    for (i = 0; i < met[metcount].inc->in; i++)
    {
        gotoxy(12, 2 * i + 11);
        cin >> met[metcount].inc[i].quantity;
        getchar();
        gotoxy(26, 2 * i + 11);
        gets(met[metcount].inc[i].explain);
    }
    // get expenses
    i = 0;
    for (i = 0; i < met[metcount].exp->ex; i++)
    {
        gotoxy(position + 27, 2 * i + 11);
        cin >> met[metcount].exp[i].quantity;
        getchar();
        gotoxy(position + 41, 2 * i + 11);
        gets(met[metcount].exp[i].explain);
    }
    // sum table
    i = 0;
    for (i = 0; i < met[metcount].inc->in; i++)
    {
        met[metcount].inc->sum += (met[metcount].inc[i].quantity);
    }
    i = 0;
    for (i = 0; i < met[metcount].exp->ex; i++)
    {
        met[metcount].exp->sum += (met[metcount].exp[i].quantity);
    }
    i = 5;
    for (i = 5; i < position + 120; i++)
    {
        gotoxy(i, 2 * max + 12);
        cout << "_";
        gotoxy(i, 2 * max + 13);
        cout << "-";
    }
    gotoxy(0, 2 * max + 14);
    cout << "SUM =>";
    gotoxy(position + 13, 2 * max + 18);
    cout << "NEST EGG = ";
    gotoxy(12, 2 * max + 14);
    cout << met[metcount].inc->sum;
    gotoxy(position + 27, 2 * max + 14);
    cout << met[metcount].exp->sum;
    gotoxy(position + 24, 2 * max + 18);
    cout << ((met[metcount].inc->sum) - (met[metcount].exp->sum));
    getch();
    metcount++;
}
//--------------------------------------- Input Data (Add Record) ---------------------------------------
void addrecord(void)
{
    int x;
    system("CLS");
    gotoxy(position, 7);
    cout << "###################################################";
    gotoxy(position, 8);
    cout << "##   1 -> Add a new story                        ##";
    gotoxy(position, 9);
    cout << "##   2 -> Add a new method                       ##";
    gotoxy(position, 10);
    cout << "###################################################";
    gotoxy(position, 11);
    cout << "##   Select Item (1 or 2) :                      ##";
    gotoxy(position, 12);
    cout << "###################################################";
    gotoxy(position + 30, 11);
    cin >> x;
    switch (x)
    {
    case 1:
        addstory();
        break;
    case 2:
        addmethod();
        break;
    default:
        gotoxy(position + 12, 22);
        cout << "YOU ENTERED WRONG CHOICE";
        gotoxy(position + 12, 23);
        system("PAUSE");
        break;
    }
}
//--------------------------------------- View records (Sort) ---------------------------------------
void viewrecord(void)
{
    int x, i, j, a, tempm, date[128];
    char temp[30];
    system("CLS");
    gotoxy(position, 7);
    cout << "###################################################";
    gotoxy(position, 8);
    cout << "##   1 -> Sort story by title                    ##";
    gotoxy(position, 9);
    cout << "##   2 -> Sort method by date                    ##";
    gotoxy(position, 10);
    cout << "###################################################";
    gotoxy(position, 11);
    cout << "##   Select Item (1 or 2) :                      ##";
    gotoxy(position, 12);
    cout << "###################################################";
    gotoxy(position + 30, 11);
    cin >> x;
    switch (x)
    {
    case 1:
        system("CLS");
        // Bubble sort for titles
        for (i = stcount - 1; i > 0; i--)
        {
            for (j = 0; j < i; j++)
            {
                a = strcmp(rec[j].title, rec[j + 1].title);
                if (a > 0)
                {
                    strcpy(temp, rec[j].title);
                    strcpy(rec[j].title, rec[j + 1].title);
                    strcpy(rec[j + 1].title, temp);
                }
            }
        }
        gotoxy(position, 2);
        cout << "<< Stories sorted by title name >>";
        for (i = 0; i < stcount; i++)
        {
            gotoxy(position + 2, i + 4);
            cout << i + 1 << " -> " << rec[i].title;
        }
        getch();
        break;

    case 2:
        system("CLS");
        // transforming dates to the single number for comparison
        for (i = 0; i < metcount; i++)
            date[i] = (met[i].tim[0].year * 365) + (met[i].tim[0].month * 30) + (met[i].tim[0].day);
        // Bubble sort for date of methods
        for (i = metcount - 1; i > 0; i--)
        {
            for (j = 0; j < i; j++)
            {
                if (date[j] > date[j + 1])
                {
                    tempm = date[j];
                    date[j] = date[j + 1];
                    date[j + 1] = tempm;
                }
            }
        }
        // Tabulate
        gotoxy(position, 2);
        cout << "<< Methods sorted by initial date >>";
        i = 41;
        for (i = 41; i < 156; i++)
        {
            gotoxy(i, 4);
            cout << "#";
        }
        gotoxy(position - 39, 5);
        cout << "Row";
        gotoxy(position - 23, 5);
        cout << "Date";
        gotoxy(position - 30, 7);
        cout << "From";
        gotoxy(position - 15, 7);
        cout << "To";
        gotoxy(position - 6, 5);
        cout << "Number of incomes";
        gotoxy(position + 14, 5);
        cout << "Number of expenses";
        gotoxy(position + 44, 5);
        cout << "Sum ($)";
        gotoxy(position + 35, 7);
        cout << "Incomes sum";
        gotoxy(position + 49, 7);
        cout << "Expenses sum";
        gotoxy(position + 64, 5);
        cout << "Nest egg ($)";
        j = 1;
        i = position - 39;
        for (j = 1; j <= 2 * metcount + 3; j++)
        {
            if (j <= metcount)
            {
                gotoxy(position - 38, 2 * j + 7);
                cout << j;
            }
            if (j % 2 == 0)
            {
                for (i = position - 39; i < position + 80; i++)
                {
                    gotoxy(i, j + 4);
                    cout << "-";
                }
                if (j > 2)
                {
                    gotoxy(position - 21, j + 4);
                    cout << "|";
                    gotoxy(position + 47, j + 4);
                    cout << "|";
                }
            }
            if (j < 2 * metcount + 3)
            {
                gotoxy(position - 21, j + 5);
                cout << "|";
                gotoxy(position + 47, j + 5);
                cout << "|";
            }
            gotoxy(position - 35, j + 4);
            cout << "|";
            gotoxy(position - 8, j + 4);
            cout << "|";
            gotoxy(position + 12, j + 4);
            cout << "|";
            gotoxy(position + 33, j + 4);
            cout << "|";
            gotoxy(position + 62, j + 4);
            cout << "|";
        }
        gotoxy(position - 39, 7);
        cout << "***";
        gotoxy(position - 6, 7);
        cout << "*****************";
        gotoxy(position + 14, 7);
        cout << "******************";
        gotoxy(position + 64, 7);
        cout << "************";
        // Fill in
        i = 0;
        for (i = 0; i < metcount; i++)
        {
            gotoxy(position - 33, 2 * i + 9);
            cout << met[i].tim[0].year << "/" << met[i].tim[0].month << "/" << met[i].tim[0].day;
            gotoxy(position - 19, 2 * i + 9);
            cout << met[i].tim[1].year << "/" << met[i].tim[1].month << "/" << met[i].tim[1].day;
            gotoxy(position + 2, 2 * i + 9);
            cout << met[i].inc->in;
            gotoxy(position + 22, 2 * i + 9);
            cout << met[i].exp->ex;
            gotoxy(position + 35, 2 * i + 9);
            cout << met[i].inc->sum;
            gotoxy(position + 49, 2 * i + 9);
            cout << met[i].exp->sum;
            gotoxy(position + 64, 2 * i + 9);
            cout << ((met[i].inc->sum) - (met[i].exp->sum));
        }
        getch();
        break;
    default:
        gotoxy(position + 12, 22);
        cout << "YOU ENTERED WRONG CHOICE";
        gotoxy(position + 12, 23);
        system("PAUSE");
        break;
    }
}
//--------------------------------------- Search data ---------------------------------------
void searchdata(void)
{
    int x, i, j, k, y, m, d, max, tmpdate, date[128];
    char stitle[30];
    system("CLS");
    gotoxy(position, 7);
    cout << "###################################################";
    gotoxy(position, 8);
    cout << "##   1 -> Search story by title                  ##";
    gotoxy(position, 9);
    cout << "##   2 -> Search method by date                  ##";
    gotoxy(position, 10);
    cout << "###################################################";
    gotoxy(position, 11);
    cout << "##   Select Item (1 or 2) :                      ##";
    gotoxy(position, 12);
    cout << "###################################################";
    gotoxy(position + 30, 11);
    cin >> x;
    switch (x)
    {
    case 1:
        system("CLS");
        getchar();
        gotoxy(position, 15);
        cout << "Search your story by title :   ";
        gotoxy(position + 31, 15);
        gets(stitle);
        for (i = 0; i < stcount; i++)
        {
            if (strcmp(rec[i].title, stitle) == 0)
            {
                system("CLS");
                for (j = 5; j < position + 120; j++)
                {
                    gotoxy(j, 5);
                    cout << "#";
                }
                gotoxy(5, 2);
                cout << "Title :  ";
                gotoxy(5, 3);
                cout << "Time :       /    /       (  :  )";
                gotoxy(5, 4);
                cout << "Place : ";
                // ................ Fill in ................
                gotoxy(13, 2);
                puts(rec[i].title);
                gotoxy(13, 3);
                cout << rec[i].tim.year;
                gotoxy(20, 3);
                cout << rec[i].tim.month;
                gotoxy(25, 3);
                cout << rec[i].tim.day;
                gotoxy(32, 3);
                cout << rec[i].tim.hour;
                gotoxy(35, 3);
                cout << rec[i].tim.minute;
                gotoxy(position + 84, 40);
                cout << "(press 'Enter' to exit)";
                gotoxy(13, 4);
                puts(rec[i].place);
                gotoxy(0, 7);
                puts(rec[i].note);
                getch();
                break;
            }
            if (i == stcount - 1)
            {
                system("CLS");
                gotoxy(position, 15);
                cout << ">>> This title is not exist <<<";
                getch();
            }
        }
        break;
    case 2:
        system("CLS");
        gotoxy(position - 8, 15);
        cout << "Search your method by initial date (yyyy/mm/dd) :   ";
        gotoxy(position + 45, 15);
        cout << "     /    /    ";
        gotoxy(position + 45, 15);
        cin >> y;
        gotoxy(position + 52, 15);
        cin >> m;
        gotoxy(position + 57, 15);
        cin >> d;
        tmpdate = (y * 365) + (m * 30) + (d);
        system("CLS");
        for (i = 0; i < metcount; i++)
        {
            date[i] = (met[i].tim[0].year * 365) + (met[i].tim[0].month * 30) + (met[i].tim[0].day);
            if (tmpdate == date[i])
            {
                for (j = 5; j < position + 120; j++)
                {
                    gotoxy(j, 4);
                    cout << "#";
                }
                gotoxy(position + 3, 2);
                cout << "From      /    /     to       /    /    ";
                gotoxy(position - 34, 6);
                cout << "<< Incomes >>";
                gotoxy(position + 64, 6);
                cout << "<< Expenses >>";
                j = 5;
                for (j = 5; j < position + 120; j++)
                {
                    gotoxy(j, 8);
                    cout << "#";
                }
                // Horizental separator line under the Row, Quntity ($) & Explanation
                j = 5;
                for (j = 5; j < position + 120; j++)
                {
                    gotoxy(j, 10);
                    cout << "_";
                }
                // Incomes subsets
                gotoxy(6, 9);
                cout << "Row";
                gotoxy(12, 9);
                cout << "Quntity ($)";
                gotoxy(48, 9);
                cout << "Explanation";
                for (k = 1; k <= 2 * (met[i].inc->in) + 2; k++)
                {
                    if (k <= met[i].inc->in)
                    {
                        gotoxy(6, 2 * k + 9);
                        cout << k;
                    }
                    if (k % 2 == 0 && k > 3)
                    {
                        j = 5;
                        for (j = 5; j < 98; j++)
                        {
                            gotoxy(j, k + 8);
                            cout << "-";
                        }
                    }
                    gotoxy(10, k + 8);
                    cout << "|";
                    gotoxy(24, k + 8);
                    cout << "|";
                }
                // Expenses subsets
                gotoxy(position + 21, 9);
                cout << "Row";
                gotoxy(position + 27, 9);
                cout << "Quntity ($)";
                gotoxy(position + 66, 9);
                cout << "Explanation";
                k = 1;
                for (k = 1; k <= 2 * (met[i].exp->ex) + 2; k++)
                {
                    if (k <= met[i].exp->ex)
                    {
                        gotoxy(position + 21, 2 * k + 9);
                        cout << k;
                    }
                    if (k % 2 == 0 && k > 3)
                    {
                        j = position + 20;
                        for (j = position + 20; j < position + 120; j++)
                        {
                            gotoxy(j, k + 8);
                            cout << "-";
                        }
                    }
                    gotoxy(position + 25, k + 8);
                    cout << "|";
                    gotoxy(position + 39, k + 8);
                    cout << "|";
                }
                // max in, ex
                max = ((met[i].inc->in) > (met[i].exp->ex) ? (met[i].inc->in) : (met[i].exp->ex));
                // main Vertical separator line
                j = 5;
                for (j = 5; j < 2 * max + 16; j++)
                {
                    gotoxy(position + 18, j);
                    cout << "##";
                }
                // ................ Fill in ................
                // put time
                j = 0;
                for (j = 0; j < 2; j++)
                {
                    gotoxy((position + 8) + 20 * j, 2);
                    cout << met[i].tim[j].year;
                    gotoxy((position + 15) + 20 * j, 2);
                    cout << met[i].tim[j].month;
                    gotoxy((position + 20) + 20 * j, 2);
                    cout << met[i].tim[j].day;
                }
                // put incomes
                j = 0;
                for (j = 0; j < met[i].inc->in; j++)
                {
                    gotoxy(12, 2 * j + 11);
                    cout << met[i].inc[j].quantity;
                    gotoxy(26, 2 * j + 11);
                    puts(met[i].inc[j].explain);
                }
                // put expenses
                j = 0;
                for (j = 0; j < met[i].exp->ex; j++)
                {
                    gotoxy(position + 27, 2 * j + 11);
                    cout << met[i].exp[j].quantity;
                    gotoxy(position + 41, 2 * j + 11);
                    puts(met[i].exp[j].explain);
                }
                // sum table
                j = 5;
                for (j = 5; j < position + 120; j++)
                {
                    gotoxy(j, 2 * max + 12);
                    cout << "_";
                    gotoxy(j, 2 * max + 13);
                    cout << "-";
                }
                gotoxy(0, 2 * max + 14);
                cout << "SUM =>";
                gotoxy(position + 13, 2 * max + 18);
                cout << "NEST EGG = ";
                gotoxy(12, 2 * max + 14);
                cout << met[i].inc->sum;
                gotoxy(position + 27, 2 * max + 14);
                cout << met[i].exp->sum;
                gotoxy(position + 24, 2 * max + 18);
                cout << ((met[i].inc->sum) - (met[i].exp->sum));
                getch();
                break;
            }
            if (i == metcount - 1)
            {
                system("CLS");
                gotoxy(position, 15);
                cout << ">>> This date is not exist <<<";
                getch();
            }
        }
        break;
    default:
        gotoxy(position + 12, 22);
        cout << "YOU ENTERED WRONG CHOICE";
        gotoxy(position + 12, 23);
        system("PAUSE");
        break;
    }
}
//--------------------------------------- Edit records ---------------------------------------
void editrecord(void)
{
    int x, i, j, k, y, m, d, max, tmpdate, date[128], it;
    char stitle[30];
    system("CLS");
    gotoxy(position, 7);
    cout << "###################################################";
    gotoxy(position, 8);
    cout << "##   1 -> Search story by title to edit          ##";
    gotoxy(position, 9);
    cout << "##   2 -> Search method by date to edit          ##";
    gotoxy(position, 10);
    cout << "###################################################";
    gotoxy(position, 11);
    cout << "##   Select Item (1 or 2) :                      ##";
    gotoxy(position, 12);
    cout << "###################################################";
    gotoxy(position + 30, 11);
    cin >> x;
    switch (x)
    {
    case 1:
        system("CLS");
        getchar();
        gotoxy(position, 15);
        cout << "Search your story by title to edit :   ";
        gotoxy(position + 40, 15);
        gets(stitle);
        for (i = 0; i < stcount; i++)
        {
            if (strcmp(rec[i].title, stitle) == 0)
            {
                system("CLS");
                gotoxy(position, 3);
                cout << "##############################################";
                gotoxy(position, 4);
                cout << "##            << Editing Menu >>            ##";
                gotoxy(position, 5);
                cout << "##############################################";
                gotoxy(position, 6);
                cout << "##   1 -> TITLE                             ##";
                gotoxy(position, 7);
                cout << "##   2 -> TIME                              ##";
                gotoxy(position, 8);
                cout << "##   3 -> PLACE                             ##";
                gotoxy(position, 9);
                cout << "##   4 -> NOTE                              ##";
                gotoxy(position, 10);
                cout << "##   5 -> WHOLE STORY                       ##";
                gotoxy(position, 11);
                cout << "##############################################";
                gotoxy(position, 12);
                cout << "##   Select Item (1 to 5) :                 ##";
                gotoxy(position, 13);
                cout << "##############################################";
                gotoxy(position + 30, 12);
                cin >> it;
                system("CLS");
                for (j = 5; j < position + 120; j++)
                {
                    gotoxy(j, 5);
                    cout << "#";
                }
                gotoxy(5, 2);
                cout << "Title :  ";
                gotoxy(5, 3);
                cout << "Time :       /    /       (  :  )";
                gotoxy(5, 4);
                cout << "Place : ";
                switch (it)
                {
                case 1:
                    // ................ Fill in ................
                    gotoxy(13, 3);
                    cout << rec[i].tim.year;
                    gotoxy(20, 3);
                    cout << rec[i].tim.month;
                    gotoxy(25, 3);
                    cout << rec[i].tim.day;
                    gotoxy(32, 3);
                    cout << rec[i].tim.hour;
                    gotoxy(35, 3);
                    cout << rec[i].tim.minute;
                    gotoxy(13, 4);
                    puts(rec[i].place);
                    gotoxy(position + 84, 40);
                    cout << "(press 'Enter' to exit)";
                    gotoxy(0, 7);
                    puts(rec[i].note);
                    // get new title
                    getchar();
                    gotoxy(13, 2);
                    gets(rec[i].title);
                    getch();
                    break;
                case 2:
                    // ................ Fill in ................
                    gotoxy(13, 2);
                    puts(rec[i].title);
                    gotoxy(13, 4);
                    puts(rec[i].place);
                    gotoxy(position + 84, 40);
                    cout << "(press 'Enter' to exit)";
                    gotoxy(0, 7);
                    puts(rec[i].note);
                    // get new time
                    gotoxy(13, 3);
                    cin >> rec[i].tim.year;
                    gotoxy(20, 3);
                    cin >> rec[i].tim.month;
                    gotoxy(25, 3);
                    cin >> rec[i].tim.day;
                    gotoxy(32, 3);
                    cin >> rec[i].tim.hour;
                    gotoxy(35, 3);
                    cin >> rec[i].tim.minute;
                    getch();
                    break;
                case 3:
                    // ................ Fill in ................
                    gotoxy(13, 2);
                    puts(rec[i].title);
                    gotoxy(13, 3);
                    cout << rec[i].tim.year;
                    gotoxy(20, 3);
                    cout << rec[i].tim.month;
                    gotoxy(25, 3);
                    cout << rec[i].tim.day;
                    gotoxy(32, 3);
                    cout << rec[i].tim.hour;
                    gotoxy(35, 3);
                    cout << rec[i].tim.minute;
                    gotoxy(position + 84, 40);
                    cout << "(press 'Enter' to exit)";
                    gotoxy(0, 7);
                    puts(rec[i].note);
                    // get new place
                    getchar();
                    gotoxy(13, 4);
                    gets(rec[i].place);
                    getch();
                    break;
                case 4:
                    // ................ Fill in ................
                    gotoxy(13, 2);
                    puts(rec[i].title);
                    gotoxy(13, 3);
                    cout << rec[i].tim.year;
                    gotoxy(20, 3);
                    cout << rec[i].tim.month;
                    gotoxy(25, 3);
                    cout << rec[i].tim.day;
                    gotoxy(32, 3);
                    cout << rec[i].tim.hour;
                    gotoxy(35, 3);
                    cout << rec[i].tim.minute;
                    gotoxy(13, 4);
                    puts(rec[i].place);
                    gotoxy(position + 84, 40);
                    cout << "(press 'Enter' to exit)";
                    // get new note
                    getchar();
                    gotoxy(0, 7);
                    gets(rec[i].note);
                    getch();
                    break;
                case 5:
                    // get a new story :)
                    getchar();
                    gotoxy(13, 2);
                    gets(rec[i].title);
                    gotoxy(13, 3);
                    cin >> rec[i].tim.year;
                    gotoxy(20, 3);
                    cin >> rec[i].tim.month;
                    gotoxy(25, 3);
                    cin >> rec[i].tim.day;
                    gotoxy(32, 3);
                    cin >> rec[i].tim.hour;
                    gotoxy(35, 3);
                    cin >> rec[i].tim.minute;
                    getchar();
                    gotoxy(13, 4);
                    gets(rec[i].place);
                    gotoxy(position + 84, 40);
                    cout << "(press 'Enter' to exit)";
                    gotoxy(0, 7);
                    gets(rec[i].note);
                    break;
                default:
                    gotoxy(position + 12, 22);
                    cout << "YOU ENTERED WRONG CHOICE";
                    gotoxy(position + 12, 23);
                    system("PAUSE");
                    break;
                }
                break;
            }
            if (i == stcount - 1)
            {
                system("CLS");
                gotoxy(position, 15);
                cout << ">>> This title is not exist <<<";
                getch();
            }
        }
        break;
    case 2:
        system("CLS");
        gotoxy(position - 8, 15);
        cout << "Search your method by initial date (yyyy/mm/dd) :   ";
        gotoxy(position + 45, 15);
        cout << "     /    /    ";
        gotoxy(position + 45, 15);
        cin >> y;
        gotoxy(position + 52, 15);
        cin >> m;
        gotoxy(position + 57, 15);
        cin >> d;
        tmpdate = (y * 365) + (m * 30) + (d);
        system("CLS");
        for (i = 0; i < metcount; i++)
        {
            date[i] = (met[i].tim[0].year * 365) + (met[i].tim[0].month * 30) + (met[i].tim[0].day);
            if (tmpdate == date[i])
            {
                met[i].inc->sum = 0;
                met[i].exp->sum = 0;
                gotoxy(position, 3);
                cout << "##############################################";
                gotoxy(position, 4);
                cout << "##            << Editing Menu >>            ##";
                gotoxy(position, 5);
                cout << "##############################################";
                gotoxy(position, 6);
                cout << "##   1 -> TIMES                             ##";
                gotoxy(position, 7);
                cout << "##   2 -> INCOMES                           ##";
                gotoxy(position, 8);
                cout << "##   3 -> EXPENSES                          ##";
                gotoxy(position, 9);
                cout << "##############################################";
                gotoxy(position, 10);
                cout << "##   Select Item (1 to 3) :                 ##";
                gotoxy(position, 11);
                cout << "##############################################";
                gotoxy(position + 30, 10);
                cin >> it;
                system("CLS");
                for (j = 5; j < position + 120; j++)
                {
                    gotoxy(j, 4);
                    cout << "#";
                }
                gotoxy(position + 3, 2);
                cout << "From      /    /     to       /    /    ";
                gotoxy(position - 34, 6);
                cout << "<< Incomes >>";
                gotoxy(position + 64, 6);
                cout << "<< Expenses >>";
                j = 5;
                for (j = 5; j < position + 120; j++)
                {
                    gotoxy(j, 8);
                    cout << "#";
                }
                // Horizental separator line under the Row, Quntity ($) & Explanation
                j = 5;
                for (j = 5; j < position + 120; j++)
                {
                    gotoxy(j, 10);
                    cout << "_";
                }
                // Incomes subsets
                gotoxy(6, 9);
                cout << "Row";
                gotoxy(12, 9);
                cout << "Quntity ($)";
                gotoxy(48, 9);
                cout << "Explanation";
                for (k = 1; k <= 2 * (met[i].inc->in) + 2; k++)
                {
                    if (k <= met[i].inc->in)
                    {
                        gotoxy(6, 2 * k + 9);
                        cout << k;
                    }
                    if (k % 2 == 0 && k > 3)
                    {
                        j = 5;
                        for (j = 5; j < position + 18; j++)
                        {
                            gotoxy(j, k + 8);
                            cout << "-";
                        }
                    }
                    gotoxy(10, k + 8);
                    cout << "|";
                    gotoxy(24, k + 8);
                    cout << "|";
                }
                // Expenses subsets
                gotoxy(position + 21, 9);
                cout << "Row";
                gotoxy(position + 27, 9);
                cout << "Quntity ($)";
                gotoxy(position + 66, 9);
                cout << "Explanation";
                k = 1;
                for (k = 1; k <= 2 * (met[i].exp->ex) + 2; k++)
                {
                    if (k <= met[i].exp->ex)
                    {
                        gotoxy(position + 21, 2 * k + 9);
                        cout << k;
                    }
                    if (k % 2 == 0 && k > 3)
                    {
                        j = 100;
                        for (j = position + 20; j < position + 120; j++)
                        {
                            gotoxy(j, k + 8);
                            cout << "-";
                        }
                    }
                    gotoxy(position + 25, k + 8);
                    cout << "|";
                    gotoxy(position + 39, k + 8);
                    cout << "|";
                }
                // max in, ex
                max = ((met[i].inc->in) > (met[i].exp->ex) ? (met[i].inc->in) : (met[i].exp->ex));
                // main Vertical separator line
                j = 5;
                for (j = 5; j < 2 * max + 16; j++)
                {
                    gotoxy(position + 18, j);
                    cout << "##";
                }
                switch (it)
                {
                case 1:
                    // put incomes
                    j = 0;
                    for (j = 0; j < met[i].inc->in; j++)
                    {
                        gotoxy(12, 2 * j + 11);
                        cout << met[i].inc[j].quantity;
                        gotoxy(26, 2 * j + 11);
                        puts(met[i].inc[j].explain);
                    }
                    // put expenses
                    j = 0;
                    for (j = 0; j < met[i].exp->ex; j++)
                    {
                        gotoxy(position + 27, 2 * j + 11);
                        cout << met[i].exp[j].quantity;
                        gotoxy(position + 41, 2 * j + 11);
                        puts(met[i].exp[j].explain);
                    }
                    // sum table
                    j = 0;
                    for (j = 0; j < met[i].inc->in; j++)
                    {
                        met[i].inc->sum += (met[i].inc[j].quantity);
                    }
                    j = 0;
                    for (j = 0; j < met[i].exp->ex; j++)
                    {
                        met[i].exp->sum += (met[i].exp[j].quantity);
                    }
                    j = 5;
                    for (j = 5; j < position + 120; j++)
                    {
                        gotoxy(j, 2 * max + 12);
                        cout << "_";
                        gotoxy(j, 2 * max + 13);
                        cout << "-";
                    }
                    gotoxy(0, 2 * max + 14);
                    cout << "SUM =>";
                    gotoxy(position + 13, 2 * max + 18);
                    cout << "NEST EGG = ";
                    gotoxy(12, 2 * max + 14);
                    cout << met[i].inc->sum;
                    gotoxy(position + 27, 2 * max + 14);
                    cout << met[i].exp->sum;
                    gotoxy(position + 24, 2 * max + 18);
                    cout << ((met[i].inc->sum) - (met[i].exp->sum));
                    // get time
                    j = 0;
                    for (j = 0; j < 2; j++)
                    {
                        gotoxy((position + 8) + 20 * j, 2);
                        cin >> met[i].tim[j].year;
                        gotoxy((position + 15) + 20 * j, 2);
                        cin >> met[i].tim[j].month;
                        gotoxy((position + 20) + 20 * j, 2);
                        cin >> met[i].tim[j].day;
                    }
                    getch();
                    break;
                case 2:
                    // put time
                    j = 0;
                    for (j = 0; j < 2; j++)
                    {
                        gotoxy((position + 8) + 20 * j, 2);
                        cout << met[i].tim[j].year;
                        gotoxy((position + 15) + 20 * j, 2);
                        cout << met[i].tim[j].month;
                        gotoxy((position + 20) + 20 * j, 2);
                        cout << met[i].tim[j].day;
                    }
                    // put expenses
                    j = 0;
                    for (j = 0; j < met[i].exp->ex; j++)
                    {
                        gotoxy(position + 27, 2 * j + 11);
                        cout << met[i].exp[j].quantity;
                        gotoxy(position + 41, 2 * j + 11);
                        puts(met[i].exp[j].explain);
                    }
                    // get incomes
                    j = 0;
                    for (j = 0; j < met[i].inc->in; j++)
                    {
                        gotoxy(12, 2 * j + 11);
                        cin >> met[i].inc[j].quantity;
                        getchar();
                        gotoxy(26, 2 * j + 11);
                        gets(met[i].inc[j].explain);
                    }
                    // sum table
                    j = 0;
                    for (j = 0; j < met[i].inc->in; j++)
                    {
                        met[i].inc->sum += (met[i].inc[j].quantity);
                    }
                    j = 0;
                    for (j = 0; j < met[i].exp->ex; j++)
                    {
                        met[i].exp->sum += (met[i].exp[j].quantity);
                    }
                    j = 5;
                    for (j = 5; j < position + 120; j++)
                    {
                        gotoxy(j, 2 * max + 12);
                        cout << "_";
                        gotoxy(j, 2 * max + 13);
                        cout << "-";
                    }
                    gotoxy(0, 2 * max + 14);
                    cout << "SUM =>";
                    gotoxy(position + 13, 2 * max + 18);
                    cout << "NEST EGG = ";
                    gotoxy(12, 2 * max + 14);
                    cout << met[i].inc->sum;
                    gotoxy(position + 27, 2 * max + 14);
                    cout << met[i].exp->sum;
                    gotoxy(position + 24, 2 * max + 18);
                    cout << ((met[i].inc->sum) - (met[i].exp->sum));
                    getch();
                    break;
                case 3:
                    // put time
                    j = 0;
                    for (j = 0; j < 2; j++)
                    {
                        gotoxy((position + 8) + 20 * j, 2);
                        cout << met[i].tim[j].year;
                        gotoxy((position + 15) + 20 * j, 2);
                        cout << met[i].tim[j].month;
                        gotoxy((position + 20) + 20 * j, 2);
                        cout << met[i].tim[j].day;
                    }
                    // put incomes
                    j = 0;
                    for (j = 0; j < met[i].inc->in; j++)
                    {
                        gotoxy(12, 2 * j + 11);
                        cout << met[i].inc[j].quantity;
                        gotoxy(26, 2 * j + 11);
                        puts(met[i].inc[j].explain);
                    }
                    // get expenses
                    j = 0;
                    for (j = 0; j < met[i].exp->ex; j++)
                    {
                        gotoxy(position + 27, 2 * j + 11);
                        cin >> met[i].exp[j].quantity;
                        getchar();
                        gotoxy(position + 41, 2 * j + 11);
                        gets(met[i].exp[j].explain);
                    }
                    // sum table
                    j = 0;
                    for (j = 0; j < met[i].inc->in; j++)
                    {
                        met[i].inc->sum += (met[i].inc[j].quantity);
                    }
                    j = 0;
                    for (j = 0; j < met[i].exp->ex; j++)
                    {
                        met[i].exp->sum += (met[i].exp[j].quantity);
                    }
                    j = 5;
                    for (j = 5; j < position + 120; j++)
                    {
                        gotoxy(j, 2 * max + 12);
                        cout << "_";
                        gotoxy(j, 2 * max + 13);
                        cout << "-";
                    }
                    gotoxy(0, 2 * max + 14);
                    cout << "SUM =>";
                    gotoxy(position + 13, 2 * max + 18);
                    cout << "NEST EGG = ";
                    gotoxy(12, 2 * max + 14);
                    cout << met[i].inc->sum;
                    gotoxy(position + 27, 2 * max + 14);
                    cout << met[i].exp->sum;
                    gotoxy(position + 24, 2 * max + 18);
                    cout << ((met[i].inc->sum) - (met[i].exp->sum));
                    getch();
                    break;
                }
                break;
            }
            if (i == metcount - 1)
            {
                system("CLS");
                gotoxy(position, 15);
                cout << ">>> This date is not exist <<<";
                getch();
            }
        }
        break;
    default:
        gotoxy(position + 12, 22);
        cout << "YOU ENTERED WRONG CHOICE";
        gotoxy(position + 12, 23);
        system("PAUSE");
        break;
    }
    system("CLS");
    gotoxy(position, 15);
    cout << "... EDITING COMPLETED ...";
    gotoxy(position - 6, 17);
    cout << "... PRESS ANY KEY TO GO MAIN MENU ...";
    getch();
}
//--------------------------------------- Delete records ---------------------------------------
void deleterecord(void)
{
    int x, i, j, y, m, d, tmpdate, date[128];
    char choice, stitle[30], answer;
    do
    {
        system("CLS");
        choice = 'Y';
        gotoxy(position, 7);
        cout << "###################################################";
        gotoxy(position, 8);
        cout << "##   1 -> Search story by title to delete        ##";
        gotoxy(position, 9);
        cout << "##   2 -> Search method by date to delete        ##";
        gotoxy(position, 10);
        cout << "###################################################";
        gotoxy(position, 11);
        cout << "##   Select Item (1 or 2) :                      ##";
        gotoxy(position, 12);
        cout << "###################################################";
        gotoxy(position + 30, 11);
        cin >> x;
        i = 0;
        switch (x)
        {
        case 1:
            system("CLS");
            getchar();
            gotoxy(position, 15);
            cout << "Search your story by title :   ";
            gotoxy(position + 31, 15);
            gets(stitle);
            for (i = 0; i < stcount; i++)
            {
                if (strcmp(rec[i].title, stitle) == 0)
                {
                    system("CLS");
                    answer = 'N';
                    gotoxy(position, 15);
                    cout << "Are you absolutely sure (Y/N) ?!";
                    gotoxy(position + 40, 15);
                    cin >> answer;
                    if (answer == 'y' || answer == 'Y')
                    {
                        j = i;
                        for (j = i; j < stcount; j++)
                        {
                            rec[j] = rec[j + 1];
                        }
                        stcount--;
                        gotoxy(position + 5, 17);
                        cout << "<... DELETED ...>";
                        gotoxy(position, 20);
                        system("PAUSE");
                        break;
                    }
                }
            }
            break;
        case 2:
            system("CLS");
            gotoxy(position - 8, 15);
            cout << "Search your method by initial date (yyyy/mm/dd) :   ";
            gotoxy(position + 45, 15);
            cout << "     /    /    ";
            gotoxy(position + 45, 15);
            cin >> y;
            gotoxy(position + 52, 15);
            cin >> m;
            gotoxy(position + 57, 15);
            cin >> d;
            tmpdate = (y * 365) + (m * 30) + (d);
            system("CLS");
            for (i = 0; i < metcount; i++)
            {
                date[i] = (met[i].tim[0].year * 365) + (met[i].tim[0].month * 30) + (met[i].tim[0].day);
                if (tmpdate == date[i])
                {
                    system("CLS");
                    answer = 'N';
                    gotoxy(position, 15);
                    cout << "Are you absolutely sure (Y/N) ?!";
                    gotoxy(position + 40, 15);
                    cin >> answer;
                    if (answer == 'y' || answer == 'Y')
                    {
                        j = i;
                        for (j = i; j < metcount; j++)
                        {
                            met[j] = met[j + 1];
                        }
                        metcount--;
                        gotoxy(position + 5, 17);
                        cout << "<... DELETED ...>";
                        gotoxy(position, 20);
                        system("PAUSE");
                        break;
                    }
                }
            }
            break;
        default:
            gotoxy(position + 12, 22);
            cout << "YOU ENTERED WRONG CHOICE";
            gotoxy(position + 12, 23);
            system("PAUSE");
            break;
        }
        system("CLS");
        gotoxy(position - 2, 17);
        cout << "Do You Want To delete another record (Y/N) ?!";
        gotoxy(position + 45, 17);
        cin >> choice;
    } while (choice != 'N' && choice != 'n');
}
//--------------------------------------- Edit Password ---------------------------------------
void editpassword(void)
{
    system("CLS");
    string pass = "";
    char ch;
    gotoxy(45, 8);
    cout << "Enter your current password: ";
    ch = getch();
    while (ch != 13)
    { // character 13 is "Enter" (ASCII CODE)
        pass.push_back(ch);
        cout << '*';
        ch = getch();
    }
    if (pass == X)
    {
        system("CLS");
        gotoxy(45, 8);
        cout << "Enter your new password: ";
        cin >> X;
    }
    else
    {
        cout << "\nAccess Aborted...\n\n";
        system("PAUSE");
        system("CLS");
        editpassword();
    }
}
//--------------------------------------- Main Function ---------------------------------------
main()
{
    Load();
    login();
    int item;
    char ch;
    gotoxy(position + 15, 2);
    cout << ":::    NOTEBOOK   :::";
    do
    {
        system("CLS");
        ch = 'N';
        gotoxy(position + 15, 2);
        cout << ":::    NOTEBOOK   :::";
        gotoxy(position, 5);
        cout << "###################################################";
        gotoxy(position, 6);
        cout << "|##               << Main Menu >>               ##|";
        gotoxy(position, 7);
        cout << "###################################################";
        gotoxy(position, 8);
        cout << "|  ##   1 -> Add a new record                 ##  |";
        gotoxy(position, 9);
        cout << "| ##   2 -> View your records                  ## |";
        gotoxy(position, 10);
        cout << "|##   3 -> Search data                          ##|";
        gotoxy(position, 11);
        cout << "##   4 -> Edit records                           ##";
        gotoxy(position, 12);
        cout << "|##   5 -> Delete records                       ##|";
        gotoxy(position, 13);
        cout << "| ##   6 -> Edit password                      ## |";
        gotoxy(position, 14);
        cout << "|  ##   7 -> Save & Exit                      ##  |";
        gotoxy(position, 15);
        cout << "###################################################";
        gotoxy(position, 16);
        cout << "|##                                             ##|";
        gotoxy(position, 17);
        cout << "##   Select Item (1 - 7) :                       ##";
        gotoxy(position, 18);
        cout << "|##                                             ##|";
        gotoxy(position, 19);
        cout << "###################################################";
        gotoxy(position + 4, 23);
        cout << "+++++ Programed by Alinejad Alinejad +++++";
        gotoxy(position + 30, 17);
        cin >> item;
        switch (item)
        {
        case 1:
            addrecord();
            break;
        case 2:
            viewrecord();
            break;
        case 3:
            searchdata();
            break;
        case 4:
            editrecord();
            break;
        case 5:
            deleterecord();
            break;
        case 6:
            editpassword();
            break;
        case 7:
            gotoxy(position, 17);
            cout << "##   Do You Want To Exit (Y/N) ?!                ##";
            gotoxy(position + 35, 17);
            cin >> ch;
            break;
        default:
            gotoxy(position + 12, 22);
            cout << "YOU ENTERED WRONG CHOICE";
            gotoxy(position + 12, 23);
            system("PAUSE");
            break;
        }
    } while (ch != 'Y' && ch != 'y');
    Save();
    return 0;
}
//........................ THE END ........................