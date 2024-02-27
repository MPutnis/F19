/*
Putnis Mārtiņš
mp13031
Programma izveidota: 20.02.2024
=== F19 =======================================

Izveidot programmu valodā C++, kas apstrādā teksta failu secīgā režīmā.
Dati no faila jānolasa pa vienai rindiņai. Nedrīkst dublēt visa faila saturu operatīvajā atmiņā.
Sīkākas prasības sk. Laboratorijas darbu noteikumos.

F19. Izvadīt dotajā teksta failā f sastapto latīņu alfabēta burtu un ciparu lietojuma biežuma tabulu (šķirojot lielos un mazos burtus) failā f1. Tabulai jābūt sakārtotai pēc burtu lietojuma biežuma.
*/
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class symbols 
{
private:
    char name = ' ';
    int count = 0;
public:
    // create object and increase count by 1
    symbols(char s) 
    {
        setName(s);
        countInc();
    }
    symbols() {}
    void setName(char s)
    {
        name = s;
    }
    char getName() 
    {
        char c = name;
        return c;
    }
    // returns current count of a char
    int getCount()
    {
        return count;
    }
    // method to increase symbol count by 1
    void countInc()
    {
        count++;
    }
    // return object information as string
    string print()
    {
        string ch = "'" + string(1,name) + "': " + to_string(count);
        return ch;
    }
};

// function to count number of different symbols in an object array
int countSymbols (symbols *s)
{
    int i = 0;
    while(s[i].getName() != ' ')
        i++;
    return i;
}
// function to count total number of case sensitive alpha-numeric characters
int countTotal (symbols *s)
{
    int i = 0, sum=0;
    while( s[i].getName() != ' ')
    {
        sum += s[i].getCount();
        i++;
    }
    return sum;
}

// function to insert char or increase char count in a symbols object array
void insertChars( char s, symbols *c) // c- array of symbols objects
{
    // check if symbols array c contains s
    bool found = false;
    for (int j = 0; j <= 62; j++)
    {
        // if c already has ss, increase count by one
        if( c[j].getName() == s)
        {
            c[j].countInc();
            found = true;
            break;
        }               
    }
    // if c doesn't contain ss, create new object
    if (!found) {
        // find first empty object in c
        int f = 0;
        while (c[f].getName() != ' ')
            f++;
        c[f].setName(s);
        c[f].countInc();
    }
}

// function to sort an object array
void sortArr( symbols *c)
{
    int symCount = countSymbols(c);
    for( int i = 0; i < symCount -1; i++)
        for( int j = symCount - 1; j > i; j--)
        {
            if ( c[j].getCount() >= c[j-1].getCount())
            {
                // when lower position symbol count is higher than higher position symbol count
                if ( c[j].getCount() > c[j-1].getCount())
                {
                    symbols tmp = c[j-1];
                    c[j-1] = c[j];
                    c[j] = tmp;
                }
                // when count is equal, put the object with lower ASCII code on top
                else if (int(c[j].getName()) < int(c[j-1].getName()))
                {
                    symbols tmp = c[j-1];
                    c[j-1] = c[j];
                    c[j] = tmp;

                }
            }
        }
}

// function to write 3 arrays to a file
void writeArr(symbols *u, symbols *l, symbols *n, fstream &f)
{
    int uLen = countSymbols(u), lLen = countSymbols(l), nLen = countSymbols(n);
    int maxLength = max(lLen, nLen);
    maxLength = max(maxLength, uLen);
    for (int i = 0; i < maxLength; i++)
    {
        string uc, lc, nu; // will hold output values
        // has i reached the end of uppercase array? If yes, then tab, else print array[i]
        (i >= uLen) ? uc = "\t\t" : uc = u[i].print();
        // has i reached the end of lowercase array? If yes, then tab, else print array[i]
        (i >= lLen) ? lc = "\t\t" : lc = l[i].print();
        // has i reached the end of numbers array? If yes, then tab, else print array[i]
        (i >= nLen) ? nu = "" : nu = n[i].print();
        f << i+1 << ".\t| " << uc << "\t| " << lc << "\t| " << nu << endl;
    }
}

int main() {
    fstream f, f1;
    f.open("text.txt", ios::in);
    f1.open("table.txt", ios::out);
    string s;

    // Declare 3 arrays
    symbols upCase[26], lowCase[26], nums[10];
    
    getline( f, s);
    while( !f.eof())
    {
        //cycle throug chars of a string
        for( int i = 0; i < s.length(); i++)
        {
            // Fill 3 arrays, one for each type of symbol
            if( isdigit(s[i])) 
                insertChars( s[i], nums);
            else if( islower(s[i]))
                insertChars( s[i], lowCase);
            else if( isupper(s[i]))
                insertChars(s[i], upCase);
        }
        getline( f, s);
    }
    // count last line
    for( int i = 0; i < s.length(); i++)
    {
        // Fill 3 arrays, one for each type of symbol
        if( isdigit(s[i])) 
            insertChars( s[i], nums);
        else if( islower(s[i]))
            insertChars( s[i], lowCase);
        else if( isupper(s[i]))
            insertChars(s[i], upCase);

    }
    // sort all arrays
    sortArr(nums);
    sortArr(lowCase);
    sortArr(upCase);
    //output each array in a new column
    writeArr(lowCase, nums, upCase, f1);
    std::cout << countSymbols(nums) << " different numbers counted!\n";
    std::cout << "Total count: " << countTotal(nums) << endl;
    std::cout << countSymbols(lowCase) << " different lower case characters counted!\n";
    std::cout << "Total count: " << countTotal(lowCase) << endl;
    std::cout << countSymbols(upCase) << " different upper case characters counted!\n";
    std::cout << "Total count: " << countTotal(upCase) << endl;
    f.close();
    f1.close();
    
    return 0;
}