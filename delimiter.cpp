#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;


void main()
{

    /*string test = "| rona ligma | lmao rona | balls rona";
    string delimiter = "|";
    while ((pos = s.find(delimiter)) != std::string::npos) {
        string test = test.substr(test.find(delimiter) + delimiter.size() + 1, test.find_last_of(delimiter));
        cout << test << endl;
    }
    return;
    */

    //needed split to loop
    std::string s = "arrow|noun -=>> Here is one arrow: <IMG> -=>> </IMG>..   \nbook | noun -=> > A set of pages. | verb -=> > To arrange something on a particular date. | verb -=> > to arrange for someone to have a seat on a plane. | noun -=> > A written work published in printed or electronic form. ";
    std::string delimiter = "|";

    size_t pos = 0;
    std::string token;
    while ((pos = s.find(delimiter)) != std::string::npos) {//while delimeter found
        token = s.substr(0, pos);//token is substring from beginning to delimeter
        std::cout << token << std::endl;//put in data source instead of cout
        s.erase(0, pos + delimiter.length());//remove the previous substring from the string in use
    }
    std::cout << "not in token:" << s << std::endl;//put in data source instead of cout
}
