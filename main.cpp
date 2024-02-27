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
        return name;
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

// function to extract and count different chars in a string
void extractChars( string s, symbols *c)
{
    char ss;
    for( int i = 0; i < s.length(); i++)
    {
        ss = s[i];
        if( isalnum(ss))
        //(ss >= 'a' && ss <= 'z') || (ss >= 'A' && ss <= 'Z') || (ss >= '0' && ss <= '9')
        {
            // check if symbols array ch contains ss
            bool found = false;
            for (int j = 0; j <= 62; j++)
            {
                // if ch already has ss, increase count by one
                if( c[j].getName() == ss)
                {
                    c[j].countInc();
                    found = true;
                    break;
                }               
            }
            // if ch doesn't contain ss, create new object
            if (!found) {
                // find first empty object ch
                int f = 0;
                while (c[f].getName() != ' ')
                    f++;
                c[f].setName(ss);
                c[f].countInc();
            }
        }
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

// function to write an array to a file
void writeArr(symbols *c, fstream &f)
{
    for (int i = 0; c[i].getName() != ' '; i++)
    {
        f << i+1 << ")\t" << c[i].print() << endl;
    }
}

int main() {
    fstream f, f1;
    f.open("text.txt", ios::in);
    f1.open("table.txt", ios::out);
    string s;
    symbols ch[62];
    
    getline( f, s);
    while( !f.eof())
    {
        extractChars(s, ch);
        getline( f, s);
    }
    // count last line
    extractChars(s, ch);
    sortArr(ch);
    writeArr(ch, f1);
    cout << countSymbols(ch) << " different chars counted!\n";
    cout << "Total count: " << countTotal(ch) << endl;
    
    f.close();
    f1.close();
    
    return 0;
}