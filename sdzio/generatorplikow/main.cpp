#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
using namespace std;

int main()
{   int pomoc;
int i =0;
    ofstream wypisz("dane.txt");
    srand( time( NULL ) );
    cin>>pomoc;
    wypisz<<pomoc<<endl;
    while(pomoc>i)
    {
        wypisz<<(rand()%4+1)*(rand()%13+1)*(rand()%25+1)*(rand()%7+1)-200<<endl;
        i++;
    }

    return 0;
}
