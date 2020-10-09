#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;


int main()
{

    string test = "rona ligma SPLIT lmao rona ";
    string delimiter = "SPLIT";
    string token1 = test.substr(0, test.find(delimiter));
    string token2 = test.substr(test.find(delimiter) + delimiter.size() + 1, test.length());
    cout << token1 << endl;
    cout << token2 << endl;
    return 0;
}