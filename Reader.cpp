#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>
using namespace std;



void read()
{  
    ifstream reader("./Data.CS.SFSU.txt");
    
    string str; 
    string outerDelimiter = "|";
    string innerDelimiter = "-=>>";
    size_t pos = 0;
    string outerToken;
    string innerToken;
    int counter = 0; // see line 37

    // tl;dr this is messy but it grabs what we want (except for arrow). i don't know how to go about putting it into a data structure so i'd like help on that
    // arrow is fucked up and i'm not quite sure how to fix that. worst case scenario we hard-code but i'm not sure how to make an exception to it

    // outermost loop grabs every line in the .txt
    // middle loop (line 29) isolates keyword by itself, then speech and definitions as the remaining string
    // innermost loop (line 35) isolates speech, and groups up the rest of definitions

    while (getline(reader, str)) { // this iterates through every line in the text file and turns it into a string 'str'
        while ((pos = str.find(outerDelimiter)) != string::npos) { // while delimiter has a position inside the string, keep going
            outerToken = str.substr(0, pos);
            string keyword = outerToken; // marker for later: we can capture keyword at this spot
            str.erase(0, pos + outerDelimiter.length());
            cout << "Keyword: " << outerToken << endl;
            
            while ((pos = str.find(innerDelimiter)) != string::npos) {
                innerToken = str.substr(0, pos);
                if (counter == 0) { // this is very caveman-like but counter exists only to indicate which token it should grab as the Speech, which is always the first thing every iteration
                    string figureOfSpeech = innerToken.substr(0, innerToken.size() - 1); // -1 is to remove the space during printing, not really a big deal
                    counter++; // increases counter to 1 in order to skip grabbing speech for everything else. this is what distinguishes speech and definition in this parsing
                }
                str.erase(0, pos + innerDelimiter.length()); 
                // ^ due to how this loop works, it grabs both speech and definition. we could just easily slap this into a data structure then destroy index 0 to only keep definitons
                cout << innerToken << endl;
            }
            counter = 0;
        }
        cout << str << endl << endl; // this loop always skips out on the last definition but adding this here fixes that. double endl for formatting output

    }
    cout << endl;
    reader.close();
    cout << "pause" << endl;
    return 0;
}
