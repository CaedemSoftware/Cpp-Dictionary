#include <iostream>
#include <vector>
#include <fstream>
using namespace std;



int main()
{
    ifstream reader("Data.CS.SFSU.txt");
    string a;
    while(!(reader.eof())) {
        reader >> a;
        cout << a << endl;
    }
    reader.close();
    return 0;
}