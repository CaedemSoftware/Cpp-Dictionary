#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

class dictionary { // move this into seprate file as well 
private:
    string word;
    string speech;
    string definition;
public:
    string getWord() {
        return word;
    }

    string getSpeech() {
        return speech;
    }
    string getDefinition() {
        return definition;
    }


};


int main()
{
    // we should probably put this in a separate class or something but i've left it in main for the time being

    // data stuff (ends at line 66)
    string absolutePath = "C:\\Users\\MickeyMouse\\AbsolutePath\\DB\\Data.CS.SFSU.txt\n"; // dummy string we use out of formality for the incorrect path used in the sample output by Duc
    string realPath = "./Data.CS.SFSU.txt"; // string that is what we want the user to input
    cout << "! Opening data file... " << absolutePath;
    try {
        //open absolute path
        ifstream isItCorrectFilePath(absolutePath); // syntax: ifStream name(string). it reads the string on the inside to see if it is a valid data file to read, which it then opens
        if (!isItCorrectFilePath.is_open()) { //  if the stream did not open a valid data file, like if its name is incorrect, throw an invalid argument
            throw std::invalid_argument("incorrect file path"); 
        }

    }
    catch (...) {
        string filePath; // string i made just as an end condition. brainpower low, effort minimal, but it works

        cout << "<!>ERROR<!> ===> File could not be opened.\n"
             << "<!> ERROR<!> == = > Provided file path: " << absolutePath << endl;
        bool correctFilePath = false;
        
        while (!correctFilePath) {
            cout << "<!>Enter the CORRECT data file path:  " << endl;
            filePath = realPath; // change this to "cin >> filepath;" whenever we're done 
            if (filePath == realPath) { // if the user's input (filepath) is equivalent to the path we want (realpath, which is: ./Data.CS.SFSU.txt, then we proceed"
                correctFilePath = true;
            }
            else {
                cout << "This shouldn't ever come up in the output but is here anyway. The correct file path is './Data.CS.SFSU.txt'. Please enter it to proceed." << endl; 
                //  ^ this is formality, not needed but i thought i'd add it
            }
            
        }
            
    }
    cout << "! Loading data..." << endl;
    //load data
    cout << "! Loading completed..." << endl;
    //close file
    cout << "! Closing data file... ./Data.CS.SFSU.txt\n" << endl;

    cout << "====== DICTIONARY 340 C++ ====="
        << "\n------Keywords: " //19
        << "\n------Definitions: " << "\n" << endl;//61
    int searchCount = 1;

    while (true) {
        string searchKey;
        cout << "Search [" << searchCount << "]: ";
        cin >> searchKey;
        searchCount++;
        if (searchCount > 2) {
            break;
        }
    }
    // end of data stuff

	ifstream reader("./Data.CS.SFSU.txt");
	string a, b, c, d;
	if (reader.is_open()) {
		reader >> a;
		reader >> b;
		reader >> c;
		reader >> d;
		cout << a << endl;
		cout << b << endl;
		cout << c << endl;
		cout << d << endl;
	}
	reader.close();
	cout << "pause" << endl;
	return 0;

}
